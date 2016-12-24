/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "npc.h"

NPC::NPC()
{
  setID("");
  setHostility(0);
  setBravery(0);
}

void NPC::init(
  std::string ID,
  int hostility, 
  int bravery)
{
  setID(ID);
  setHostility(hostility);
  setBravery(bravery);
}

void NPC::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/npcs.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value npcs = value["npcs"];

  //go through the json file and find the item by ID
  for (size_t i = 0; i < npcs.size(); i++)
  {
    if (ID.compare(npcs[i]["id"].asString()) == 0)
    {
      //initialize the character
      Character::init(
        npcs[i]["first_name"].asString(),
        npcs[i]["last_name"].asString(),
        npcs[i]["nickname"].asString(),
        npcs[i]["race"].asString(),
        npcs[i]["faction"].asString(),
        npcs[i]["intelligence"].asInt(),
        npcs[i]["discourse"].asInt(),
        npcs[i]["strength"].asInt()
        );

      //initialize the NPC
      init(
        ID,
        npcs[i]["hostility"].asInt(),
        npcs[i]["bravery"].asInt()
        );
    }
  }

  log::messageln("Created %s", getID().c_str());
}

void NPC::setID(std::string ID)
{
  _ID = ID;
}

void NPC::setHostility(int hostility)
{
  _hostility = hostility;
}

void NPC::setBravery(int bravery)
{
  _bravery = bravery;
}

std::string NPC::getID()
{
  return _ID;
}

int NPC::getHostility()
{
  return _hostility;
}

int NPC::getBravery()
{
  return _bravery;
}
