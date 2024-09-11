#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>


class RTImage
{
public:
	RTImage() = default;
	~RTImage();

	void Init(int i_xSize, int i_ySize, SDL_Renderer* i_renderer);
	void SetPixel(int i_x, int i_y, double red, double green, double blue);
	void Display();

private:
	uint32_t ConvertColor(double i_red, double i_green, double i_blue) const;
	void InitTexture();

private:

	std::vector<std::vector<double>> m_rChannel;
	std::vector<std::vector<double>> m_gChannel;
	std::vector<std::vector<double>> m_bChannel;
	
	int m_xSize = 0;
	int m_ySize = 0;

	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;
};
