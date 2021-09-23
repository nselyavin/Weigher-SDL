#pragma once
#include <SDL.h>
#include <string>

namespace EngineModule {


    class Viewport {
        Viewport();
    public:
        static int init(std::string windowName, int w, int h);

        static SDL_Window*   getWindow();
        static SDL_Renderer* getRenderer();
    private:
        static SDL_Window*   window;
        static SDL_Renderer* renderer;
    };
} // namespace EngineModule
