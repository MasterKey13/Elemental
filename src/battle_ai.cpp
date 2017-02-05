/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include <stdlib.h>
#include <time.h>
#include "battle_ai.h"

int BattleAI::_best_choice_index = 0;

BattleAI::BattleAI()
{
  srand(time(NULL));
}

//! Make a decision and perform appropriate action
/*!
\param self_ship the AI Character's ship
\param enemy_ship the enemy's ship
\param self_NPC the NPC for whom we're doing these choices
\param battle a smart pointer to the active battle in which this AI is participating
*/
void BattleAI::think(spShip self_ship, spShip enemy_ship, spNPC self_NPC, spBattle battle)
{
  _final_decision = -10;

  while (self_ship->getHull()->getBattery()->getActionSlots() > 0 &&
         !battle->isBattleFinished() &&
         !battle->isPlayerTurn() &&
         
         _final_decision != -1)
  {
    log::messageln("PROCESSING TURN FOR ENEMY SHIP... %d", self_ship->getHull()->getBattery()->getActionSlots());

    _best_choice_index = 0;

    resetChoices();
    chooseTarget(self_ship, enemy_ship, self_NPC, battle);
    sortChoices();
    makeFinalDecision();
    validateDecisions(self_ship);
    executeDecision(self_ship, enemy_ship, battle);
 }

  battle->endTurn();
}

//! Make the AI decide which action to perform
/*!
\param self_ship the AI Character's ship
\param enemy_ship the enemy's ship
\param self_NPC the NPC for whom we're doing these choices
\param battle a smart pointer to the active battle in which this AI is participating
*/
void BattleAI::chooseTarget(spShip self_ship, spShip enemy_ship, spNPC self_NPC, spBattle battle)
{
  //scan self and enemy for weapon damages
  std::vector<int> self_damages = scanEquipmentDamage(self_ship);
  std::vector<int> enemy_damages = scanEquipmentDamage(enemy_ship);
  std::sort(self_damages.begin(), self_damages.end(), biggerThan);
  std::sort(enemy_damages.begin(), enemy_damages.end(), biggerThan);

  //get highest and second highest damages from weapons
  float self_highest_dmg = 1.0f;
  float self_second_highest_dmg = 1.0f;
  float enemy_highest_dmg = 1.0f;
  float enemy_second_highest_dmg = 1.0f;

  if (self_damages.size() > 0) { self_highest_dmg = (float)self_damages[0]; }
  if (self_damages.size() > 1) { self_second_highest_dmg = (float)self_damages[1]; }
  if (enemy_damages.size() > 0) { enemy_highest_dmg = (float)enemy_damages[0]; }
  if (enemy_damages.size() > 1) { enemy_second_highest_dmg = (float)enemy_damages[1]; }

  //variables for assessing how quickly each ship can destroy each other
  float self_hull_hp = (float)self_ship->getHull()->getHitPoints();
  float self_battery_hp = (float)self_ship->getHull()->getBattery()->getHitPoints();
  float self_engine_hp = (float)self_ship->getHull()->getEngine()->getHitPoints();

  float enemy_hull_hp = (float)enemy_ship->getHull()->getHitPoints();
  float enemy_battery_hp = (float)enemy_ship->getHull()->getBattery()->getHitPoints();
  float enemy_engine_hp = (float)enemy_ship->getHull()->getEngine()->getHitPoints();

  float turns_until_self_hull_dead = (float)self_ship->getHull()->getHitPoints() / enemy_highest_dmg;
  float turns_until_self_engine_dead = (float)self_ship->getHull()->getEngine()->getHitPoints() / enemy_highest_dmg;
  float turns_until_self_battery_dead = (float)self_ship->getHull()->getBattery()->getHitPoints() / enemy_highest_dmg;
  float turns_until_self_dead = std::min(turns_until_self_hull_dead, turns_until_self_engine_dead + turns_until_self_battery_dead);

  float turns_until_enemy_hull_dead = (float)enemy_ship->getHull()->getHitPoints() / self_highest_dmg;
  float turns_until_enemy_engine_dead = (float)enemy_ship->getHull()->getEngine()->getHitPoints() / self_highest_dmg;
  float turns_until_enemy_battery_dead = (float)enemy_ship->getHull()->getBattery()->getHitPoints() / self_highest_dmg;
  float turns_until_enemy_dead = std::min(turns_until_enemy_hull_dead, turns_until_enemy_engine_dead + turns_until_enemy_battery_dead);

  float turns_until_self_hull_dead_worse_equipment = (float)self_ship->getHull()->getHitPoints() / enemy_second_highest_dmg;
  float turns_until_self_engine_dead_worse_equipment = (float)self_ship->getHull()->getEngine()->getHitPoints() / enemy_second_highest_dmg;
  float turns_until_self_battery_dead_worse_equipment = (float)self_ship->getHull()->getBattery()->getHitPoints() / enemy_second_highest_dmg;
  float turns_until_self_dead_worse_equipment = std::min(turns_until_self_hull_dead_worse_equipment, 
                                                         turns_until_self_engine_dead_worse_equipment + turns_until_self_battery_dead_worse_equipment);

  float turns_until_enemy_hull_dead_worse_equipment = (float)enemy_ship->getHull()->getHitPoints() / self_second_highest_dmg;
  float turns_until_enemy_engine_dead_worse_equipment = (float)enemy_ship->getHull()->getEngine()->getHitPoints() / self_second_highest_dmg;
  float turns_until_enemy_battery_dead_worse_equipment = (float)enemy_ship->getHull()->getBattery()->getHitPoints() / self_second_highest_dmg;
  float turns_until_enemy_dead_worse_equipment = std::min(turns_until_enemy_hull_dead_worse_equipment, 
                                                          turns_until_enemy_engine_dead_worse_equipment + turns_until_enemy_battery_dead_worse_equipment);

  //start thinking and tallying up points for all possible AI choices
  _choice_scores[decisions::ESCAPE] += ((float)self_NPC->getBravery() / ((float)(rand() % 30) / 10.0f + 43.0f)) - (float)self_NPC->getHostility() / (((float)(rand() % 30) / 10.0f + 48.3f));

  //take in consideration the AI's brutality and hostility
  _choice_scores[decisions::ATTACK_HULL] += ((float)self_NPC->getBrutality() + (float)self_NPC->getHostility()) / ((float)(rand() % 30 + 1) / 10.0f + 25.0f);
  _choice_scores[decisions::ATTACK_BATTERY] += ((float)self_NPC->getBrutality() + (float)self_NPC->getHostility()) / ((float)(rand() % 30 + 1) / 10.0f + 25.6f);
  _choice_scores[decisions::ATTACK_ENGINE] += ((float)self_NPC->getBrutality() + (float)self_NPC->getHostility()) / ((float)(rand() % 30 + 1) / 10.0f + 25.8f);
  _choice_scores[decisions::ATTACK_EQUIPMENT] += ((float)self_NPC->getBrutality() + (float)self_NPC->getHostility()) / ((float)(rand() % 30 + 1) / 10.0f + 25.5f);

  //assess how quickly enemy can kill its hull and consider escape
  if (turns_until_self_dead <= turns_until_enemy_dead)
  {
    _choice_scores[decisions::ESCAPE] += ((float)self_NPC->getIntelligence() / 75.0f + ((float)turns_until_enemy_dead - (float)turns_until_self_dead)) / 1.5f;
  }

  //assess and compare enemy hull and engine & battery hp and consider attacking its hull
  if (enemy_hull_hp <= (enemy_battery_hp + enemy_engine_hp))
  {
    _choice_scores[decisions::ATTACK_HULL] += (float)enemy_hull_hp / (float)(enemy_battery_hp + enemy_engine_hp);
  }

  //assess and compare enemy's engine and battery hp values and consider attacking its battery
  if (enemy_battery_hp < enemy_engine_hp &&
    enemy_hull_hp > (enemy_battery_hp + enemy_engine_hp))
  {
    _choice_scores[decisions::ATTACK_BATTERY] += ((float)enemy_battery_hp / (float)enemy_engine_hp) * (float)(rand() % 100) / 80.0f;
  }

  //assess who can kill who first, and if enemy can kill first, consider attacking the enemy's battery
  if (turns_until_self_dead <= turns_until_enemy_dead)
  {
    _choice_scores[decisions::ATTACK_BATTERY] += ((float)turns_until_enemy_dead - (float)turns_until_self_dead) / 3.0f;
  }

  //assess and compare enemy's engine and battery hp values and consider attacking its engine
  if (enemy_battery_hp > enemy_engine_hp &&
    enemy_hull_hp > (enemy_battery_hp + enemy_engine_hp))
  {
    _choice_scores[decisions::ATTACK_ENGINE] += (float)enemy_engine_hp / (float)enemy_battery_hp;
  }

  //assess each other's equipments and decide if it's worth it to attack their best equipment
  if (turns_until_self_dead < turns_until_enemy_dead)
  {
    log::messageln("HELLO! %.2f, %.2f, %.2f, %.2f", 
      turns_until_self_hull_dead_worse_equipment, 
      turns_until_self_battery_dead_worse_equipment, 
      turns_until_self_engine_dead_worse_equipment,
      turns_until_self_dead_worse_equipment);
    _choice_scores[decisions::ATTACK_EQUIPMENT] += std::max(turns_until_self_dead_worse_equipment / 
                                                  (turns_until_enemy_dead * turns_until_enemy_dead), 
                                                  0.0f);
  }

  //log AI battle decision scores
  log::messageln("--------------------------");
  log::messageln("BATTLE AI DECISION SCORES:");
  log::messageln("ESCAPE: %.2f", _choice_scores[decisions::ESCAPE]);
  log::messageln("ATTACK_HULL: %.2f", _choice_scores[decisions::ATTACK_HULL]);
  log::messageln("ATTACK_BATTERY: %.2f", _choice_scores[decisions::ATTACK_BATTERY]);
  log::messageln("ATTACK_ENGINE: %.2f", _choice_scores[decisions::ATTACK_ENGINE]);
  log::messageln("ATTACK_EQUIPMENT: %.2f", _choice_scores[decisions::ATTACK_EQUIPMENT]);
  log::messageln("--------------------------");
}

//! Makes final decision based on NPC's intelligence
void BattleAI::makeFinalDecision()
{
  //for now let the NPC make the best decision always
  _final_decision = _decisions[_best_choice_index];
}

//! Validates whether the finally decided action is possible to execute and change accordingly
/*!
\param self_ship the AI Character's ship
*/
void BattleAI::validateDecisions(spShip self_ship)
{
  std::vector<int> self_damages = scanEquipmentDamage(self_ship);
  std::sort(self_damages.begin(), self_damages.end(), biggerThan);

  log::messageln("FINAL DECISION PRE-VALID: %d", _final_decision);

  //if it has no weapons to attack with, attempt to escape
  if (self_damages.size() == 0)
  {
    _final_decision = ESCAPE;
  }

  //if the ship wants to escape, but can't yet, do nothing so as to gain more AP
  if (_final_decision == ESCAPE &&
    self_ship->getHull()->getEngine()->getAPEscapePool() <
    self_ship->getHull()->getEngine()->getAPThreshold())
  {
    _final_decision = -1; //do nothing
  }
}

//! Execute the final decision
void BattleAI::executeDecision(spShip self_ship, spShip enemy_ship, spBattle battle)
{
  log::messageln("FINAL DECISION: %d", _final_decision);

  switch (_final_decision)
  {
  case -1: 
    log::messageln("ENEMY SHIP IS ATTEMPTING TO ESCAPE! %d/%d Action points!", 
      self_ship->getHull()->getEngine()->getAPEscapePool() + self_ship->getHull()->getBattery()->getActionPoints(),
      self_ship->getHull()->getEngine()->getAPThreshold());
    break;

  case ESCAPE:
    log::messageln("ENEMY SHIP ESCAPED BATTLE!");
    battle->finishBattle();
    break;

  case ATTACK_HULL:
    if (BattleAction::canPerform(self_ship, self_ship->getHull()->getEquipment()[0], enemy_ship->getHull().get()))
    {
      log::messageln("ATTACKED HULL");

      battle->addAction(new BattleAction(), self_ship->getHull()->getEquipment()[0], enemy_ship->getHull().get());
    }
    else 
    {
      doNextBestChoice(self_ship, enemy_ship, battle);
    }
    break;
    
  case ATTACK_BATTERY:
    if (BattleAction::canPerform(self_ship, self_ship->getHull()->getEquipment()[0], enemy_ship->getHull()->getBattery().get()))
    {
      log::messageln("ATTACKED BATTERY");

      battle->addAction(new BattleAction(), self_ship->getHull()->getEquipment()[0], enemy_ship->getHull()->getBattery().get());
    }
    else
    {
      doNextBestChoice(self_ship, enemy_ship, battle);
    }
    break;

  case ATTACK_ENGINE:
    if (BattleAction::canPerform(self_ship, self_ship->getHull()->getEquipment()[0], enemy_ship->getHull()->getEngine().get()))
    {
      log::messageln("ATTACKED BATTERY");

      battle->addAction(new BattleAction(), self_ship->getHull()->getEquipment()[0], enemy_ship->getHull()->getEngine().get());
    }
    else
    {
      doNextBestChoice(self_ship, enemy_ship, battle);
    }
    break;

  case ATTACK_EQUIPMENT:
    if (BattleAction::canPerform(self_ship, self_ship->getHull()->getEquipment()[0], enemy_ship->getHull()->getEquipment()[0].get()))
    {
      log::messageln("ATTACKED EQUIPMENT");

      battle->addAction(new BattleAction(), self_ship->getHull()->getEquipment()[0], enemy_ship->getHull()->getEquipment()[0].get());
    }
    else
    {
      doNextBestChoice(self_ship, enemy_ship, battle);
    }
    break;

  }
}

//! Return a vector of the total damage values of all equipment on ship, ordered from highest to lowest
/*!
\param ship the ship whose equipment will be scanned
*/
std::vector<int> BattleAI::scanEquipmentDamage(spShip ship)
{
  std::vector<int> damages;
  std::vector<spEquipment> equipment = ship->getHull()->getEquipment();

  //loop over the equipment on the ship and add their total damage values to vector
  for (std::vector<spEquipment>::size_type i = 0; i != equipment.size(); i++)
  {
    damages.push_back(
      equipment[i]->getDamage(Damage::Type::Ballistic) +
      equipment[i]->getDamage(Damage::Type::Chemical) +
      equipment[i]->getDamage(Damage::Type::Electrical)
      );
  }

  return damages;
}

//! Sorts choice score indexes from highest to lowest
void BattleAI::sortChoices()
{
  //create temporary scores for sorting
  float scores_temp[DECISION_COUNT];
  std::copy(std::begin(_choice_scores), std::end(_choice_scores), std::begin(scores_temp));

  //sort indexes by value from highest to lowest (best choice -> worst choice)
  for (int i = 0; i < DECISION_COUNT; i++)
  {
    float largest = 0.0f;
    int index = -100;

    for (int j = 0; j < DECISION_COUNT; j++)
    {
      if (largest <= scores_temp[j])
      {
        largest = scores_temp[j];
        index = j;
      }
    }

    _decisions[i] = index;
    scores_temp[index] = -1.0f;
  }
}

void BattleAI::resetChoices()
{
  //enemy-target choices
  _choice_scores[decisions::ATTACK_HULL] = 0.0f;
  _choice_scores[decisions::ATTACK_BATTERY] = 0.0f;
  _choice_scores[decisions::ATTACK_ENGINE] = 0.0f;
  _choice_scores[decisions::ATTACK_EQUIPMENT] = 0.0f;

  //self-target choices
  /*
  _choice_scores[decisions::REPAIR_HULL] = 0.0f;
  _choice_scores[decisions::REPAIR_BATTERY] = 0.0f;
  _choice_scores[decisions::REPAIR_ENGINE] = 0.0f;
  _choice_scores[decisions::REPAIR_EQUIPMENT] = 0.0f;
  */

  //other choices
  _choice_scores[decisions::ESCAPE] = 0.0f;

  _final_decision = -1;
}

void BattleAI::doNextBestChoice(spShip self_ship, spShip enemy_ship, spBattle battle)
{
  log::messageln("Choosing next best AI option...");

  _best_choice_index++;

  makeFinalDecision();
  validateDecisions(self_ship);
  executeDecision(self_ship, enemy_ship, battle);
}

