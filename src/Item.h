/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"

//declare smart pointer
DECLARE_SMART(Item, spItem);

using namespace oxygine;

class Item : public Actor
{
  public:
	  Item();

	  void init();

  private:
    
};