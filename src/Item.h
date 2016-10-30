/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "json/json.h"
#include "celestial_body.h"

//declare smart pointer
DECLARE_SMART(Item, spItem);
DECLARE_SMART(CelestialBody, spCelestialBody);

using namespace oxygine;

#define MAX_ELEMENTS 50

class Item : public Actor
{
  public:
	  Item();

    enum DamageType
    {
      Ballistic,
      Electrical,
      Radioactive,
      Chemical
    };

    void init(
      int ID,
      int size,
      std::string name,
      std::string desc,
      std::string brand,
      int hitpoints,
      int hitpoints_cap,
      int power,
      int power_cap,
      int ballistic_dmg,
      int electrical_dmg,
      int radioactive_dmg,
      int chemical_dmg,
      int ballistic_res,
      int electrical_res,
      int radioactive_res,
      int chemical_res,
      int efficiency,
      int reliability,
      int storage_capacity,
      int max_temp,
      bool craftable,
      bool equipment,
      bool weapon,
      bool battery,
      bool engine,
      bool hull,
      bool mine
      );

    void init(int ID);

    void log();

    //SETTERS
    void setID(int ID);
    void setName(std::string name);
    void setDescription(std::string desc);
    void setBrand(std::string brand);
    void setSize(int size);
    void setComposition(int element, int abundance);
    void setCompositionDefault();
    void setCraftable(bool craftable);
    void setDamageResistance(DamageType type, int resistance);
    void setDamageResistanceDefault();
    void setHitPoints(int hitpoints);
    void setHitPointsCap(int hitpoints_cap);
    void setPower(int power);
    void setPowerCap(int power_cap);
    void setStorageCapacity(int cap);
    void setStorage(int element, int amount);
    void setEfficiency(int efficiency);
    void setReliability(int reliability);
    void setStorageDefault();
    void setCurrentTotalStorage(int amount);
    void setHostBody(spCelestialBody host);
    void setMaxTemp(int temp);
    void setDamage(DamageType damage_type, int damage_resistance);
    void setDamageDefault();

    //GETTERS
    int getID();
    std::string getName();
    std::string getDescription();
    std::string getBrand();
    int getSize();
    int getComposition(int element);
    bool getCraftable();
    int getDamageResistance(DamageType type);
    int getHitPoints();
    int getHitPointsCap();
    int getPower();
    int getPowerCap();
    int getStorageCapacity();
    int getStorage(int element);
    int getEfficiency();
    int getReliability();
    int getCurrentStorage();
    spCelestialBody getHostBody();
    int getMaxTemp();
    int getDamage(DamageType damage_type);

    void extract();

  private:
    int _itemID;
    std::string _name;
    std::string _desc;
    std::string _brand;
    int _size;
    int _composition[120];
    bool _craftable;
    int _damage_resistance[4];
    int _hitpoints;
    int _hitpoints_cap;
    int _power;
    int _power_cap;
    int _storage_capacity;
    int _efficiency; //extraction multiplier, how efficiently it mines
    int _reliability; //chance that it will extract an element (from 0 - 10000, where 10000 = 100.00%)
    int _storage[MAX_ELEMENTS];
    int _current_total_storage;
    spCelestialBody _host;
    int _max_temp;
    int _AP_cost;
    int _damage[4];
};