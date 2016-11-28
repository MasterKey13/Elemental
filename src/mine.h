/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "celestial_body.h"

//declare smart pointer
DECLARE_SMART(CelestialBody, spCelestialBody);
DECLARE_SMART(Mine, spMine);

using namespace oxygine;

class Mine : public Item
{
  public:
    Mine();

    void init(int chem_storage_max, int efficiency, int reliability, int max_temp);

    void init(std::string ID);

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