#include "CApp.h"

CApp::~CApp()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool CApp::OnInit()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		return false;
	}

	m_window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	if(m_renderer == nullptr)
	{
		return false;
	}

	m_image.Init(1280, 720, m_renderer);

	for (int x = 0; x < 1280; x++)
	{
		for (int y = 0; y < 720; y++)
		{
			double red = (static_cast<double>(x) / 1280) * 255.0;
			double green = (static_cast<double>(y) / 720) * 255.0;
			m_image.SetPixel(x, y, red, green, 0.0);
		}
	}

	return true;
}

int CApp::OnExecute()
{
	SDL_Event ev;
	if (OnInit() == false)
	{
		return -1;
	}
	
	while (m_isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			OnEvent(&ev);
		}
		OnLoop();
		OnRender();
    }
}

void CApp::OnEvent(SDL_Event* i_event)
{
	switch (i_event->type)
	{
		case SDL_QUIT:
		{
			m_isRunning = false;
			break;
		}
	}
}

void CApp::OnLoop()
{

}

void CApp::OnRender()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer); 

	m_image.Display();
	SDL_RenderPresent(m_renderer);
}

