/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "ship.h"
#include "mine.h"
#include "settlement.h"

using namespace oxygine;

DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Mine, spMine);
DECLARE_SMART(Settlement, spSettlement);

class CelestialBody : public Actor
{
  public:
    CelestialBody();

	  void init(
      int radius,
      int mass,
      int surface_temp,
      int effective_temp,
      std::string type
    );

    void log();

    //SETTERS
    void setRadius(int radius);
    void setMass(int mass);
    void setSurfaceTemp(int temp);
    void setEffectiveTemp(int temp);
    void setType(std::string type);
    void setComposition(int element, int abundance);
    void setCompositionDefault();
    void setAtmosphereComposition(int element, int abundance);
    void setAtmosphereCompositionDefault();
   
    //GETTERS
    int getRadius();
    int getMass();
    int getSurfaceTemp();
    int getEffectiveTemp();
    std::string getType();
    int getComposition(int element);
    int getAtmosphereComposition(int element);

  private:
    int _radius;
    int _mass;
    int _surface_temp;
    int _effective_temp;
    std::string _type;
    int _composition[120];
    int _atmosphere_composition[120];

    //TODO: implement getters/setters for this later
    spShip* _ships[10];

    //TODO: implement getters/setters and validation for mines
    spMine* _mines[10];

    //TODO: implement getters/setters and validation for settlements
    spSettlement* _settlements[10];
};