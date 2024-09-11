#pragma once

#include <SDL2/SDL.h>
#include "raytracer/RTImage.h"
class CApp
{
public:
	CApp() = default;
	~CApp();
	int OnExecute();

private:
	bool OnInit();
	void OnEvent(SDL_Event* i_event);
	void OnLoop();
	void OnRender();

private:
	bool m_isRunning = true;
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	RTImage m_image;
};