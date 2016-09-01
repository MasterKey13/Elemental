/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"

#include <string>

//declare smart pointer
DECLARE_SMART(Item, spItem);

using namespace oxygine;

class Item : public Actor
{
  public:
	  Item();

    void init(
      int ID,
      std::string name,
      int size,
      int rarity,
      std::string brand = "",
      std::string model = "");

    void log();

    //SETTERS
    void setID(int ID);
    void setName(std::string name);
    void setBrand(std::string brand);
    void setModel(std::string model);
    void setSize(int size);
    void setComposition(int element, int abundance);
    void setCompositionDefault(); //sets composition to all 0s
    void setRarity(int rarity);

    //GETTERS
    int getID();
    std::string getName();
    std::string getBrand();
    std::string getModel();
    int getSize();
    int getComposition(int element);
    int getRarity();

  private:
    int _itemID;
    std::string _name;
    std::string _brand;
    std::string _model;
    int _size;
    int _composition[120];
    int _rarity;
};