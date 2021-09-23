#pragma once
#include "EngineModule/Actor.h"
#include <SDL.h>
#include <SDL_ttf.h>

namespace GameModule {
    class Weighty : public EngineModule::Actor {
    public:
        Weighty(std::string nodeName, std::string imageName);
        void init(std::string imageName);
        void render() override;
        void onDestroy() override;

        void setWeight(float val);
        void setTitle(std::wstring title);

        float       getWeight();
        std::wstring getTitle();

        void OnLButtonDown(int mX, int mY) override;
        void OnLButtonUp(int mX, int mY) override;
        void OnMouseMove(int  mX,
                         int  mY,
                         int  relX,
                         int  relY,
                         bool Left,
                         bool Right,
                         bool Middle) override;

    private:
        bool         isForward;
        SDL_Texture* titleTx;
        SDL_Texture* weighTx;
        std::wstring  title;
        SDL_Texture* sprite;
        float        weight;
    };
} // namespace GameModule