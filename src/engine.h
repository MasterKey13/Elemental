/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "armor.h"
#include "target.h"
#include "resources.h"

//declare smart pointer
DECLARE_SMART(Engine, spEngine);
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Engine : public Item, public Target
{
  public:
    Engine();

    void init(int evasion, int ap_threshold, float max_weight);
    void init(std::string ID);

    //SETTERS
    void setEvasion(int evasion);
    void setAPThreshold(int threshold);
    void setMaxWeight(float weight);
    void setAPEscapePool(int pool);

    //GETTERS
    int getEvasion();
    int getAPThreshold();
    float getMaxWeight();
    int getAPEscapePool();
    spSprite getSprite();

  private:
    int _evasion;
    int _ap_threshold;
    float _max_weight;
    spSprite _sprite;
    int _ap_escape_pool;
};