#include "Viewport.h"

using namespace EngineModule;

SDL_Window*   Viewport::window{};
SDL_Renderer* Viewport::renderer{};

int EngineModule::Viewport::init(std::string windowName, int w, int h) {
    if (!window) {
        window = SDL_CreateWindow("Balancer",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  w,
                                  h,
                                  SDL_WINDOW_SHOWN);
    }

    if (!window) {
        return -1;
    }

    if (!renderer) {
        renderer = SDL_CreateRenderer(window, -1, 0);
    }
}

SDL_Window* Viewport::getWindow() {
    return window;
}

SDL_Renderer* EngineModule::Viewport::getRenderer()
{
    return renderer;
}
