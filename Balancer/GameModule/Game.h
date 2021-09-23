#pragma once

#include <SDL.h>
#include <vector>
#include "EngineModule/Actor.h"

namespace GameModule {
    enum class SceneState;
    class Balancer;
    class Weighty;
    class Button;

    class Game : public EngineModule::Actor {
    public:
        Game(std::string name);
        void init();
        void loop();
        void render();

        void OnExit() override;
        void OnLButtonUp(int mX, int mY) override;

        void                   setState(SceneState);
        std::vector<Weighty*>& getWeights();
        SceneState             getState();

    private:
        SceneState            state;
        Button*               menuButton;
        SDL_Window*           window;
        SDL_Renderer*         renderer;
        SDL_Texture*          bg;
        Balancer*             balancer;
        std::vector<Weighty*> weights;
    };

} // namespace GameModule