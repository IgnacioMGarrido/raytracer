#include "RTImage.h"

RTImage::~RTImage()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void RTImage::Init(int i_xSize, int i_ySize, SDL_Renderer* i_renderer)
{
	m_rChannel.resize(i_xSize, std::vector<double>(i_ySize, 0.0));
	m_gChannel.resize(i_xSize, std::vector<double>(i_ySize, 0.0));
	m_bChannel.resize(i_xSize, std::vector<double>(i_ySize, 0.0));

	m_xSize = i_xSize;
	m_ySize = i_ySize;

	m_renderer = i_renderer;

	InitTexture();
}

void RTImage::SetPixel(int i_x, int i_y, double i_red, double i_green, double i_blue)
{
	m_rChannel.at(i_x).at(i_y) = i_red;
	m_gChannel.at(i_x).at(i_y) = i_green;
	m_bChannel.at(i_x).at(i_y) = i_blue;
}

void RTImage::Display()
{
	std::vector<uint32_t> pixels(m_xSize * m_ySize);

	for (int x = 0; x < m_xSize; x++)
	{
		for (int y = 0; y < m_ySize; y++)
		{
			pixels.at(y * m_xSize + x) = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
		}
	}

	SDL_UpdateTexture(m_texture, nullptr, pixels.data(), m_xSize * sizeof(uint32_t));

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_xSize;
	srcRect.h = m_ySize;

	SDL_Rect bounds = srcRect;
	SDL_RenderCopy(m_renderer, m_texture, &srcRect, &bounds);
}

uint32_t RTImage::ConvertColor(double i_red, double i_green , double i_blue) const
{
	uint8_t r = static_cast<uint8_t>(i_red);
	uint8_t g = static_cast<uint8_t>(i_green);
	uint8_t b = static_cast<uint8_t>(i_blue);


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	uint32_t pixels = (b << 24) + (g << 16) + (r << 8) + 255;
#else
	uint32_t pixels = (255 << 24) + (r << 16) + (g << 8) + b;
#endif

	return pixels;
}

void RTImage::InitTexture()
{

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	static constexpr uint32_t rmask = 0xff000000;
	static constexpr uint32_t gmask = 0x00ff0000;
	static constexpr uint32_t bmask = 0x0000ff00;
	static constexpr uint32_t amask = 0x000000ff;
#else
	static constexpr uint32_t amask = 0xff000000;
	static constexpr uint32_t bmask = 0x00ff0000;
	static constexpr uint32_t gmask = 0x0000ff00;
	static constexpr uint32_t rmask = 0x000000ff;
#endif

	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}

	SDL_Surface* surface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);

}
