#pragma once

#include <SDL.h>
#include <functional>
#include "EngineModule/Actor.h"


namespace GameModule {
    class Button : public EngineModule::Actor {
    public:
        Button(std::string nodeName, std::string spriteName);
        void init(std::string spriteName);
        void setOnClickCallback(std::function<void()> function);
        void OnLButtonDown(int mX, int mY) override;
        void render() override;

    private:
        SDL_Texture* sprite;

        std::function<void()> callback;
    };
} // namespace GameModule