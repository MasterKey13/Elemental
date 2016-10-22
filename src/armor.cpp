/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "armor.h"
#include "item.h"

Armor::Armor()
{

}

//! Manual initalization function for custom armor pieces used for debugging
/*!
  \param ID unique item ID
  \param size size of the item
  \param craftable whether the item is craftable
  \param ballistic_res ballistic resistance
  \param electical_res electrical resistance
  \param chemical_res chemical resistance
  \param name name of the item
  \param desc description of the armor piece
  \param brand brand name
*/
void Armor::init(
  int ID,
  int size,
  bool craftable,
  int ballistic_res,
  int electrical_res,
  int radioactive_res,
  int chemical_res,
  std::string name,
  std::string desc,
  std::string brand)
{
  setID(ID);
  setName(name);
  setSize(size);
  setCompositionDefault();
  setDescription(desc);

  setDamageResistance(Ballistic, ballistic_res);
  setDamageResistance(Electrical, electrical_res);
  setDamageResistance(Radioactive, radioactive_res);
  setDamageResistance(Chemical, chemical_res);

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
void Armor::initByID(int ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/armors.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value armors = value["armors"];

  //go through the json file and find the item by ID
  for (int i = 0; i < armors.size(); i++)
  {
    if (armors[i]["id"].asInt() == ID)
    {
      //initialize the item
      init(
        ID,
        armors[i]["size"].asInt(),
        armors[i]["craftable"].asBool(),
        armors[i]["ballistic_res"].asInt(),
        armors[i]["electrical_res"].asInt(),
        armors[i]["radioactive_res"].asInt(),
        armors[i]["chemical_res"].asInt(),
        armors[i]["name"].asCString(),
        armors[i]["description"].asCString(),
        armors[i]["brand"].asCString()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, armors[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

void Armor::log()
{
  log::messageln("\n[ARMOR]\nID: %d\nName: %s\nDescription: %s\nSize: %d\nBrand: %s\nBallRes: %d\nElectrRes: %d\nRadRes: %d\nChemRes: %d\n",
    getID(),
    getName().c_str(),
    getDescription().c_str(),
    getSize(),
    getBrand().c_str(),
    getDamageResistance(Ballistic),
    getDamageResistance(Electrical),
    getDamageResistance(Radioactive),
    getDamageResistance(Chemical));
}

int Armor::getDamageResistance(DamageType type)
{
  return _damage_resistance[type];
}

void Armor::setDamageResistance(DamageType type, int resistance)
{
  _damage_resistance[type] = resistance;
}