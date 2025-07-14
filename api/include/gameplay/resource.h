#ifndef RESOURCE_H
#define RESOURCE_H

#include <functional>
#include <iostream>

class Resource {

public:
  // Texture
  enum class ResourceType {
    kNone,
    kWood,
    kFood,
    kRock
  };

private:
  int tile_index_ = 0;
  float quantity_ = 0;
  //Define the resource status
  bool is_being_worked_on_;
  bool is_respawning_;
  ResourceType type_ = ResourceType::kNone;
  double cut_time_ = 0;

public:
  [[nodiscard]] ResourceType GetType() const;
  [[nodiscard]] int GetTileIndex() const;
  [[nodiscard]] float GetQty() const;
  [[nodiscard]] bool GetWorkStatus() const;
  [[nodiscard]] bool GetDespawnStatus() const;

  void SetType(ResourceType type);
  void SetIndex(int index);
  void SetQuantity(float quantity);
  void SetWorkStatus(bool used);
  void SetDespawnStatus(bool spawn);

  void Exploit(float);

  std::function<void(int, float)> on_chop_resource_ = nullptr;

};

inline void Resource::SetType(ResourceType type) {type_ = type;}

inline void Resource::SetIndex(int index) {tile_index_ = index;}

inline void Resource::SetQuantity(float quantity) {quantity_ = quantity;}

inline void Resource::SetWorkStatus(bool used) {is_being_worked_on_ = used;}

inline void Resource::SetDespawnStatus(bool spawn) {is_respawning_ = spawn;}

inline Resource::ResourceType Resource::GetType() const {return type_;}

inline int Resource::GetTileIndex() const {return tile_index_;}

inline float Resource::GetQty() const {return quantity_;}

inline bool Resource::GetWorkStatus() const {return is_being_worked_on_;}

inline bool Resource::GetDespawnStatus() const {return is_respawning_;}


inline void Resource::Exploit(float rate) {
  quantity_ -= rate;
  quantity_ = std::max<float>(quantity_, 0);

  if (on_chop_resource_) {
    on_chop_resource_(tile_index_, quantity_);
    is_respawning_ =true;
  }
}

#endif //RESOURCE_H
