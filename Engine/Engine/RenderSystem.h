#pragma once

#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <string>
#include <list>

class Renderable;

class RenderSystem
{
private:
	std::string name = "Game";
	unsigned int width = 1280;
	unsigned int height = 720;
	bool fullScreen = false;
	std::list<Renderable*> renderables;

public:
	static RenderSystem& Instance()
	{
		if (instance == nullptr)
		{
			instance = new RenderSystem();
		}
		return *instance;
	}

	void AddRenderable(Renderable* renderable);
	void RemoveRenderable(Renderable* renderable);

protected:
	void Initialize();
	void Update();
	void Destroy();
	void Load();

private:
	static RenderSystem* instance;
	
	friend class Engine;

private:
	inline explicit RenderSystem() = default;
	inline ~RenderSystem() = default;
	inline explicit RenderSystem(RenderSystem const&) = delete;
	inline RenderSystem& operator=(RenderSystem const&) = delete;
};

#endif