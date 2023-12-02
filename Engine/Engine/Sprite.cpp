#include "EngineCore.h"
#include "RenderSystem.h"
#include "Sprite.h"

#include "AssetManager.h"

#include "TextureAsset.h"
#include "Entity.h"

IMPLEMENT_DYNAMIC_CLASS(Sprite);

void Sprite::Initialize() {
    Renderable::Initialize();
}

void Sprite::Destroy() {
    texture = nullptr;
    Renderable::Destroy();
}

void Sprite::Update() {
    const Transform& transform = ownerEntity->GetTransform();
    size = IVec2(transform.scale * IVec2(sourceRect.w, sourceRect.h)).Abs();
    const IVec2 pos = transform.position - size / 2;
    targetRect = {
        pos.x,
        pos.y,
        size.x,
        size.y
    };

    flip = static_cast<SDL_RendererFlip>((transform.scale.x < 0) | ((transform.scale.y < 0) << 1));
}

void Sprite::Load(json::JSON& node) {
    // Checks for width in RenderSettings
    if (!node.hasKey("ClassData"))
    {
        return;
    }

    if (json::JSON class_data = node["ClassData"]; class_data.hasKey("Texture")) {
        const std::string tex_asset_guid = class_data["Texture"].ToString();
        SetTextureAsset(dynamic_cast<TextureAsset*>(AssetManager::Get().GetAsset(tex_asset_guid)));
    }
}

void Sprite::SetSourceRect(const SDL_Rect rect) {
    sourceRect = rect;
}

void Sprite::SetTextureAsset(TextureAsset* texAsset) {
    texture = texAsset;

    if (texAsset != nullptr)
    {
        size = texAsset->GetDimensions();
        sourceRect = { 0, 0, size.x, size.y };
    }
}

void Sprite::Render()
{
    const auto texture = this->texture->GetTexture();
    SDL_SetTextureColorMod(texture, filterColor.r, filterColor.g, filterColor.b);
    SDL_RenderCopyEx(
        &RenderSystem::Instance().GetRenderer(),
        texture,
        &sourceRect,
        &targetRect,
        (double)ownerEntity->GetTransform().rotation,
        nullptr,
        flip
    );
    SDL_SetTextureColorMod(texture, 255, 255, 255);
}
