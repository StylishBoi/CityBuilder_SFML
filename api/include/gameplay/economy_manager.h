#ifndef ECONOMY_MANAGER_H
#define ECONOMY_MANAGER_H

class EconomyManager
{
 private:
  size_t woodEconomy_ = 50;
  size_t stoneEconomy_ = 50;
  size_t foodEconomy_ = 0;

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
