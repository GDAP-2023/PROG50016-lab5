#include "EngineCore.h"
#include "RenderSystem.h"
#include "Renderable.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

RenderSystem* RenderSystem::_instance = nullptr;

RenderSystem& RenderSystem::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new RenderSystem();
	}
	return *_instance;
}

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::Initialize()
{
	std::ifstream inputStream("../Assets/RenderSettings.json");
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);
}

void RenderSystem::Destroy()
{
	
}

void RenderSystem::Update()
{
	for (Renderable* renderable : _renderables)
	{
		renderable->Render();
	}
}

void RenderSystem::Load()
{

}

void RenderSystem::AddRenderable(Renderable* renderable)
{
	_renderables.push_back(renderable);
}

void RenderSystem::RemoveRenderable(Renderable* renderable)
{
	_renderables.remove(renderable);
}