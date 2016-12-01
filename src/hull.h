/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"

#include <vector>

#include "item.h"
#include "armor.h"
#include "damageable.h"
#include "battery.h"
#include "engine.h"
#include "equipment.h"
#include "synthesizer.h"

//declare smart pointer
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Armor, spArmor);
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Engine, spEngine);
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Synthesizer, spSynthesizer);

using namespace oxygine;

class Hull : public Item, public Damageable
{
  public:
    Hull();

    void init(
      int ballistic_res, 
      int electrical_res, 
      int chemical_res
      );

    void init(std::string ID);

    //SETTERS
    void setArmorPiece(spArmor armor);

    void setBattery(spBattery battery);
    void setEngine(spEngine engine);
    void setSynthesizer(spSynthesizer synth);

    void setVolumeRemaining(float volume);

    //GETTERS
    spArmor getArmorPiece();

    std::vector<spItem> getInventory();
    spBattery getBattery();
    spEngine getEngine();
    spSynthesizer getSynthesizer();

    float getVolumeRemaining();

  private:
    spArmor _armor_piece;

    std::vector<spItem> _inventory;
    std::vector<spEquipment> _equipment;
    spBattery _battery;
    spEngine _engine;
    spSynthesizer _synthesizer;

    float _volume_remaining = 0.0f;
};