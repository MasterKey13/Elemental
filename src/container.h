/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"

//declare smart pointer
DECLARE_SMART(Container, spContainer);

using namespace oxygine;

class Container : public Item
{
  public:
    Container();

    void init(int capacity);

    void init(std::string ID);

    //SETTERS
    void setCapacity(int cap);

    //GETTERS
    int getCapacity();

  private:
    int _capacity;
    spItem _storage[];
};