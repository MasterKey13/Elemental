/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"

#include "ship.h"

using namespace oxygine;

DECLARE_SMART(Ship, spShip);

class CelestialBody : public Actor
{
  public:
    CelestialBody();

	  void init();

    //SETTERS
    void setRadius(int radius);
    void setMass(int mass);
    void setSurfaceTemp(int temp);
    void setEffectiveTemp(int temp);
    void setComposition(int element, int abundance);
    void setCompositionDefault();
    void setAtmosphereComposition(int element, int abundance);
    void setAtmosphereCompositionDefault();
   
    //GETTERS
    int getRadius();
    int getMass();
    int getSurfaceTemp();
    int getEffectiveTemp();
    int getComposition(int element);
    int getAtmosphereComposition(int element);

  private:
    int _radius;
    int _mass;
    int _surface_temp;
    int _effective_temp;
    int _composition[120];
    int _atmosphere_composition[120];

    //TODO: implement getters/setters and stuff for this later
    spShip* _ships[];
};