#include "socket.h"

#include "SDL.h"
#include "SDL_keyboard.h"

#ifdef WIN32
#include <winsock2.h>
#include <errno.h>
#include "pthread.h"
/*
#define EADDRINUSE WSAEADDRINUSE
#define EADDRNOTAVAIL WSAEADDRNOTAVAIL
#define EAFNOSUPPORT WSAEAFNOSUPPORT
#define EALREADY WSAEALREADY
#define ECONNABORTED WSAECONNABORTED
#define ECONNREFUSED WSAECONNREFUSED
#define ECONNRESET WSAECONNRESET
#define EDESTADDRREQ WSAEDESTADDRREQ
#define EDQUOT WSAEDQUOT
#define EHOSTDOWN WSAEHOSTDOWN
#define EHOSTUNREACH WSAEHOSTUNREACH
#define EINPROGRESS WSAEINPROGRESS
#define EISCONN WSAEISCONN
#define ELOOP WSAELOOP
#define EMSGSIZE WSAEMSGSIZE
#define ENETDOWN WSAENETDOWN
#define ENETRESET WSAENETRESET
#define ENETUNREACH WSAENETUNREACH
#define ENOBUFS WSAENOBUFS
#define ENOPROTOOPT WSAENOPROTOOPT
#define ENOTCONN WSAENOTCONN
#define ENOTSOCK WSAENOTSOCK
#define EOPNOTSUPP WSAEOPNOTSUPP
#define EPFNOSUPPORT WSAEPFNOSUPPORT
#define EPROTONOSUPPORT WSAEPROTONOSUPPORT
#define EPROTOTYPE WSAEPROTOTYPE
#define EREMOTE WSAEREMOTE
#define ESHUTDOWN WSAESHUTDOWN
#define ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
#define ESTALE WSAESTALE
#define ETIMEDOUT WSAETIMEDOUT
#define ETOOMANYREFS WSAETOOMANYREFS
#define EUSERS WSAEUSERS
#define EWOULDBLOCK WSAEWOULDBLOCK
*/
#else
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#endif

#include "socket.h"
#include "core/ThreadDispatcher.h"
#include "core/oxygine.h"
#include "Event.h"
#include "core/ox_debug.h"

#include "utils/stringUtils.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif


#include "core/log.h"

#ifdef WIN32
WSADATA _wsa;
#endif



bool debugSocketCheckKey(int k)
{
#ifdef OX_DEBUG
    const Uint8* data = SDL_GetKeyboardState(0);
    if (data[k])
        return true;
#endif
    return false;
}

#define SINGLE_THREAD 0

using namespace oxygine;

Socket::Socket(): _socket(0), _status(status_disconnected), _connection(pthread_self())
{
}

Socket::~Socket()
{
    close();
}

void Socket::init()
{
#ifdef _WIN32
    WSAStartup(0x0202, &_wsa);
#endif
}
void Socket::release()
{
#ifdef _WIN32
    WSACleanup();
#endif

}

void Socket::close()
{
    if (_socket)
    {
#ifdef EMSCRIPTEN
        EM_ASM_INT(
        {
            return socket.close($0);
        }, _socket);
#else

#   ifdef WIN32
        closesocket(_socket);
#   else
        ::shutdown(_socket, 0);
        ::close(_socket);

#   endif

#   if !SINGLE_THREAD
        pthread_join(_connection, 0);
        _connection = pthread_self();
#   endif
#endif

        _status = status_disconnected;
        _socket = 0;
    }
}


bool SetSocketBlockingEnabled(int fd, bool blocking)
{
    if (fd < 0)
        return false;

#ifdef WIN32
    unsigned long mode = blocking ? 0 : 1;
    return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
#else
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return false;
    flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
#endif
}

void Socket::connection()
{
    log::messageln("Socket::connection begin %s:%d", _host.c_str(), _port);

    struct hostent*        he;

    if ((he = gethostbyname(_host.c_str())) == NULL)
    {
        log::message("Socker::connection gethostname failed");

        core::getMainThreadDispatcher().postCallback([ = ]()
        {
            error();
            releaseRef();
        });
        return;
    }

    _socket = socket(AF_INET, SOCK_STREAM, 0);


    sockaddr_in* serv = new sockaddr_in;
    memset(serv, 0, sizeof(sockaddr_in));

    serv->sin_family = AF_INET;
    serv->sin_port = htons(_port);

    memcpy(&serv->sin_addr, he->h_addr_list[0], he->h_length);

    int r = ::connect(_socket, (sockaddr*)serv, sizeof(sockaddr_in));
    delete serv;

    if (debugSocketCheckKey(SDL_SCANCODE_R))
        r = -1;

    if (r == -1)
    {
        core::getMainThreadDispatcher().postCallback([ = ]()
        {
            error();
            releaseRef();
        });
        return;
    }

    SetSocketBlockingEnabled(_socket, false);

    core::getMainThreadDispatcher().postCallback([ = ]()
    {
        connected();
        releaseRef();
    });
}

void Socket::error()
{
    log::messageln("Socket::connection failed");
    _status = status_disconnected;

    Event ev(EVENT_DISCONNECTED);
    dispatchEvent(&ev);
}

void Socket::connected()
{
    log::messageln("Socket::connected to %s:%d", _host.c_str(), _port);
    _status = status_connected;

    Event ev(EVENT_CONNECTED);
    dispatchEvent(&ev);
}


void* Socket::sconnection(void* p)
{
    ((Socket*)p)->connection();
    return 0;
}

void Socket::connect(int port, const char* host)
{
    _status = status_connecting;
    _port = port;
    _host = host;

    /*
    #if EMSCRIPTEN
    int v = 0;
    EM_ASM_INT({
        return socket.test($0);
    }, &v);
    log::messageln("res %d", v);
    return;
    #endif
    */




#if EMSCRIPTEN
    char addr[255];
    safe_sprintf(addr, "ws://slots-server-dev0.alisagaming.net:80/");
    _socket = EM_ASM_INT(
    {
        return socket.connect(Pointer_stringify($0));
    }, addr);
    return;
#else
    OX_ASSERT(_socket == 0);


#   if SINGLE_THREAD
    int r = ::connect(_socket, (sockaddr*)serv, sizeof(sockaddr_in));
    SetSocketBlockingEnabled(_socket, false);
#   else
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    addRef();
    pthread_create(&_connection, &attr, Socket::sconnection, this);
#   endif

#endif
}


Socket::status Socket::getStatus() const
{
#if EMSCRIPTEN
    int s = EM_ASM_INT(
    {
        return socket.status($0);
    }, _socket);

    switch (s)
    {
        case 0:
            _status = status_connecting;
            break;
        case 1:
            _status = status_connected;
            break;
        case -1:
            _status = status_disconnected;
            break;
        default:
            break;
    }
    //log::messageln("status %d", s);
#else
#endif


    return _status;
}

bool isCriticalError()
{
#ifdef WIN32
    int er = WSAGetLastError();
#else
    int er = errno;
#endif

    switch (er)
    {
#ifdef WIN32
        //case WSATRY_AGAIN:
        case WSAEWOULDBLOCK:
#else
        case EWOULDBLOCK:
#endif
            return false;
        default:
            break;
    }

    log::messageln("MySocket error");
    return true;
}

int Socket::send(const char* buf, int size)
{
    OX_ASSERT(_status == status_connected);


    if (debugSocketCheckKey(SDL_SCANCODE_E))
    {
        if (debugSocketCheckKey(SDL_SCANCODE_LSHIFT))
        {
            close();
            return -1;
        }
        return 0;
    }

#if EMSCRIPTEN

    EM_ASM_INT(
    {
        var length = $2;
        var data = new Int8Array(length);
        for (var i = 0; i < length; i++)
        {
            data[i] = getValue($1 + i, 'i8');
        }

        return socket.message($0, data, $2);
    }, _socket, buf, size);

    return size;

#else

    int messageSent = 0;
    do
    {
        size_t bt = size - messageSent;
        int retValue = static_cast<int>(::send(_socket, buf + messageSent, bt, 0));

        // sending has been successful, see how many bytes are left to send
        if (retValue > 0)
            messageSent += retValue;

        // an error occurred while sending
        if (retValue < 0)
        {
            if (!isCriticalError())
                return messageSent;//try next time

            close();

            return -1;
        }

    }
    while (messageSent < size);

    return messageSent;
#endif
}

int Socket::receive(char* buf, int size)
{
    if (debugSocketCheckKey(SDL_SCANCODE_E))
    {
        if (debugSocketCheckKey(SDL_SCANCODE_LSHIFT))
        {
            close();
            return -1;
        }
        return 0;
    }

#if EMSCRIPTEN

    size = EM_ASM_INT(
    {
        return socket.update($0, $1, $2);
    }, _socket, buf, size);

    /*
    if (size)
    {
        log::messageln("rec %d", size);
        for (int i = 0; i < size; ++i)
        {
            log::messageln("%d, ", (unsigned char)buf[i]);
        }

        //memcpy(buf, data, size);
    }
    */

    return size;

#else


    size_t ret = recv(_socket, buf, size, 0);

    if (ret == -1)
    {
        if (!isCriticalError())
            return 0;

        close();
        return -1;
    }

    /*
    if (ret)
    {
        log::messageln("rec %d", ret);
        for (int i = 0; i < ret; ++i)
        {
            log::messageln("%d, ", (unsigned char)buf[i]);
        }
    }
    */

    return  static_cast<int>(ret);
#endif
}
