/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "item.h"

Item::Item()
{

}

//! Initialize a custom item with given parameters
/*!
\param ID ID of the item
\param size size of the item
\param name name of the item
\param desc description of the item
\param brand the brand name of the item
\param model model name of the item
\param craftable whether the item is craftable
*/
void Item::init(
  int ID, 
  int size,
  std::string name,
  std::string desc,
  std::string brand, 
  std::string model,
  bool craftable)
{
  this->setID(ID);
  this->setName(name);
  this->setSize(size);
  this->setDescription(desc);
  this->setCompositionDefault();

  if (brand.length() > 0)
  {
    this->setBrand(brand);
  }

  if (model.length() > 0)
  {
    this->setModel(model);
  }
  
  this->setCraftable(craftable);

  log();
}

//! Initialize an item by ID (load from item definition file items.json)
/*!
\param ID ID of the item
*/
void Item::initByID(int ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/items.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["items"];

  //go through the json file and find the item by ID
  for (int i = 0; i < items.size(); i++)
  {
    if (items[i]["id"].asInt() == ID)
    {
      //initialize the item
      init(
        ID,
        items[i]["size"].asInt(),
        items[i]["name"].asCString(),
        items[i]["description"].asCString(),
        items[i]["brand"].asCString(),
        items[i]["model"].asCString(),
        items[i]["craftable"].asBool()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

void Item::log()
{
  log::messageln("\n[ITEM]\nID: %d\nName: %s\nSize: %d\nBrand: %s\nModel: %s\nCraftable: %s\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
    this->getBrand().c_str(),
    this->getModel().c_str(),
    (this->getCraftable() ? "true" : "false"));
}

void Item::setID(int ID)
{
  _itemID = ID;
}

void Item::setName(std::string name)
{
  _name = name;
}

void Item::setDescription(std::string desc)
{
  _desc = desc;
}

void Item::setBrand(std::string brand)
{
  _brand = brand;
}

void Item::setModel(std::string model)
{
  _model = model;
}

void Item::setSize(int size)
{
  _size = size;
}

void Item::setComposition(int element, int abundance)
{
  _composition[element] = abundance;
}

void Item::setCompositionDefault()
{
  for (int i = 0; i < 120; i++)
  {
    _composition[i] = 0;
  }
}

void Item::setCraftable(bool craftable)
{
  _craftable = false;
}

int Item::getID()
{
  return _itemID;
}

std::string Item::getName()
{
  return _name;
}

std::string Item::getDescription()
{
  return _desc;
}

std::string Item::getBrand()
{
  return _brand;
}

std::string Item::getModel()
{
  return _model;
}

int Item::getSize()
{
  return _size;
}

int Item::getComposition(int element)
{
  return _composition[element];
}

bool Item::getCraftable()
{
  return _craftable;
}
