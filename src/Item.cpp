/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "item.h"

Item::Item()
{

}

void Item::init(
  int ID, 
  std::string name, 
  int size,
  std::string brand, 
  std::string model)
{
  this->setID(ID);
  this->setName(name);
  this->setSize(size);
  this->setCompositionDefault();

  if (brand.length() > 0)
  {
    this->setBrand(brand);
  }

  if (model.length() > 0)
  {
    this->setModel(model);
  }

  log();
}

void Item::log()
{
  log::messageln("\n[ITEM]\nID: %d\nName: %s\nSize: %d\nBrand: %s\nModel: %s\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
    this->getBrand().c_str(),
    this->getModel().c_str());
}

void Item::setID(int ID)
{
  _itemID = ID;
}

void Item::setName(std::string name)
{
  _name = name;
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

int Item::getID()
{
  return _itemID;
}

std::string Item::getName()
{
  return _name;
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
