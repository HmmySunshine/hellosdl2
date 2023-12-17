//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>

constexpr const int WINDOW_WIDTH = 640;
constexpr const int WINDOW_HEIGHT = 480;

bool Init();
bool LoadMedia();
void Close();

//SDL_Window* window = nullptr;
//SDL_Surface* gXout = nullptr;
std::unique_ptr <SDL_Window, decltype(&SDL_DestroyWindow)> windowPtr(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> gXoutPtr(nullptr, SDL_FreeSurface);

SDL_Surface* screenSurface = nullptr;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface* LoadSurface(std::string path);

bool Init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "sdl³õÊ¼»¯Ê§°Ü sdlÊ§°Ü´íÎó:" << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		windowPtr.reset(SDL_CreateWindow("hellosdl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN));
	
		if (windowPtr == nullptr)
		{
			std::cout << "´°¿Ú³õÊ¼»¯Ê§°Ü" << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(windowPtr.get());
		}
		return success;
	}
}
	
bool LoadMedia()
{
	bool success = true;
	gXoutPtr.reset(SDL_LoadBMP("x.bmp"));
	
	if (gXoutPtr == nullptr)
	{
		std::cout << "¼ÓÔØÍ¼Æ¬Ê§°Ü" << SDL_GetError() << std::endl;
		success = false;
	}
	return success;
	
}
SDL_Surface* LoadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "Í¼Æ¬¼ÓÔØÊ§°Ü: " << SDL_GetError() << std::endl;
	}
	return loadedSurface;
}

void Close()
{
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!Init())
	{
		std::cout << "Ã»ÓÐ³õÊ¼»¯" << std::endl;
	}
	else
	{
		if (!LoadMedia())
		{
			std::cout << "¼ÓÔØÍ¼Æ¬Ê§°Ü" << std::endl;
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			while (quit == false)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				SDL_BlitSurface(gXoutPtr.get(), nullptr, screenSurface, nullptr);
				SDL_UpdateWindowSurface(windowPtr.get());
			}
		}
	}
	Close();
	return 0;
}