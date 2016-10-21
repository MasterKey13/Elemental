/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "celestial_body.h"

using namespace oxygine;

#define MAX_ELEMENTS 50

DECLARE_SMART(CelestialBody, spCelestialBody);

class Mine : public Item
{
  public:
    Mine();

    void init(
      int ID,
      std::string name,
      int size,
      int efficiency,
      int reliability,
      int storage_capacity,
      int max_temp,
      std::string brand = "");

    void initByID(int ID);

    void log();

    //SETTERS
    void setStorageCapacity(int cap);
    void setStorage(int element, int amount);
    void setEfficiency(int efficiency);
    void setReliability(int reliability);
    void setStorageDefault();
    void setCurrentTotalStorage(int amount);
    void setHostBody(spCelestialBody host);
    void setMaxTemp(int temp);

    //GETTERS
    int getStorageCapacity();
    int getStorage(int element);
    int getEfficiency();
    int getReliability();
    int getCurrentStorage();
    spCelestialBody getHostBody();
    int getMaxTemp();

    void extract();

  private:
    int _storage_capacity;
    int _efficiency; //extraction multiplier, how efficiently it mines
    int _reliability; //chance that it will extract an element (from 0 - 10000, where 10000 = 100.00%)
    int _storage[MAX_ELEMENTS];
    int _current_total_storage;
    spCelestialBody _host;
    int _max_temp;
};
