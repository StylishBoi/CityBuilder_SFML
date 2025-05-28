#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string>
#include <vector>
#include <map>

template <typename TAsset>
class AssetManager {

public:
  enum class TextureIndex{
    kDefault = 0,
    kGrass,
    kWater,
    kFlowers,
    kSand,
  };
  //Include dictionary (Called MAP)
  std::string folder_;
  std::map<int, TAsset> assets_;
  TAsset default_asset_;

public:
  explicit AssetManager(std::string folder);
  void LoadAssets();
  const TAsset &GetAsset(TextureIndex textIndex);
};

template <typename TAsset>
AssetManager<TAsset>::AssetManager(std::string folder) : folder_(folder) {
}

template<typename TAsset>
void AssetManager<TAsset>::LoadAssets() {
  //If the folder doesn't exist, it returns.
  if (!std::filesystem::exists(folder_)) {
    return;
  }
  assets_.insert({static_cast<int>(TextureIndex::kDefault), TAsset(folder_ + "default.png")});
  assets_.insert({static_cast<int>(TextureIndex::kWater), TAsset(folder_ + "water.png")});
  assets_.insert({static_cast<int>(TextureIndex::kGrass), TAsset(folder_ + "grass.png")});
  assets_.insert({static_cast<int>(TextureIndex::kFlowers), TAsset(folder_ + "flowers.png")});
  assets_.insert({static_cast<int>(TextureIndex::kSand), TAsset(folder_ + "sand.png")});
}

template <typename TAsset>
const TAsset &AssetManager<TAsset>::GetAsset(TextureIndex textIndex) {

  int index = static_cast<int>(textIndex);
  if (index < 0 || index >= assets_.size()) {
    return default_asset_;
  }

  return assets_[index];
}


#endif