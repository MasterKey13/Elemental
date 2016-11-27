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
      int size,
      std::string name,
      std::string desc,
      std::string brand,
      int hitpoints
    );

    void init(std::string ID);

    void log();

    //SETTERS
    void setID(std::string ID);
    void setSize(int size);
    void setName(std::string name);
    void setDescription(std::string desc);
    void setBrand(std::string brand);
    void setHitPoints(int hitpoints);
    void setHitPointsMax(int hitpoints_cap);
    void setComposition(int element, int abundance);
    void setCompositionDefault();

    //GETTERS
    std::string getID();
    int getSize();
    std::string getName();
    std::string getDescription();
    std::string getBrand();
    int getHitPoints();
    int getHitPointsMax();
    int getComposition(int element);

  private:
    std::string _itemID;
    int _size;
    std::string _name;
    std::string _desc;
    std::string _brand;
    int _hitpoints;
    int _hitpoints_max;
    int _composition[MAX_ELEMENTS];
};