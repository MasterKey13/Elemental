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

class Item : public Actor
{
  public:
	  Item();

    void init(
      int ID,
      int size,
      bool craftable = false,
      std::string name = "",
      std::string desc = "",
      std::string brand = "");

    void initByID(int ID);

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

    //GETTERS
    int getID();
    std::string getName();
    std::string getDescription();
    std::string getBrand();
    int getSize();
    int getComposition(int element);
    bool getCraftable();

  private:
    int _itemID;
    std::string _name;
    std::string _desc;
    std::string _brand;
    int _size;
    int _composition[120];
    bool _craftable;
};