#include "Button.h"

#include <SDL_image.h>
#include "EngineModule/Viewport.h"

using namespace GameModule;

GameModule::Button::Button(std::string nodeName, std::string spriteName) : Actor{nodeName} {
    init(spriteName);
}

void GameModule::Button::init(std::string spriteName) {
    std::string path = "Resource/" + spriteName;
    SDL_Surface* buttonSurf = IMG_Load(path.c_str());
    sprite = SDL_CreateTextureFromSurface(EngineModule::Viewport::getRenderer(),
        buttonSurf);

    SDL_FreeSurface(buttonSurf);

    setX(20);
    setY(600);
    setSizeX(buttonSurf->w);
    setSizeY(buttonSurf->h);
}

void GameModule::Button::setOnClickCallback(std::function<void()> function) {
    callback = function;
}

void GameModule::Button::OnLButtonDown(int mX, int mY) {
    if (callback != nullptr && getX() < mX && mX < getX() + getSizeX() && getY() < mY && mY < getY() + getSizeY()) {
        callback();
    }
}

void GameModule::Button::render() {
    SDL_Rect srcWg1{0, 0, getSizeX(), getSizeY()};
    SDL_Rect destWg1{getX(), getY(), getSizeX(), getSizeY()};
    SDL_RenderCopy(
        EngineModule::Viewport::getRenderer(), sprite, &srcWg1, &destWg1);
}
