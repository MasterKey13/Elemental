/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "item.h"

Item::Item()
{
  //set all values to default (0, false, empty strings and nullptrs)
  setID(0);
  setSize(0);
  setName("");
  setDescription("");
  setBrand("");
  setHitPoints(0);
  setHitPointsCap(0);
  setActionSlots(0);
  setActionSlotsCap(0);
  setEvasion(0);
  setPower(0);
  setPowerCap(0);
  setDamageDefault();
  setDamageResistanceDefault();
  setDamageAbsorbtion(0);
  setEfficiency(0);
  setReliability(0);
  setStorageCapacity(0);
  setCurrentTotalStorage(0);
  setStorageDefault();
  setMaxTemp(0);
  setCraftable(false);
  setHostBody(nullptr);
  setArmorPiece(nullptr);

  _isEquipment = false;
  _isWeapon = false;
  _isArmor = false;
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
\param battery_power battery power this item provides
\param action_slots action slots this item provides
\param evasion how much evasion this item provides
\param ballistic_dmg amount of ballistic damage this item does
\param electrical_dmg amount of electrical damage this item does
\param chemical_dmg amount of chemical damage this item does
\param ballistic_res resistance to ballistic damage of this item
\param electrical_res resistance to electrical damage of this item
\param chemical_res resistance to chemical damage of this item
\param damage_absorbtion maximum amount of damage the armor item can absorb
\param mining_efficiency the mining efficiency of this item
\param mining_reliability how reliably this item can mine for elements
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
  int battery_power,
  int action_slots,
  int evasion,
  int ballistic_dmg,
  int electrical_dmg,
  int chemical_dmg,
  int ballistic_res,
  int electrical_res,
  int chemical_res,
  int damage_absorbtion,
  int mining_efficiency,
  int mining_reliability,
  int storage_capacity,
  int max_temp,
  bool isCraftable,
  bool isEquipment,
  bool isWeapon,
  bool isArmor,
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
  setHitPointsCap(hitpoints);

  setPower(battery_power);
  setPowerCap(battery_power);

  setActionSlots(action_slots);
  setActionSlotsCap(action_slots);
  setEvasion(evasion);

  setDamage(Ballistic, ballistic_dmg);
  setDamage(Electrical, electrical_dmg);
  setDamage(Chemical, chemical_dmg);
  setDamageResistance(Ballistic, ballistic_res);
  setDamageResistance(Electrical, electrical_res);
  setDamageResistance(Chemical, chemical_res);
  setDamageAbsorbtion(damage_absorbtion);

  setEfficiency(mining_efficiency);
  setReliability(mining_reliability);
  setStorageCapacity(storage_capacity);
  setMaxTemp(max_temp);

  setCraftable(isCraftable);
  
  _isEquipment = isEquipment;
  _isWeapon = isWeapon;
  _isArmor = isArmor;
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
        items[i]["power"].asInt(),
        items[i]["action_slots"].asInt(),
        items[i]["evasion"].asInt(),
        items[i]["ballistic_dmg"].asInt(),
        items[i]["electrical_dmg"].asInt(),
        items[i]["chemical_dmg"].asInt(),
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt(),
        items[i]["damage_absorbtion"].asInt(),
        items[i]["efficiency"].asInt(),
        items[i]["reliability"].asInt(),
        items[i]["storage_capacity"].asInt(),
        items[i]["max_temp"].asInt(),
        items[i]["craftable"].asBool(),
        items[i]["isEquipment"].asBool(),
        items[i]["isWeapon"].asBool(),
        items[i]["isArmor"].asBool(),
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
  log::messageln("ID: %d\nSize: %d\nName: %s\nDescription: %s\nBrand: %s\nHP: %d/%d",
    getID(), getSize(), getName().c_str(), getDescription().c_str(), getBrand().c_str(), getHitPoints(), getHitPointsCap());

  if (isBattery())
  {
    log::messageln("Battery Power: %d/%d", getPower(), getPowerCap());
  }

  if (isWeapon() || isBattery() || isEquipment() || isEngine() || isHull() || isArmor())
  {
    log::messageln("Damages: %d | %d | %d", getDamage(Item::DamageType::Ballistic), getDamage(Item::DamageType::Electrical), getDamage(Item::DamageType::Chemical));
    log::messageln("Resists: %d | %d | %d", getDamageResistance(Item::DamageType::Ballistic), getDamageResistance(Item::DamageType::Electrical), getDamageResistance(Item::DamageType::Chemical));
    log::messageln("Absorbtion: %d", getDamageAbsorbtion());
  }

  if (isMine())
  {
    log::messageln("Mining efficiency: %d", getEfficiency());
    log::messageln("Mining reliability: %d", getReliability());
    log::messageln("Mining storage cap: %d", getStorageCapacity());
    log::messageln("Max temperature: %d", getMaxTemp());
  }

  log::messageln("");
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

int Item::getDamageAbsorbtion()
{
  return _damage_absorbtion;
}

int Item::getHitPoints()
{
  return _hitpoints;
}

int Item::getHitPointsCap()
{
  return _hitpoints_cap;
}

int Item::getActionSlots()
{
  return _action_slots;
}

int Item::getActionSlotsCap()
{
  return _action_slots_cap;
}

int Item::getEvasion()
{
  return _evasion;
}

int Item::getPower()
{
  return _battery_power;
}

int Item::getPowerCap()
{
  return _battery_power_cap;
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

void Item::setDamageAbsorbtion(int absorb)
{
  _damage_absorbtion = absorb;
}

void Item::setHitPoints(int hitpoints)
{
  _hitpoints = hitpoints;
}

void Item::setHitPointsCap(int hitpoints_cap)
{
  _hitpoints_cap = hitpoints_cap;
}

void Item::setActionSlots(int action_slots)
{
  _action_slots = action_slots;
}

void Item::setActionSlotsCap(int action_slots_cap)
{
  _action_slots_cap = action_slots_cap;
}

void Item::setEvasion(int evasion)
{
  _evasion = evasion;
}

void Item::setPower(int power)
{
  _battery_power = power;
}

void Item::setPowerCap(int power_cap)
{
  _battery_power_cap = power_cap;
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
  _mining_efficiency = efficiency;
}

void Item::setReliability(int reliability)
{
  _mining_reliability = reliability;
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

void Item::setArmorPiece(spItem armor)
{
  //only weapons, equipment, batteries, engines and hulls can have armor pieces
  if (isWeapon() || isEquipment() || isBattery() || isEngine() || isHull())
  {
    _armor_piece = armor;
  }
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
  return _mining_efficiency;
}

int Item::getReliability()
{
  return _mining_reliability;
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

bool Item::isArmor()
{
  return _isArmor;
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

spItem Item::getArmorPiece()
{
  if (_armor_piece)
  {
    return _armor_piece;
  }
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
