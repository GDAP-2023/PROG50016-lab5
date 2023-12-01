#include "EngineCore.h"
#include "AssetManager.h"
#include <iostream>

AssetManager* AssetManager::instance = nullptr;

void AssetManager::Initialize()
{
	std::cout << "AssetManager Initialize()" << std::endl;
}

void AssetManager::AddAsset(Asset* newAsset)
{
	assets.push_back(newAsset);
}

void AssetManager::RemoveAsset(Asset* asset)
{
	for (Asset* a : assets)
	{
		if (a == asset)
			assets.remove(asset);
	}
}

AssetManager::AssetManager()
{
	std::cout << "AssetManager Constructor" << std::endl;
}

AssetManager::~AssetManager()
{
	std::cout << "AssetManager Destructor" << std::endl;
}

void AssetManager::LoadAsset(int AssetId)
{
	//Check the map for loaded assets or do something
}

void AssetManager::Destroy()
{
	for (Asset* a : assets)
	{
		Asset* assetToDelete = a;
		delete(assetToDelete);
	}
	assets.clear();

	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
