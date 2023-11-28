#include "EngineCore.h"
#include "RenderSystem.h"
#include "Renderable.h"

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
	//Pulls RenderWindow information from the RenderSettings file loated in Assets
	std::ifstream inputStream("../Assets/RenderSettings.json");
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);

	//Hard stops if any of important information is missing from the RenderSettings file
	THROW_RUNTIME_ERROR(!document.hasKey("name"), "Render Settings must have a name");
	_name = document["name"].ToString();
	THROW_RUNTIME_ERROR(!document.hasKey("width"), "Render Settings must have a width");
	_width = document["width"].ToInt();
	THROW_RUNTIME_ERROR(!document.hasKey("height"), "Render Settings must have a height");
	_height = document["height"].ToInt();

	if (document.hasKey("fullscreen"))
	{
		_fullScreen = document["fullScreen"].ToBool();
		std::cout << "WINDOW FOUND IT IS: " << _fullScreen << std::endl;
	}
	
	//_fullscreen is set to start as false so if fullscreen isn't in the RenderSettings the system defaults to not full screen 
	if(_fullScreen == true)
	{
		_window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		_window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0);
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderSystem::Destroy()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}

void RenderSystem::Update()
{
	SDL_RenderClear(_renderer);
	SDL_SetRenderDrawColor(_renderer, 119, 84, 188, 10);

	for (Renderable* renderable : _renderables)
	{
		renderable->Render();
	}

	SDL_RenderPresent(_renderer);
}

void RenderSystem::Load()
{

}

SDL_Window& RenderSystem::GetWindow()
{
	return *_window;
}

SDL_Renderer& RenderSystem::GetRenderer()
{
	return *_renderer;
}

void RenderSystem::AddRenderable(Renderable* renderable)
{
	_renderables.push_back(renderable);
}

void RenderSystem::RemoveRenderable(Renderable* renderable)
{
	_renderables.remove(renderable);
}