#pragma once
#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <list>
#include "Asset.h"

class AssetManager {
public:

	static AssetManager& Instance() {
		if (instance == nullptr) {
			instance = new AssetManager();
		}
		return *instance;
	}

	void Destroy();

	void Initialize();

	void AddAsset(Asset* newAsset);

	void LoadAsset(int AssetId);

	void RemoveAsset(Asset* asset);

private:

	std::list<Asset*> assets;

	static AssetManager* instance;

	AssetManager();
	~AssetManager();
	inline explicit AssetManager(AssetManager const&) = delete;
	inline AssetManager& operator=(AssetManager const&) = delete;

};

#endif // !_ASSET_MANAGER_H_