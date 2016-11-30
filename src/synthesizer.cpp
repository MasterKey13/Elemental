/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "synthesizer.h"

Synthesizer::Synthesizer()
{
  
}

//! Initialize a container with given parameters
void Synthesizer::init(int capacity)
{
  
}

//! Initialize a synthesizer by ID (load from item definition file synthesizers.json)
/*!
\param ID ID of the item
*/
void Synthesizer::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/synthesizers.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["synthesizers"];

  //go through the json file and find the item by ID
  for (size_t  i = 0; i < items.size(); i++)
  {
    if (ID.compare(items[i]["id"].asCString()) == 0)
    {
      //initialize the item
      Item::init(
        ID,
        items[i]["volume"].asFloat(),
        items[i]["weight"].asFloat(),
        items[i]["name"].asCString(),
        items[i]["desc"].asCString(),
        items[i]["brand"].asCString(),
        items[i]["hitpoints"].asInt()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

//! Decompose an item into its most basic elements
/*!
\param item smart pointer to item which to decompose
*/
void Synthesizer::decomposeItem(spItem item)
{
  //TODO: reimplement this
}

//! Synthesize a new item based on item ID and place it in the ship's inventory
/*!
\param ID ID of item to synthesize
*/
void Synthesizer::synthesizeItem(std::string ID)
{
  //TODO: implement this
}
