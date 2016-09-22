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
DECLARE_SMART(CelestialBody, spCelestialBody);

class CelestialBody : public Actor
{
  public:
    CelestialBody();

	  void init(
      float radius,
      float mass, 
      int temp, //in Kelvin
      std::string type //types = "Planet", "Star", "White Dwarf", "Black Hole", "Moon"
    );

    void log();

    //SETTERS
    void setRadius(float radius);
    void setMass(float mass);
    void setTemp(int temp);
    void setType(std::string type); 
    void setComposition(int element, int abundance);
    void setCompositionDefault();
    void setAtmosphereComposition(int element, int abundance);
    void setAtmosphereCompositionDefault();
   
    //GETTERS
    float getRadius();
    float getMass();
    int getTemp();
    std::string getType();
    int getComposition(int element);
    int getAtmosphereComposition(int element);

    //randomized generation functions
    void generateStar();
    void generatePlanet(int distance);

  private:
    float _radius;
    float _mass;
    int _temp;
    std::string _type;
    int _composition[120];
    int _atmosphere_composition[120];

    //TODO: implement getters/setters for orbiting star/planets/moons
    spCelestialBody* _orbit[10];
    spCelestialBody* _partners[2];
    int _orbit_count;
    int _partner_count;

    //TODO: implement getters/setters for ships later
    spShip* _ships[10];
    int _ship_count;

    //TODO: implement getters/setters and validation for mines
    spMine* _mines[10];
    int _mine_count;

    //TODO: implement getters/setters and validation for settlements
    spSettlement* _settlements[10];
    int _settlement_count;
};