/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "celestial_body.h"

CelestialBody::CelestialBody()
{

}

void CelestialBody::init(
  float radius,
  float mass,
  int surface_temp,
  std::string type)
{
  setRadius(radius);
  setMass(mass);
  setSurfaceTemp(surface_temp);
  setType(type);

  setCompositionDefault();
  setAtmosphereCompositionDefault();

  log();
}

void CelestialBody::log()
{
  log::messageln("\n[CELESTIAL BODY]\nRadius: %.2f\nMass: %.2f\nSurface Temp: %d\nType: %s\n",
    this->getRadius(),
    this->getMass(),
    this->getSurfaceTemp(),
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

void CelestialBody::setSurfaceTemp(int temp)
{
  _surface_temp = temp;
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

int CelestialBody::getSurfaceTemp()
{
  return _surface_temp;
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

}
