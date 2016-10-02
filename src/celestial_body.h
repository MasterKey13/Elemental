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

#define MAX_ELEMENTS 50
#define SUN_RADIUS 695700 //KM
#define EARTH_RADIUS 6371 //KM


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
    void setDistanceFromCenter(int distance);
    void setParentBody(spCelestialBody parent);
   
    //GETTERS
    float getRadius();
    float getMass();
    int getTemp();
    std::string getType();
    int getComposition(int element);
    int getAtmosphereComposition(int element);
    int getDistanceFromCenter();
    int getOrbitCount();
    spCelestialBody getParentBody();

    //randomized generation functions
    void generateStar();
    void generatePlanet(int distance);
    void generateMoon(float mass, int temp, float radius, int distance);

    void generateTerrestrialDistribution();

  private:
    float _radius;
    float _mass;
    int _temp;
    std::string _type;
    int _distance_from_center;
    int _composition[MAX_ELEMENTS];
    int _atmosphere_composition[MAX_ELEMENTS];

    //Orbit-related methods and variables
    spCelestialBody _orbit[100];
    spCelestialBody _parent;
    int _orbit_count;
    void addOrbiter(spCelestialBody orbiter);

    //TODO: implement getters/setters for ships later
    spShip _ships[10];
    int _ship_count;

    //TODO: implement getters/setters and validation for mines
    spMine _mines[100];
    int _mine_count;

    //TODO: implement getters/setters and validation for settlements
    spSettlement _settlements[10];
    int _settlement_count;
};