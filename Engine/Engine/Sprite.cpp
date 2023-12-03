#include "EngineCore.h"
#include "RenderSystem.h"
#include "Sprite.h"

#include "AssetManager.h"

#include "TextureAsset.h"
#include "Entity.h"
#include <cmath>

IMPLEMENT_DYNAMIC_CLASS(Sprite);

Sprite::Sprite() {
}

Sprite::~Sprite() {
}

void Sprite::Initialize() {

}

void Sprite::Destroy() {
	texture = nullptr;
}

void Sprite::Update() {
	const Transform* t = ownerEntity->GetTransform();
	size.x = std::abs(sourceRect.w * t->scale.x);
	size.y = std::abs(sourceRect.h * t->scale.y);
	targetRect = {
		(int)(t->position.x - size.x * .5f),
		(int)(t->position.y - size.y * .5f),
		size.x,
		size.y
	};
	flip = SDL_FLIP_NONE;
	if (t->scale.x < 0) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (t->scale.y < 0) {
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
	}
}

void Sprite::Load(json::JSON& document) {
	// Checks for width in RenderSettings
	if (document.hasKey("ClassData"))
	{
		json::JSON classData = document["ClassData"];

		if (classData.hasKey("Texture")) {
			std::string guid = classData["Texture"].ToString();
			SetNewTexture(
				((TextureAsset*)AssetManager::Get().GetAsset(guid))->GetTexture()
			);
		}
	}
}

void Sprite::SetSourceRect(SDL_Rect _rect) {
	sourceRect = _rect;
}

void Sprite::SetNewTexture(SDL_Texture* _texture) {
	texture = _texture;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	
	const Transform* t = ownerEntity->GetTransform();
	sourceRect = { 0, 0, size.x, size.y };
	targetRect = { 
		(int)(t->position.x - size.x * .5f),
		(int)(t->position.y - size.y * .5f),
		(int)(size.x * std::abs(t->scale.x)), (int)(size.y * std::abs(t->scale.y))
	};
	flip = SDL_FLIP_NONE;
	if (t->scale.x < 0) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (t->scale.y < 0) {
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
	}
}

void Sprite::Render()
{
	SDL_SetTextureColorMod(texture, _filterColor.r, _filterColor.g, _filterColor.b);
	SDL_RenderCopyEx(
		&RenderSystem::Instance().GetRenderer(),
		texture,
		&sourceRect,
		&targetRect,
		ownerEntity->GetTransform()->rotation,
		NULL,
		flip
	);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}
