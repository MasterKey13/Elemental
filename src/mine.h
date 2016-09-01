/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"

using namespace oxygine;

class Mine : public Item
{
  public:
    Mine();

    void init(
      int ID,
      std::string name,
      int size,
      int rarity,
      int storage_capacity,
      std::string brand = "",
      std::string model = "");

    void log();

    //SETTERS
    void setStorageCapacity(int cap);
    void setStorage(int element, int amount);
    void setStorageDefault();

    //GETTERS
    int getStorageCapacity();
    int getStorage(int element);

  private:
    int _storage_capacity;
    int _storage[120];
};
