/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "json/json.h"
#include "Item.h"

//declare smart pointer
DECLARE_SMART(Item, spItem);

using namespace oxygine;

class ItemContainer : public Item
{
public:
  ItemContainer();

private:

};