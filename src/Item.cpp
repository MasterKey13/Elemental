/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "item.h"

Item::Item()
{
  setID(0);
  setSize(0);
  setName("");
  setDescription("");
  setBrand("");
  setHitPoints(0);
  setHitPointsCap(0);
  setPower(0);
  setPowerCap(0);
  setDamageDefault();
  setDamageResistanceDefault();
  setEfficiency(0);
  setReliability(0);
  setStorageCapacity(0);
  setCurrentTotalStorage(0);
  setStorageDefault();
  setMaxTemp(0);
  setCraftable(false);
  setHostBody(nullptr);

  _isEquipment = false;
  _isWeapon = false;
  _isBattery = false;
  _isEngine = false;
  _isHull = false;
  _isMine = false;

  setCompositionDefault();
}

//! Initialize an item with given parameters
/*!
\param ID ID of the item
\param size size of the item
\param name name of the item
\param desc description of the item
\param brand the brand name of the item
\param hitpoints the amount of hitpoints the item has (health)
\param hitpoints_cap maximum amount of hitpoints
\param power battery power this item provides
\param power_cap maximum amount of battery power
\param ballistic_dmg amount of ballistic damage this item does
\param electrical_dmg amount of electrical damage this item does
\param chemical_dmg amount of chemical damage this item does
\param ballistic_res resistance to ballistic damage of this item
\param electrical_res resistance to electrical damage of this item
\param chemical_res resistance to chemical damage of this item
\param efficiency the mining efficiency of this item
\param reliability how reliably this item can mine for elements
\param storage_capacity the maximum amount of elements this item can store
\param max_temp maximum temperature this item can endure
\param craftable whether the item is craftable
\param isEquipment whether the item can be used as an equipment piece
\param isWeapon whether the item can be used as a weapon
\param isBattery whether the item can be used as a ship battery
\param isEngine whether the item can be used as a ship engine
\param isHull whether the item can be used as a ship hull
\param isMine whether the item can be used as a planetary mine
*/
void Item::init(
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
  bool isCraftable,
  bool isEquipment,
  bool isWeapon,
  bool isBattery,
  bool isEngine,
  bool isHull,
  bool isMine
  )
{
  setID(ID);
  setSize(size);

  setName(name);
  setDescription(desc);
  setBrand(brand);

  setHitPoints(hitpoints);
  setHitPointsCap(hitpoints_cap);

  setPower(power);
  setPowerCap(power_cap);

  setDamage(Ballistic, ballistic_dmg);
  setDamage(Electrical, electrical_dmg);
  setDamage(Chemical, chemical_dmg);

  setDamageResistance(Ballistic, ballistic_res);
  setDamageResistance(Electrical, electrical_res);
  setDamageResistance(Chemical, chemical_res);

  setEfficiency(efficiency);
  setReliability(reliability);
  setStorageCapacity(storage_capacity);
  setMaxTemp(max_temp);

  setCraftable(isCraftable);
  
  _isEquipment = isEquipment;
  _isWeapon = isWeapon;
  _isBattery = isBattery;
  _isEngine = isEngine;
  _isHull = isHull;
  _isMine = isMine;

  if (brand.length() > 0)
  {
    setBrand(brand);
  }

  log();
}

//! Initialize an item by ID (load from item definition file items.json)
/*!
\param ID ID of the item
*/
void Item::init(int ID)
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
        items[i]["desc"].asCString(),
        items[i]["brand"].asCString(),
        items[i]["hitpoints"].asInt(),
        items[i]["hitpoints"].asInt(),
        items[i]["power"].asInt(),
        items[i]["power"].asInt(),
        items[i]["ballistic_dmg"].asInt(),
        items[i]["electrical_dmg"].asInt(),
        items[i]["chemical_dmg"].asInt(),
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt(),
        items[i]["efficiency"].asInt(),
        items[i]["reliability"].asInt(),
        items[i]["storage_capacity"].asInt(),
        items[i]["max_temp"].asInt(),
        items[i]["craftable"].asBool(),
        items[i]["isEquipment"].asBool(),
        items[i]["isWeapon"].asBool(),
        items[i]["isBattery"].asBool(),
        items[i]["isEngine"].asBool(),
        items[i]["isHull"].asBool(),
        items[i]["isMine"].asBool()
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
  log::messageln("\n[ITEM]\nID: %d\nName: %s\nDescription: %s\nSize: %d\nBrand: %s\nCraftable: %s\n",
    getID(),
    getName().c_str(),
    getDescription().c_str(),
    getSize(),
    getBrand().c_str(),
    (getCraftable() ? "true" : "false"));
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
  for (int i = 0; i < MAX_ELEMENTS; i++)
  {
    _composition[i] = 0;
  }
}

void Item::setCraftable(bool craftable)
{
  _isCraftable = craftable;
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
  return _isCraftable;
}

int Item::getDamageResistance(DamageType type)
{
  return _damage_resistance[type];
}

int Item::getHitPoints()
{
  return _hitpoints;
}

int Item::getHitPointsCap()
{
  return _hitpoints_cap;
}

int Item::getPower()
{
  return _power;
}

int Item::getPowerCap()
{
  return _power_cap;
}

void Item::setDamageResistance(DamageType type, int resistance)
{
  _damage_resistance[type] = resistance;
}

void Item::setDamageResistanceDefault()
{
  setDamageResistance(Ballistic, 0);
  setDamageResistance(Electrical, 0);
  setDamageResistance(Chemical, 0);
}

void Item::setHitPoints(int hitpoints)
{
  _hitpoints = hitpoints;
}

void Item::setHitPointsCap(int hitpoints_cap)
{
  _hitpoints_cap = hitpoints_cap;
}

void Item::setPower(int power)
{
  _power = power;
}

void Item::setPowerCap(int power_cap)
{
  _power_cap = power_cap;
}

void Item::setStorageCapacity(int cap)
{
  _storage_capacity = cap;
}

void Item::setStorage(int element, int amount)
{
  _storage[element] = amount;
}

void Item::setEfficiency(int efficiency)
{
  _efficiency = efficiency;
}

void Item::setReliability(int reliability)
{
  _reliability = reliability;
}

void Item::setStorageDefault()
{
  for (int i = 0; i < MAX_ELEMENTS; i++)
  {
    _storage[i] = 0;
  }

  setCurrentTotalStorage(0);
}

void Item::setCurrentTotalStorage(int amount)
{
  _current_total_storage = amount;
}

void Item::setHostBody(spCelestialBody host)
{
  _host = host;
}

void Item::setMaxTemp(int temp)
{
  _max_temp = temp;
}

int Item::getStorageCapacity()
{
  return _storage_capacity;
}

int Item::getStorage(int element)
{
  return _storage[element];
}

int Item::getEfficiency()
{
  return _efficiency;
}

int Item::getReliability()
{
  return _reliability;
}

int Item::getCurrentStorage()
{
  return _current_total_storage;
}

//! Extracts elements from its host body based on its attributes
void Item::extract()
{
  if (getHostBody() != NULL)
  {
    /*
    for every element go over the host body's composition
    for that element, and using the mine's reliability
    and efficiency attributes add those composition amounts
    to the mine's storage
    */
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
      for (int j = 0; j < getHostBody()->getComposition(i); j++)
      {
        int extractGen = rand() % 10000;

        //determine if the mine will mine this element (by reliability attribute)
        //and check if mine has enough storage space
        if ((extractGen <= getReliability()) &&
          ((getStorageCapacity() - getCurrentStorage()) >= getEfficiency()))
        {
          setStorage(i, getStorage(i) + getEfficiency());
          setCurrentTotalStorage(getCurrentStorage() + getEfficiency());
        }
      }

      log::messageln("Extracted %d of element [%d] from host body",
        getStorage(i), i);
    }

    log::messageln("Mine capacity: %d/%d",
      getCurrentStorage(), getStorageCapacity());
  }
}

bool Item::isEquipment()
{
  return _isEquipment;
}

bool Item::isWeapon()
{
  return _isWeapon;
}

bool Item::isBattery()
{
  return _isBattery;
}

bool Item::isEngine()
{
  return _isEngine;
}

bool Item::isHull()
{
  return _isHull;
}

bool Item::isMine()
{
  return _isMine;
}

//! Returns a smart pointer to the CelestialBody on which it is installed
spCelestialBody Item::getHostBody()
{
  return _host;
}

int Item::getMaxTemp()
{
  return _max_temp;
}

//! Return the amount of damage the weapon deals for the given damage type
/*!
\param damage_type the damage type to return damage amount for
*/
int Item::getDamage(DamageType damage_type)
{
  return _damage[damage_type];
}

//! Set the amount of damage the weapon deals for given damage type
/*!
\param damage_type the damage type for which to the set the damage amount
\param damage the amount of damage it deals
*/
void Item::setDamage(DamageType damage_type, int damage)
{
  _damage[damage_type] = damage;
}

void Item::setDamageDefault()
{
  setDamage(Ballistic, 0);
  setDamage(Electrical, 0);
  setDamage(Chemical, 0);
}
