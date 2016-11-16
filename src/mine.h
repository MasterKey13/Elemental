/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "json/json.h"
#include "item.h"

//declare smart pointer
DECLARE_SMART(Item, spItem);

using namespace oxygine;

class Mine : public Item
{
  public:
    Mine();

    void setChemStorageCapacity(int cap);
    void setChemStorage(int element, int amount);
    void setEfficiency(int efficiency);
    void setReliability(int reliability);
    void setStorageDefault();
    void setCurrentTotalStorage(int amount);
    void setHostBody(spCelestialBody host);
    void setMaxTemp(int temp);

    int getChemStorageCapacity();
    int getChemStorage(int element);
    int getMiningEfficiency();
    int getMiningReliability();
    int getCurrentChemStorage();
    int getMaxTemp();
    spCelestialBody getHostBody();

    void extract();

  private:
    spCelestialBody _host;
    int _composition[MAX_ELEMENTS];
    int _mining_efficiency;
    int _mining_reliability;
    int _storage_capacity;
    int _storage[MAX_ELEMENTS];
    int _current_total_storage;
    int _max_temp;
};