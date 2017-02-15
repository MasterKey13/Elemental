#pragma once
#include <pthread.h>
#include "EventDispatcher.h"

using namespace oxygine;

DECLARE_SMART(Socket, spSocket);
class Socket: public EventDispatcher
{
public:
    static void init();
    static void release();

    Socket();
    ~Socket();

    enum
    {
        EVENT_CONNECTED    = EventID("SoCn"),
        EVENT_DISCONNECTED = EventID("SoDs"),
    };


    enum status
    {
        status_disconnected,
        status_connecting,
        status_connected,
    };

    void connect(int port, const char* host);
    void close();

    int send(const char* buf, int size);
    int receive(char* buf, int size);

    status getStatus() const;

private:
    void error();
    void connected();

    mutable status _status;
    int _socket;

    std::string _host;
    int _port;

    pthread_t _connection;

    void connection();
    static void* sconnection(void*);
};
