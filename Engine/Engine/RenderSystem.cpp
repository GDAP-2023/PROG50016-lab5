#include "EngineCore.h"
#include "RenderSystem.h"
#include "Renderable.h"

RenderSystem* RenderSystem::instance = nullptr;

void RenderSystem::AddRenderable(Renderable* renderable)
{
	renderables.push_back(renderable);
}

void RenderSystem::RemoveRenderable(Renderable* renderable)
{
	renderables.remove(renderable);
}

void RenderSystem::Initialize()
{
	std::ifstream inputStream("../Assets/RenderSettings.json");
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);

	std::cout << str.c_str() << std::endl;

	THROW_RUNTIME_ERROR(!document.hasKey("name"), "Render Settings must have a name");
	name = document["name"].ToString();
	THROW_RUNTIME_ERROR(!document.hasKey("width"), "Render Settings must have a width");
	width = document["width"].ToInt();
	THROW_RUNTIME_ERROR(!document.hasKey("height"), "Render Settings must have a height");
	height = document["height"].ToInt();

	if (document.hasKey("fullscreen"));
	{
		fullScreen = document["fullScreen"].ToBool();
	}
}

void RenderSystem::Destroy()
{
}

void RenderSystem::Update()
{
	for (auto& renderable : renderables)
	{
		renderable->Render();
	}
}

void RenderSystem::Load()
{
}
