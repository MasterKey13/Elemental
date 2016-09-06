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

void CelestialBody::log()
{
  log::messageln("\n[CELESTIAL BODY]\nRadius: %.2f\nMass: %.2f\nTemp: %d\nType: %s\n",
    this->getRadius(),
    this->getMass(),
    this->getTemp(),
    this->getType().c_str());
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
  _composition[element] = abundance;
}

void CelestialBody::setCompositionDefault()
{
  for (int i = 0; i < 120; i++)
  {
    _composition[i] = 0;
  }
}

void CelestialBody::setAtmosphereComposition(int element, int abundance)
{
  _atmosphere_composition[element] = abundance;
}

void CelestialBody::setAtmosphereCompositionDefault()
{
  for (int i = 0; i < 120; i++)
  {
    _atmosphere_composition[i] = 0;
  }
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

void CelestialBody::generateStar()
{
  srand(time(NULL)); //random seed
  int gen = rand() % 9999;

  //90% chance to generate a main sequence star
  if (gen < 9000)
  {
    int gen_main = rand() % 999;

    //73% chance to generate a red main sequence star
    if (gen_main < 730)
    {
      setMass((rand() % 275 + 75) * 0.001f); //0.075 - 0.35Mo
      setTemp(rand() % 1300 + 2400); //2400 - 3700K
      setRadius((rand() % 52 + 8) * 0.01f); //0.08 - 0.6Ro
    }
    //12% chance to generate an orange main sequence star
    else if (gen_main >= 730 && gen_main < 850)
    {
      setMass((rand() % 35 + 45) * 0.01f); //0.45 - 0.8Mo
      setTemp(rand() % 1500 + 3700); //3700 - 5200K
      setRadius((rand() % 3 + 7) * 0.1f); //0.7 - 1Ro
    }
  }
}
