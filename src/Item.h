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
      int chemical_dmg,
      int ballistic_res,
      int electrical_res,
      int chemical_res,
      int efficiency,
      int reliability,
      int storage_capacity,
      int max_temp,
      bool craftable,
      bool isEquipment,
      bool isWeapon,
      bool isArmor,
      bool isBattery,
      bool isEngine,
      bool isHull,
      bool isMine
      );

    void init(int ID);

    void log();

    //SETTERS
    void setID(int ID);
    void setSize(int size);
    void setName(std::string name);
    void setDescription(std::string desc);
    void setBrand(std::string brand);
    void setHitPoints(int hitpoints);
    void setHitPointsCap(int hitpoints_cap);
    void setPower(int power);
    void setPowerCap(int power_cap);
    void setDamage(DamageType damage_type, int damage_resistance);
    void setDamageDefault();
    void setDamageResistance(DamageType type, int resistance);
    void setDamageResistanceDefault();
    void setStorageCapacity(int cap);
    void setStorage(int element, int amount);
    void setEfficiency(int efficiency);
    void setReliability(int reliability);
    void setStorageDefault();
    void setCurrentTotalStorage(int amount);
    void setHostBody(spCelestialBody host);
    void setMaxTemp(int temp);
    void setCraftable(bool craftable);
    void setComposition(int element, int abundance);
    void setCompositionDefault();

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

    //type of item (equipment, weapon, battery, engine, hull, mine or a combination of any)
    bool isEquipment();
    bool isWeapon();
    bool isArmor();
    bool isBattery();
    bool isEngine();
    bool isHull();
    bool isMine();

  private:
    int _itemID;
    int _size;
    std::string _name;
    std::string _desc;
    std::string _brand;
    int _hitpoints;
    int _hitpoints_cap;
    int _power;
    int _power_cap;
    int _damage[3];
    int _damage_resistance[3];
    int _efficiency;
    int _reliability;
    int _storage_capacity;
    int _storage[MAX_ELEMENTS];
    int _current_total_storage;
    int _max_temp;

    int _action_point_cost;
    int _composition[MAX_ELEMENTS];
    spCelestialBody _host;

    bool _isCraftable;
    bool _isEquipment;
    bool _isWeapon;
    bool _isArmor;
    bool _isBattery;
    bool _isEngine;
    bool _isHull;
    bool _isMine;
};