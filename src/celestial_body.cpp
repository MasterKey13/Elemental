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
  srand(time(NULL));
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
  setAtmosphereCompositionDefault();
}

void CelestialBody::generatePlanet()
{

}