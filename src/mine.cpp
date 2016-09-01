/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "mine.h"

Mine::Mine()
{

}

void Mine::init(
  int ID,
  std::string name,
  int size,
  int rarity,
  int storage_capacity,
  std::string brand,
  std::string model)
{
  this->setID(ID);
  this->setName(name);
  this->setSize(size);
  this->setRarity(rarity);
  this->setStorageCapacity(storage_capacity);
  this->setBrand(brand);
  this->setModel(model);

  log();
}

void Mine::log()
{
  log::messageln("\n[MINE]\nStorage Cap: %d\n",
    this->getStorageCapacity());
}

void Mine::setStorageCapacity(int cap)
{
  _storage_capacity = cap;
}

void Mine::setStorage(int element, int amount)
{
  _storage[element] = amount;
}

void Mine::setStorageDefault()
{
  for (int i = 0; i < 120; i++)
  {
    _storage[i] = 0;
  }
}

int Mine::getStorageCapacity()
{
  return _storage_capacity;
}

int Mine::getStorage(int element)
{
  return _storage[element];
}
