/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "json/json.h"

//declare smart pointer
DECLARE_SMART(Item, spItem);

using namespace oxygine;

#define MAX_ELEMENTS 50

class Item : public Actor
{
  public:
	  Item();

    void init(
      std::string ID,
      float volume,
      float weight,
      std::string name,
      std::string desc,
      std::string brand
    );

    void init(std::string ID);

    void log();

    //SETTERS
    void setID(std::string ID);
    void setVolume(float volume);
    void setWeight(float weight);
    void setName(std::string name);
    void setDescription(std::string desc);
    void setBrand(std::string brand);
    void setComposition(int element, int abundance);
    void setCompositionDefault();

    //GETTERS
    std::string getID();
    float getVolume();
    float getWeight();
    std::string getName();
    std::string getDescription();
    std::string getBrand();
    int getComposition(int element);

  private:
    std::string _itemID;
    float _volume;
    float _weight;
    std::string _name;
    std::string _desc;
    std::string _brand;
    int _composition[MAX_ELEMENTS];
};