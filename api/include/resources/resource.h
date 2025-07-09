#ifndef RESOURCE_H
#define RESOURCE_H

#include <functional>

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
  bool isBeingWorkedOn;
  ResourceType type_ = ResourceType::kNone;
  double cut_time_ = 0;

public:
  [[nodiscard]] ResourceType GetType() const;
  [[nodiscard]] int GetTileIndex() const;
  [[nodiscard]] float GetQty() const;
  [[nodiscard]] bool GetWorkStatus() const;

  void SetType(ResourceType type);
  void SetIndex(int index);
  void SetQuantity(float quantity);
  void SetWorkStatus(bool used);

  void Exploit(float);

  std::function<void(int, float)> OnChopRessource_ = nullptr;

};

inline void Resource::SetType(ResourceType type){
  type_ = type;
}
inline void Resource::SetIndex(int index){
  tile_index_ = index;
}
inline void Resource::SetQuantity(float quantity){
  quantity_ = quantity;
}
inline void Resource::SetWorkStatus(bool used){
  isBeingWorkedOn = used;
}

inline Resource::ResourceType Resource::GetType() const{
  return type_;
}
inline int Resource::GetTileIndex() const {
  return tile_index_;
}
inline float Resource::GetQty() const {
  return quantity_;
}
inline bool Resource::GetWorkStatus() const {
  return isBeingWorkedOn;
}


inline void Resource::Exploit(float rate) {
  quantity_ -= rate;
  quantity_ = std::max<float>(quantity_, 0);

  if (OnChopRessource_) {
    OnChopRessource_(tile_index_, quantity_);
  }
}

#endif //RESOURCE_H
