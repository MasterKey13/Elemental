/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "container.h"

Container::Container()
{
  setCapacity(0);
}

//! Initialize a container with given parameters
/*!
\param capacity the capacity of the inventory/container
*/
void Container::init(int capacity)
{
  setCapacity(capacity);
}

//! Initialize an item by ID (load from item definition file items.json)
/*!
\param ID ID of the item
*/
void Container::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/containers.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["containers"];

  //go through the json file and find the item by ID
  for (int i = 0; i < items.size(); i++)
  {
    if (ID.compare(items[i]["id"].asCString()) == 0)
    {
      //initialize the item
      Item::init(
        ID,
        items[i]["size"].asInt(),
        items[i]["name"].asCString(),
        items[i]["desc"].asCString(),
        items[i]["brand"].asCString(),
        items[i]["hitpoints"].asInt()
        );

      //initialize the container
      init(items[i]["capacity"].asInt());

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

void Container::setCapacity(int cap)
{
  _capacity = cap;
}

int Container::getCapacity()
{
  return _capacity;
}
