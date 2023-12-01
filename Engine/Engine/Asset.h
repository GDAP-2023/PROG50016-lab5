#pragma once

#ifndef  _ASSET_H_
#define _ASSET_H_

#include "Object.h"

class Asset : public Object
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Asset, Object)
public:
	Asset() = default;
	~Asset() override = default;
	void Initialize() override;
	void Destroy() override;

	friend class AssetManager;
};

#endif // !_ASSET_H_
