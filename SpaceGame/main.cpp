#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "SDL_CPP.h"

int main(int, char** argv)
{
    std::string const executablePath{argv[0]};
    std::string const path{ executablePath.begin(), executablePath.begin() + executablePath.find_last_of('/') + 1 };

    try
    {
        SDL::Context context;
        SDL::Window window{"SpaceGame", 10, 10, 1920, 1080};
        SDL::Renderer renderer{window};

        SDL::Texture backgroundTexture{renderer, SDL::Surface::CreateFromImage(path + "background.png")};
        SDL::Texture spaceshipTexture{renderer, SDL::Surface::CreateFromImage(path + "spaceship.png")};

        bool quit = false;
        SDL_Event event;

        while(!quit)
        {
            auto currentTicks = SDL_GetTicks();

            while(SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                if (event.type == SDL_KEYDOWN)
                {
                    quit = true;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    quit = true;
                }
            }

            renderer.Clear();

            int x = currentTicks / 10;
            x %= 1920;

            renderer.Copy(backgroundTexture, -x, 0);
            renderer.Copy(backgroundTexture, -x + 1920, 0);

            renderer.Copy(spaceshipTexture, 50, 500);

            renderer.Present();

        }
    }
    catch(SDL::SDL_Exception e)
    {
        std::cerr << e.source_method() << " - " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
