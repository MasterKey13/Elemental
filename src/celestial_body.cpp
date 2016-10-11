/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "celestial_body.h"
#include <stdlib.h>
#include <time.h>  

CelestialBody::CelestialBody()
{
  
}

void CelestialBody::init(
  float radius,
  float mass,
  int temp,
  std::string type)
{
  setRadius(radius);
  setMass(mass);
  setTemp(temp);
  setType(type);

  setCompositionDefault();
  setAtmosphereCompositionDefault();

  log();
}

//Logs all relevant information for a celestial body
void CelestialBody::log()
{
  log::messageln("\n[CELESTIAL BODY]\nType: %s\nRadius: %.2f\nMass: %.2f\nTemp: %dK (%dC)\nDistance: %d\nMine Count: %d",
    this->getType().c_str(),
    this->getRadius(),
    this->getMass(),
    this->getTemp(),
    this->getTemp() - 274,
    this->getDistanceFromCenter(),
    this->getMineCount());

  int totalComposition = 0;

  int i = 0, j = 0;
  while(i < MAX_ELEMENTS)
  {
    if (getComposition(i) != 0)
    {
      totalComposition = totalComposition + getComposition(i);
      log::message("[%d]%d", i, getComposition(i));

      if (j % 5 != 0)
      {
        log::message("\t\t");
      }
      else
      {
        log::message("\n");
      }

      j++;
    }

    i++;
  }

  if (this->getParentBody() != NULL)
  {
    log::messageln("PARENT MASS: %.2f\n", this->getParentBody()->getMass());
  }
  log::message("\n");
}

void CelestialBody::setRadius(float radius)
{
  _radius = radius;
}

void CelestialBody::setMass(float mass)
{
  _mass = mass;
}

void CelestialBody::setTemp(int temp)
{
  _temp = temp;
}

void CelestialBody::setType(std::string type)
{
  _type = type;
}

void CelestialBody::setComposition(int element, int abundance)
{
  if (element < MAX_ELEMENTS)
  {
    _composition[element] = abundance;
  }
}

void CelestialBody::setCompositionDefault()
{
  for (int i = 0; i < MAX_ELEMENTS; i++)
  {
    _composition[i] = 0;
  }
}

void CelestialBody::setAtmosphereComposition(int element, int abundance)
{
  if (element < MAX_ELEMENTS)
  {
    _atmosphere_composition[element] = abundance;
  }
}

void CelestialBody::setAtmosphereCompositionDefault()
{
  for (int i = 0; i < MAX_ELEMENTS; i++)
  {
    _atmosphere_composition[i] = 0;
  }
}

void CelestialBody::setDistanceFromCenter(int distance)
{
  _distance_from_center = distance;
}

void CelestialBody::setParentBody(spCelestialBody parent)
{
  _parent = parent;
}

float CelestialBody::getRadius()
{
  return _radius;
}

float CelestialBody::getMass()
{
  return _mass;
}

int CelestialBody::getTemp()
{
  return _temp;
}

std::string CelestialBody::getType()
{
  return _type;
}

int CelestialBody::getComposition(int element)
{
  return _composition[element];
}

int CelestialBody::getAtmosphereComposition(int element)
{
  return _atmosphere_composition[element];
}

int CelestialBody::getDistanceFromCenter()
{
  return _distance_from_center;
}

int CelestialBody::getOrbitCount()
{
  return _orbit_count;
}

int CelestialBody::getMineCount()
{
  return _mine_count;
}

void CelestialBody::addOrbiter(spCelestialBody orbiter)
{
  if (getOrbitCount() < MAX_ORBITERS)
  {
    _orbit[_orbit_count] = orbiter;
    _orbit_count++;
  }
}

void CelestialBody::addMine(spMine mine)
{
  if (getMineCount() < MAX_MINES)
  {
    _mines[_mine_count] = mine;
    _mine_count++;
  }
}

spCelestialBody CelestialBody::getParentBody()
{
  return _parent;
}

void CelestialBody::generateTerrestrialDistribution()
{
  //set to default at the start
  setCompositionDefault();
  setAtmosphereCompositionDefault();

  //create planet composition percentages
  int primary = rand() % 30 + 360; //36% - 39%
  int secondary = rand() % 30 + 220; //22% - 25%
  int tertiary = rand() % 20 + 180; //18% - 20%
  int quaternary = rand() % 20 + 130; //13% - 15%
  int remaining = 1000 - primary - secondary - tertiary - quaternary; //1% - 11%

  //primary distribution loop
  for (int p = 0; p < primary; p++)
  {
    //randomly distribute among elements id 5-8
    int element_index = rand() % 3 + 5;
    setComposition(element_index,
      getComposition(element_index) + 1);
  }

  //secondary distribution loop
  for (int s = 0; s < primary; s++)
  {
    //randomly distribute among elements id 10-16
    int element_index = rand() % 6 + 10;
    setComposition(element_index,
      getComposition(element_index) + 1);
  }

  //tertiary distribution loop
  for (int t = 0; t < primary; t++)
  {
    //randomly distribute among elements id 18-22
    int element_index = rand() % 4 + 18;
    setComposition(element_index,
      getComposition(element_index) + 1);
  }

  //quaternary  distribution loop
  for (int q = 0; q < quaternary; q++)
  {
    //randomly distribute among elements id 23-27
    int element_index = rand() % 4 + 23;
    setComposition(element_index,
      getComposition(element_index) + 1);
  }

  //remaining  distribution loop
  for (int r = 0; r < remaining; r++)
  {
    //randomly distribute among elements id 0-49
    int element_index = rand() % 50;
    setComposition(element_index,
      getComposition(element_index) + 1);
  }
}

void CelestialBody::generateStar()
{
  int gen = rand() % 9999;

  //90% chance to generate a main sequence star
  if (gen < 9000)
  {
    int gen_main = rand() % 999;

    //73% chance to generate a red main sequence star
    if (gen_main < 730)
    {
      setType("Red Main Sequence Star");
      setMass((rand() % 275 + 75) * 0.001f); //0.075 - 0.35Mo
      setTemp(rand() % 1300 + 2400); //2400 - 3700K
      setRadius((rand() % 52 + 8) * 0.01f); //0.08 - 0.6Ro
    }
    //12% chance to generate an orange main sequence star
    else if (gen_main >= 730 && gen_main < 850)
    {
      setType("Orange Main Sequence Star");
      setMass((rand() % 35 + 45) * 0.01f); //0.45 - 0.8Mo
      setTemp(rand() % 1500 + 3700); //3700 - 5200K
      setRadius((rand() % 30 + 70) * 0.01f); //0.7 - 1Ro
    }
    //8% chance to generate a yellow main sequence star
    else if (gen_main >= 850 && gen_main < 930)
    {
      setType("Yellow Main Sequence Star");
      setMass((rand() % 20 + 80) * 0.01f); //0.8 - 1.0Mo
      setTemp(rand() % 800 + 5200); //5200 - 6000K
      setRadius((rand() % 15 + 100) * 0.01f); //1.0 - 1.15Ro
    }
    //3% chance to generate a yellow-white main sequence star
    else if (gen_main >= 930 && gen_main < 960)
    {
      setType("Yellow-White Main Sequence Star");
      setMass((rand() % 40 + 100) * 0.01f); //1.0 - 1.4Mo
      setTemp(rand() % 500 + 6000); //6000 - 7500K
      setRadius((rand() % 25 + 115) * 0.01f); //1.15 - 1.4Ro
    }
    //2% chance to generate a white main sequence star
    else if (gen_main >= 960 && gen_main < 980)
    {
      setType("White Main Sequence Star");
      setMass((rand() % 70 + 140) * 0.01f); //1.4 - 2.1Mo
      setTemp(rand() % 2500 + 7500); //7500 - 10000K
      setRadius((rand() % 40 + 140) * 0.01f); //1.4 - 1.8Ro
    }
    //1.5% chance to generate a blue-white main sequence star
    else if (gen_main >= 980 && gen_main < 895)
    {
      setType("Blue-White Main Sequence Star");
      setMass((rand() % 1390 + 210) * 0.01f); //2.1 - 16.0Mo
      setTemp(rand() % 20000 + 10000); //10000 - 30000K
      setRadius((rand() % 480 + 180) * 0.01f); //1.8 - 6.6Ro
    }
    //0.5% chance to generate a blue main sequence star
    else
    {
      setType("Blue Main Sequence Star");
      setMass((rand() % 13400 + 1600) * 0.01f); //16.0 - 150.0Mo
      setTemp(rand() % 45000 + 30000); //30000 - 75000K
      setRadius((rand() % 19340 + 660) * 0.01f); //6.6 - 200Ro
    }
  }
  //1% chance to generate a blue giant
  else if (gen >= 9000 && gen < 9100)
  {
    setType("Blue Giant Star");
    setMass((rand() % 22500 + 2500) * 0.01f); //25.0 - 250.0Mo
    setTemp(rand() % 40000 + 10000); //10000 - 50000K
    setRadius((rand() % 500 + 500) * 0.01f); //5.0 - 10.0Ro
  }
  //3% chance to generate a red giant
  else if (gen >= 9100 && gen < 9400)
  {
    setType("Red Giant Star");
    setMass((rand() % 770 + 30) * 0.01f); //0.3 - 8.0Mo
    setTemp(rand() % 1000 + 3000); //3000 - 4000K
    setRadius((rand() % 19000 + 1000) * 0.01f); //10.0 - 200.0Ro
  }
  //2% chance to generate a white dwarf (has planetary nebula)
  else if (gen >= 9400 && gen < 9600)
  {
    setType("White Dwarf Star");
    setMass((rand() % 60 + 80) * 0.01f); //0.8 - 1.4Mo
    setTemp(rand() % 40000 + 100000); //100000 - 140000K
    setRadius((rand() % 60 + 70) * 0.0001f); //0.007 - 0.013Ro
  }
  //2% chance to generate a brown dwarf
  else if (gen >= 9600 && gen < 9800)
  {
    setType("Brown Dwarf Star");
    setMass((rand() % 78 + 2) * 0.001f); //0.002 - 0.08Mo
    setTemp(rand() % 1200 + 100); //100 - 1300K
    setRadius((rand() % 40 + 80) * 0.001f); //0.08 - 0.12Ro
  }
  //1.5% chance to generate a neutron star
  else if (gen >= 9800 && gen < 9950)
  {
    setType("Neutron Star");
    setMass((rand() % 90 + 130) * 0.01f); //1.3 - 2.2Mo
    setTemp(rand() % 7200000 + 800000); //800000 - 8000000K
    setRadius((rand() % 2 + 14) * 0.000001f); //0.000014 - 0.000016Ro
  }
  //0.48% chance to generate a pulsar (same as neutron, except blinks)
  else if (gen >= 9950 && gen < 9992)
  {
    setType("Pulsar");
    setMass((rand() % 90 + 130) * 0.01f); //1.3 - 2.2Mo
    setTemp(rand() % 7200000 + 800000); //800000 - 8000000K
    setRadius((rand() % 2 + 14) * 0.000001f); //0.000014 - 0.000016Ro
  }
  //0.02% chance to generate a black hole
  else if (gen >= 9992 && gen < 10000)
  {
    setType("Black Hole");
    setMass(-1);
    setTemp(-1);
    setRadius(-1);
  }

  //we won't be extracting anything from stars (yet?)
  setCompositionDefault();
  setAtmosphereCompositionDefault();
  setDistanceFromCenter(0);
  setParentBody(NULL);

  log();

  //generate planets in orbit
  for (int distance = 1; distance < 101; distance++)
  {
    int planet_gen = rand() % 1000;

    //7.0% chance to generate a planet at this index
    if (planet_gen <= 70)
    {
      spCelestialBody planet = new CelestialBody();
      addOrbiter(planet);
      planet->setParentBody(this);

      planet->generatePlanet(distance);
    }
  }
}

void CelestialBody::generatePlanet(int distance)
{
  int jovian_gen = rand() % 1000;

  //14.0 + loopnum % chance to generate a jovian planet
  //at the current distance
  if (jovian_gen < (140 + distance * 10))
  {
    setType("Jovian Planet");
    setMass((rand() % 150000 + 10000) * 0.001f); //10.00 - 160.00Me
    setTemp(rand() % 100 + (800 / distance)); //1 - 800K related to distance + random under 100
    setRadius((rand() % 100000 + 10) * 0.001f); //1.00 - 100.00Re

    //we won't be extracting anything from jovians (yet?)
    setCompositionDefault();
    setAtmosphereCompositionDefault();
  }
  else //generate terrestrial planet
  {
    setType("Terrestrial Planet");
    setMass((rand() % 7400 + 100) * 0.001f); //0.1 - 7.5Me
    setTemp(rand() % 100 + (750 / distance)); //50 - 650K related to distance + random under 100 
    setRadius((rand() % 2900 + 100) * 0.001f); //0.1 - 3.0Me

    //generate terrestrial chemical distribution
    generateTerrestrialDistribution();
  }

  setDistanceFromCenter(distance);

  log();

  //generate planets in orbit
  _orbit_count = 0;

  for (int distance_moon = 1; distance_moon < 11; distance_moon++)
  {
    int moon_gen = rand() % 1000;

    //14.0% chance to generate a planet at this index
    if (moon_gen <= 140)
    {
      spCelestialBody moon = new CelestialBody();
      this->addOrbiter(moon);
      moon->setParentBody(this);

      moon->generateMoon(this->getMass(), this->getTemp(), this->getRadius(), distance_moon);
    }
  }
}

void CelestialBody::generateMoon(float mass, int temp, float radius, int distance)
{
  setType("Moon");
  setMass(((rand() % 450 + 50) * 0.0001f) * mass); //0.005 - 0.05 mass of its parent
  setTemp(std::max(rand() % 45 + temp - 20, 1)); //deviation of 25 degrees to its parent, deviated on the colder side
  setRadius(((rand() % 250 + 50) * 0.0001f) * radius); //0.005 - 0.03 radius of its parent
  setDistanceFromCenter(distance);

  //generate terrestrial chemical distribution
  generateTerrestrialDistribution();

  log();
}
