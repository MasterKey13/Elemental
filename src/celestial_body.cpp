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
  int radius,
  int mass,
  int surface_temp,
  int effective_temp,
  std::string type)
{
  setRadius(radius);
  setMass(mass);
  setSurfaceTemp(surface_temp);
  setEffectiveTemp(effective_temp);
  setType(type);

  setCompositionDefault();
  setAtmosphereCompositionDefault();

  log();
}

void CelestialBody::log()
{
  log::messageln("\n[CELESTIAL BODY]\nRadius: %d\nMass: %d\nSurface Temp: %d\nEffective Temp: %d\nType: %s\n",
    this->getRadius(),
    this->getMass(),
    this->getSurfaceTemp(),
    this->getEffectiveTemp(),
    this->getType().c_str());
}

void CelestialBody::setRadius(int radius)
{
  _radius = radius;
}

void CelestialBody::setMass(int mass)
{
  _mass = mass;
}

void CelestialBody::setSurfaceTemp(int temp)
{
  _surface_temp = temp;
}

void CelestialBody::setEffectiveTemp(int temp)
{
  _effective_temp = temp;
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

int CelestialBody::getRadius()
{
  return _radius;
}

int CelestialBody::getMass()
{
  return _mass;
}

int CelestialBody::getSurfaceTemp()
{
  return _surface_temp;
}

int CelestialBody::getEffectiveTemp()
{
  return _effective_temp;
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
