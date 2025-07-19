#include "gameplay/economy_manager.h"

bool EconomyManager::CheckBuildingCost(size_t wood_cost, size_t stone_cost) {
  if(wood_cost > woodEconomy_ || stone_cost > stoneEconomy_){
    return false;
  }
  return true;
}

void EconomyManager::ReduceWoodEconomyBy(const size_t number)
{
  woodEconomy_ -= number;
}
void EconomyManager::IncreaseWoodEconomyBy(const size_t number)
{
  woodEconomy_ += number;
}

void EconomyManager::ReduceStoneEconomyBy(const size_t number)
{
  stoneEconomy_ -= number;
}
void EconomyManager::IncreaseStoneEconomyBy(const size_t number)
{
  stoneEconomy_ += number;
}

void EconomyManager::ReduceFoodEconomyBy(const size_t number)
{
  foodEconomy_ -= number;
}
void EconomyManager::IncreaseFoodEconomyBy(const size_t number)
{
  foodEconomy_ += number;
}


//GET
size_t EconomyManager::GetWoodEconomy() const
{
  return woodEconomy_;
}
size_t EconomyManager::GetStoneEconomy() const
{
  return stoneEconomy_;
}
size_t EconomyManager::GetFoodEconomy() const
{
  return foodEconomy_;
}