#pragma once
#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <list>
#include <filesystem>
#include "Asset.h"

class AssetManager {
	DECLARE_SINGLETON(AssetManager)

	std::string assetDirectory = "../Assets";
	bool recursiveSearch = true;

	std::list<Asset*> assets;
public:

	void Destroy();

	void Initialize();

	void AddAsset(Asset* newAsset);

	void LoadAsset(int AssetId);

	void RemoveAsset(Asset* asset);

	void Load(const std::string& config_file);

};

#endif // !_ASSET_MANAGER_H_