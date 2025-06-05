#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <span>
#include <format>
#include <string>
#include <array>

namespace core::experimental {

template<size_t N>
struct StringLiteral {
  constexpr StringLiteral(const char (&arg)[N]) {
    std::copy_n(arg, N, str);
  }
  char str[N];
};

template<typename TAsset, typename TAssetType, StringLiteral folderPath>
requires std::is_enum_v<TAssetType> && requires
{
  {static_cast<size_t>(TAssetType::kLength)};
}
class AssetManager {
  public:

  void LoadAssets(std::span<const std::string_view> assetsPaths) {
    for (size_t i = 0; i < assets_.size(); ++i) {
      assets_[i] = TAsset(std::format("{}/{}", folderPath.str, assetsPaths[i]));
    }
  }

  const TAsset &GetAsset(TAssetType asset_index) {
    const auto index = static_cast<int64_t>(asset_index);
    if (index < 0 || index >= std::ssize(assets_)) {
      throw std::out_of_range("Invalid index");
    }
    return assets_[index];
  }
private:
  std::array<TAsset, static_cast<size_t>(TAssetType::kLength)> assets_{};
};

}

/*template <typename TAsset>
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
}*/


#endif