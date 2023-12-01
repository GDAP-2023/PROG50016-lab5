#pragma once

#ifndef  _ASSET_H_
#define _ASSET_H_

#include "Object.h"

class Asset : public Object
{
	std::string filepath;

	DECLARE_ABSTRACT_DERIVED_CLASS(Asset, Object)
	Asset() = default;
	~Asset() override = default;
	void Initialize() override;
	void Destroy() override;

	friend class AssetManager;
};

#endif // !_ASSET_H_
