#include "EngineCore.h"
#include "AssetManager.h"

#include <filesystem>

using std::filesystem::directory_iterator;
using std::filesystem::recursive_directory_iterator;

void AssetManager::Initialize() {
	if (recursiveSearch)
	{
		for (const auto& entry: recursive_directory_iterator(assetDirectory))
		{
			std::cout << entry.path() << std::endl;
		}
	}
}

void AssetManager::AddAsset(Asset* newAsset) {
	assets.push_back(newAsset);
}

void AssetManager::RemoveAsset(Asset* asset) {
	for (Asset* a : assets) {
		if (a == asset)
			assets.remove(asset);
	}
}

void AssetManager::Load(const std::string& config_file) {
	std::ifstream inputStream(config_file.c_str());
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON node = json::JSON::Load(str);

	if (node.hasKey("AssetDirectory")) {
		assetDirectory = node.at("AssetDirectory").ToString();
	}

	if (node.hasKey("RecursiveSearch")) {
		recursiveSearch = node.at("RecursiveSearch").ToBool();
	}
}

void AssetManager::LoadAsset(int AssetId) {
	//Check the map for loaded assets or do something
}

void AssetManager::Destroy() {
	for (Asset* a : assets) {
		Asset* assetToDelete = a;
		delete(assetToDelete);
	}
	assets.clear();
}
