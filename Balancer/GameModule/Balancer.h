#pragma once
#include "EngineModule/Actor.h"
#include <SDL.h>

namespace GameModule {
    class Weighty;
    class Game;

    class Balancer : public EngineModule::Actor {
    public:
        Balancer(std::string nodeName, Game* game);
        void init();

        void render() override;
        void OnLButtonUp(int mX, int mY) override;
        void weighCups();
        void initTextureFromWeight();

    private:
        SDL_Texture*  balancerTX;
        SDL_Renderer* renderer;
        Game*         game;
        float         weight1;
        float         weight2;
        char          compareSign;
        SDL_Texture*  weight1Tx;
        SDL_Texture*  weight2Tx;
        SDL_Rect      cupArea;
        SDL_Rect      cup2Area;
    };
} // namespace GameModule