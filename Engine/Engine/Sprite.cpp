#include "EngineCore.h"
#include "RenderSystem.h"
#include "Sprite.h"

#include "AssetManager.h"

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
		json::JSON classData = document["width"];

		if (classData.hasKey("Texture")) {
			std::string guid = classData["Texture"].ToString();
			// Retrieve texture from asset manager by path
			// SetNewTexture()
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
	
	int pos[2] = { 100, 100 };
	int scale[2] = { 1, 1 };
	sourceRect = { 0, 0, size.x, size.y };
	targetRect = { (int)(pos[0] - size.x * .5f),  (int)(pos[1] - size.y * .5f), size.x * scale[0], size.y * scale[1]};
}

void Sprite::Render()
{
	SDL_SetTextureColorMod(texture, _filterColor.r, _filterColor.g, _filterColor.b);
	double angle = 0;
	SDL_RenderCopyEx(&RenderSystem::Instance().GetRenderer(), texture, &sourceRect, &targetRect, angle, NULL, SDL_FLIP_NONE);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}
