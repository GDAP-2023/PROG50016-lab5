#include "EngineCore.h"
#include "RenderSystem.h"
#include "Sprite.h"

#include "AssetManager.h"

#include "TextureAsset.h"
#include "Entity.h"

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
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	
	Transform t = ownerEntity->GetTransform();
	sourceRect = { 0, 0, size.x, size.y };
	targetRect = { 
		(int)(t.position.x - size.x * .5f),
		(int)(t.position.y - size.y * .5f),
		(int)(size.x * t.scale.x), (int)(size.y * t.scale.y)
	};
}

void Sprite::Render()
{
	SDL_SetTextureColorMod(texture, _filterColor.r, _filterColor.g, _filterColor.b);
	SDL_RenderCopyEx(
		&RenderSystem::Instance().GetRenderer(),
		texture,
		&sourceRect,
		&targetRect,
		ownerEntity->GetTransform().rotation,
		NULL,
		SDL_FLIP_NONE
	);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}
