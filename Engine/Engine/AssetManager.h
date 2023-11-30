#pragma once
#ifndef _AM_H_
#define _AM_H_

#include <list>

class Asset;

class AssetManager
{
public:

	inline static AssetManager& Instance()
	{
		if (instance == nullptr)
		{
			instance = new AssetManager();
		}
		return *instance;
	}

	void Destroy();

	void Initialize();

	void AddAsset(Asset* newAsset);

	void LoadAsset(int AssetId);

	void LoadTexture();

	void LoadSound();

	void LoadMusic();

	void LoadFont();

	void RemoveAsset(Asset* asset);

private:

	std::list<Asset*> assets;

	static AssetManager* instance;

	AssetManager();
	~AssetManager();
	inline explicit AssetManager(AssetManager const&) = delete;
	inline AssetManager& operator=(AssetManager const&) = delete;
	
};

#endif // !_AM_H_