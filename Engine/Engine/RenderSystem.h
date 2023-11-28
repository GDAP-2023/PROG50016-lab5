#pragma once

#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <iostream>
#include <list>
#include "SDL.h"

class Renderable;

class RenderSystem
{
	friend class Engine;

	std::string _name = "Game";

	unsigned int _width = 1280;
	unsigned int _height = 720;

	bool _fullScreen = false;

	std::list<Renderable*> _renderables;

	static RenderSystem* _instance;

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	inline explicit RenderSystem();

	inline ~RenderSystem();

	inline explicit RenderSystem(RenderSystem const&) = delete;
	inline RenderSystem& operator=(RenderSystem const&) = delete;

protected:

	void Initialize();

	void Update();

	void Destroy();

	void Load();

public:

	static RenderSystem& Instance();

	SDL_Window& GetWindow();

	SDL_Renderer& GetRenderer();

	void AddRenderable(Renderable* renderable);

	void RemoveRenderable(Renderable* renderable);
};

#endif