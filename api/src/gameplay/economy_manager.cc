#include "gameplay/economy_manager.h"

bool EconomyManager::CheckBuildingCost(size_t wood_cost, size_t stone_cost) {
  if(wood_cost > wood_economy_ || stone_cost > stone_economy_){
    return false;
  }
  return true;
}

void EconomyManager::ReduceWoodEconomyBy(const size_t number)
{
  wood_economy_ -= number;
}
void EconomyManager::IncreaseWoodEconomyBy(const size_t number)
{
  wood_economy_ += number;
}

void EconomyManager::ReduceStoneEconomyBy(const size_t number)
{
  stone_economy_ -= number;
}
void EconomyManager::IncreaseStoneEconomyBy(const size_t number)
{
  stone_economy_ += number;
}

void EconomyManager::ReduceFoodEconomyBy(const size_t number)
{
  food_economy_ -= number;
}
void EconomyManager::IncreaseFoodEconomyBy(const size_t number)
{
  food_economy_ += number;
}


//GET
size_t EconomyManager::GetWoodEconomy() const
{
  return wood_economy_;
}
size_t EconomyManager::GetStoneEconomy() const
{
  return stone_economy_;
}
size_t EconomyManager::GetFoodEconomy() const
{
  return food_economy_;
}