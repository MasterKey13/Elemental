/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "battle_ai.h"

BattleAI::BattleAI()
{
  //enemy-target choices
  _choice_scores["ATTACK_HULL"] = 0.0f;
  _choice_scores["ATTACK_BATTERY"] = 0.0f;
  _choice_scores["ATTACK_ENGINE"] = 0.0f;
  _choice_scores["ATTACK_EQUIPMENT"] = 0.0f;

  //self-target choices
  _choice_scores["REPAIR_HULL"] = 0.0f;
  _choice_scores["REPAIR_BATTERY"] = 0.0f;
  _choice_scores["REPAIR_ENGINE"] = 0.0f;
  _choice_scores["REPAIR_EQUIPMENT"] = 0.0f;

  //other choices
  _choice_scores["ESCAPE"] = 0.0f;

  _decision = "ESCAPE";
}

//! Make the AI decide which action to perform
/*!
\param self the AI Character's ship
\param self_AI the NPC for whom we're doing these choices (ie. self)
\param enemy the enemy Character's ship (usually player, but could be another AI)
*/
void BattleAI::chooseTarget(spShip self, spNPC self_AI, spShip enemy)
{
  //custom sorting function (from highest to smallest)
  struct { bool operator() (int a, int b) { return a > b; } } biggerThan;

  //scan self and enemy for weapon damages
  std::vector<int> self_damages = scanEquipmentDamage(self);
  std::vector<int> enemy_damages = scanEquipmentDamage(enemy);
  std::sort(self_damages.begin(), self_damages.end(), biggerThan);
  std::sort(enemy_damages.begin(), enemy_damages.end(), biggerThan);

  //get highest and second highest damages from weapons
  float self_highest_dmg = 1.0f;
  float self_second_highest_dmg = 1.0f;
  float enemy_highest_dmg = 1.0f;
  float enemy_second_highest_dmg = 1.0f;

  if (self_damages[0]) { self_highest_dmg = (float)self_damages[0]; }
  if (self_damages[1]) { self_second_highest_dmg = (float)self_damages[1]; }
  if (enemy_damages[0]) { enemy_highest_dmg = (float)enemy_damages[0]; }
  if (enemy_damages[1]) { enemy_second_highest_dmg = (float)enemy_damages[1]; }

  //variables for assessing how quickly each ship can destroy each other
  float self_hull_hp = (float)self->getHull()->getHitPoints();
  float self_battery_hp = (float)self->getHull()->getBattery()->getHitPoints();
  float self_engine_hp = (float)self->getHull()->getEngine()->getHitPoints();

  float enemy_hull_hp = (float)enemy->getHull()->getHitPoints();
  float enemy_battery_hp = (float)enemy->getHull()->getBattery()->getHitPoints();
  float enemy_engine_hp = (float)enemy->getHull()->getEngine()->getHitPoints();

  float turns_until_self_hull_dead = (float)self->getHull()->getHitPoints() / enemy_highest_dmg;
  float turns_until_self_engine_dead = (float)self->getHull()->getEngine()->getHitPoints() / enemy_highest_dmg;
  float turns_until_self_battery_dead = (float)self->getHull()->getBattery()->getHitPoints() / enemy_highest_dmg;
  float turns_until_self_dead = std::min(turns_until_self_hull_dead, turns_until_self_engine_dead + turns_until_self_battery_dead);

  float turns_until_enemy_hull_dead = (float)enemy->getHull()->getHitPoints() / self_highest_dmg;
  float turns_until_enemy_engine_dead = (float)enemy->getHull()->getEngine()->getHitPoints() / self_highest_dmg;
  float turns_until_enemy_battery_dead = (float)enemy->getHull()->getBattery()->getHitPoints() / self_highest_dmg;
  float turns_until_enemy_dead = std::min(turns_until_enemy_hull_dead, turns_until_enemy_engine_dead + turns_until_enemy_battery_dead);

  float turns_until_self_hull_dead_worse_equipment = (float)self->getHull()->getHitPoints() / enemy_second_highest_dmg;
  float turns_until_self_engine_dead_worse_equipment = (float)self->getHull()->getEngine()->getHitPoints() / enemy_second_highest_dmg;
  float turns_until_self_battery_dead_worse_equipment = (float)self->getHull()->getBattery()->getHitPoints() / enemy_second_highest_dmg;
  float turns_until_self_dead_worse_equipment = std::min(turns_until_self_hull_dead, turns_until_self_engine_dead + turns_until_self_battery_dead);

  float turns_until_enemy_hull_dead_worse_equipment = (float)enemy->getHull()->getHitPoints() / self_second_highest_dmg;
  float turns_until_enemy_engine_dead_worse_equipment = (float)enemy->getHull()->getEngine()->getHitPoints() / self_second_highest_dmg;
  float turns_until_enemy_battery_dead_worse_equipment = (float)enemy->getHull()->getBattery()->getHitPoints() / self_second_highest_dmg;
  float turns_until_enemy_dead_worse_equipment = std::min(turns_until_enemy_hull_dead, turns_until_enemy_engine_dead + turns_until_enemy_battery_dead);

  //start thinking and tallying up points for all possible AI choices
  _choice_scores["ESCAPE"] += (6.1f - (float)self_AI->getBravery() / 2.5f) - ((float)self_AI->getHostility() / 3.0f);

  //take in consideration the AI's brutality and hostility
  _choice_scores["ATTACK_HULL"] += std::max((float)self_AI->getBrutality() + (float)self_AI->getHostility() - 8.1f, 0.0f);
  _choice_scores["ATTACK_BATTERY"] += std::max((float)self_AI->getBrutality() + (float)self_AI->getHostility() - 8.5f, 0.0f);
  _choice_scores["ATTACK_ENGINE"] += std::max((float)self_AI->getBrutality() + (float)self_AI->getHostility() - 8.7f, 0.0f);
  _choice_scores["ATTACK_EQUIPMENT"] += std::max((float)self_AI->getBrutality() + (float)self_AI->getHostility() - 9.4f, 0.0f);

  //assess how quickly enemy can kill its hull and consider escape
  if (turns_until_self_dead < turns_until_enemy_dead)
  {
    _choice_scores["ESCAPE"] += ((float)self_AI->getIntelligence() / 4.4f + ((float)turns_until_enemy_dead - (float)turns_until_self_dead));
  }

  //assess and compare enemy hull and engine & battery hp and consider attacking its hull
  if (enemy_hull_hp < (enemy_battery_hp + enemy_engine_hp))
  {
    _choice_scores["ATTACK_HULL"] += 9.7f * (float)enemy_hull_hp / (float)(enemy_battery_hp + enemy_engine_hp);
  }

  //asses and compare enemy's engine and battery hp values and consider attacking its battery
  if (enemy_battery_hp < enemy_engine_hp &&
    enemy_hull_hp > (enemy_battery_hp + enemy_engine_hp))
  {
    _choice_scores["ATTACK_BATTERY"] += 8.3f * (float)enemy_battery_hp / (float)enemy_engine_hp;
  }

  //assess who can kill who first, and if enemy can kill first, consider attacking the enemy's battery
  if (turns_until_self_dead < turns_until_enemy_dead)
  {
    _choice_scores["ATTACK_BATTERY"] += (float)turns_until_enemy_dead - (float)turns_until_self_dead;
  }

  //assess and compare enemy's engine and battery hp values and consider attacking its engine
  if (enemy_battery_hp > enemy_engine_hp &&
    enemy_hull_hp > (enemy_battery_hp + enemy_engine_hp))
  {
    _choice_scores["ATTACK_ENGINE"] += 8.3f * (float)enemy_engine_hp / (float)enemy_battery_hp;
  }

  //assess each other's equipments and decide if it's worth it to attack their best equipment
  if (turns_until_self_dead < turns_until_enemy_dead)
  {
    _choice_scores["ATTACK_EQUIPMENT"] += turns_until_self_dead_worse_equipment - 
                                          turns_until_enemy_dead;
  }

  log::messageln("[BATTLE AI] DECISION SCORES:\n",
    "ESCAPE: %.2f",
    "ATTACK_HULL: %.2f",
    "ATTACK_BATTERY: %.2f", 
    "ATTACK_ENGINE: %.2f", 
    "ATTACK_EQUIPMENT: %.2f", 
    
    _choice_scores["ESCAPE"],
    _choice_scores["ATTACK_HULL"],
    _choice_scores["ATTACK_BATTERY"],
    _choice_scores["ATTACK_ENGINE"],
    _choice_scores["ATTACK_EQUIPMENT"]);
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

