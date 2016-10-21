/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "weapon.h"
#include "item.h"

Weapon::Weapon()
{

}

//! Initialize a custom weapon with given parameters
/*!
\param ID ID of the item (weapon)
\param size size of the weapon
\param hitpoints the amount of hitpoints the weapon starts with
\param hitpoints_cap the maximum amount of hitpoints
\param ballistic_dmg the amount of ballistic damage the weapon deals
\param electrical_dmg the amount of electrical damage the weapon deals
\param radioactive_dmg the amount of radioactive damage the weapon deals
\param chemical_dmg the amount of chemical damage the weapon deals
\param name name of the item (weapon)
\param desc description of the item (weapon)
\param brand the brand name of the weapon
\param craftable whether the item is craftable
*/
void Weapon::init(
  int ID, 
  int size,
  int hitpoints, 
  int hitpoints_cap,
  bool craftable,
  int ballistic_dmg,
  int electrical_dmg,
  int radioactive_dmg,
  int chemical_dmg,
  std::string name, 
  std::string desc,
  std::string brand)
{
  setID(ID);
  setName(name);
  setSize(size);
  setCompositionDefault();

  if (brand.length() > 0)
  {
    setBrand(brand);
  }

  setCraftable(craftable);

  log();
}

void Weapon::initByID(int ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/weapons.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value weapons = value["weapons"];

  //go through the json file and find the weapon by ID
  for (int i = 0; i < weapons.size(); i++)
  {
    if (weapons[i]["id"].asInt() == ID)
    {
      //initialize the weapon
      init(
        ID,
        weapons[i]["size"].asInt(),
        weapons[i]["hitpoints"].asInt(),
        weapons[i]["hitpoints"].asInt(),
        weapons[i]["brand"].asCString(),
        weapons[i]["ballistic_dmg"].asInt(),
        weapons[i]["electrical_dmg"].asInt(),
        weapons[i]["radioactive_dmg"].asInt(),
        weapons[i]["chemical_dmg"].asInt(),
        weapons[i]["name"].asCString()
      );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, weapons[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

void Weapon::log()
{
  log::messageln("\n[WEAPON]\nID: %d\nName: %s\nSize: %d\nBrand: %s\n",
    getID(),
    getName().c_str(),
    getSize(),
    getBrand().c_str());
}

//! Return the amount of damage the weapon deals for the given damage type
/*!
\param damage_type the damage type to return damage amount for
*/
int Weapon::getDamage(DamageType damage_type)
{
  return _damage[damage_type];
}

//! Set the amount of damage the weapon deals for given damage type
/*!
\param damage_type the damage type for which to the set the damage amount
\param damage the amount of damage it deals
*/
void Weapon::setDamage(DamageType damage_type, int damage)
{
  _damage[damage_type] = damage;
}
