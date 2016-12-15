/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"

#include <vector>

#include "item.h"
#include "armor.h"
#include "target.h"
#include "battery.h"
#include "engine.h"
#include "equipment.h"
#include "synthesizer.h"
#include "resources.h"

//declare smart pointer
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Armor, spArmor);
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Engine, spEngine);
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Synthesizer, spSynthesizer);

using namespace oxygine;

class Hull : public Item, public Target
{
  public:
    Hull();

    void init(
      int ballistic_res, 
      int electrical_res, 
      int chemical_res,
      int max_equip
      );

    void init(std::string ID);

    //SETTERS
    void setBattery(spBattery battery);
    void setEngine(spEngine engine);
    void setSynthesizer(spSynthesizer synth);
    void setVolumeRemaining(float volume);
    void setMaxEquip(int max);

    //GETTERS
    std::vector<spItem> getInventory();
    std::vector<spEquipment> getEquipment();
    spBattery getBattery();
    spEngine getEngine();
    spSynthesizer getSynthesizer();
    float getVolumeRemaining();
    int getMaxEquip();

    void addEquipment(spEquipment eq);

  private:
    std::vector<spItem> _inventory;
    std::vector<spEquipment> _equipment;
    spBattery _battery;
    spEngine _engine;
    spSynthesizer _synthesizer;
    float _volume_remaining;
    int _max_equip;
    spSprite _sprite;
};