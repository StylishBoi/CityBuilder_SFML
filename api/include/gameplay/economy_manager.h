#ifndef ECONOMY_MANAGER_H
#define ECONOMY_MANAGER_H

class EconomyManager
{
 private:
  size_t wood_economy_ = 50;
  size_t stone_economy_ = 50;
  size_t food_economy_ = 50;

 public:

  bool CheckBuildingCost(size_t wood_cost, size_t stone_cost);

  //reduce/increase wood_economy by a certain number
  void ReduceWoodEconomyBy(size_t number);
  void IncreaseWoodEconomyBy(size_t number);
  [[nodiscard]] size_t GetWoodEconomy() const;

  void ReduceStoneEconomyBy(size_t number);
  void IncreaseStoneEconomyBy(size_t number);
  [[nodiscard]] size_t GetStoneEconomy() const;

  void ReduceFoodEconomyBy(size_t number);
  void IncreaseFoodEconomyBy(size_t number);
  [[nodiscard]] size_t GetFoodEconomy() const;

};
#endif  // ECONOMY_MANAGER_H
