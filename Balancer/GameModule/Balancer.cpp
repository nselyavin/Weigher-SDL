#include "Balancer.h"
#include <SDL_image.h>
#include "EngineModule/Viewport.h"
#include "GameModule/Game.h"
#include "GameModule/Weighty.h"

using namespace GameModule;

GameModule::Balancer::Balancer(std::string nodeName, Game* game)
    : Actor{nodeName}, game{game} {
    weight1 = 0;
    weight2 = 0;
    init();
}

void GameModule::Balancer::init() {
    if (TTF_Init() < 0) {
        std::cerr << "[WARNING]: Failed to init TTF: " << TTF_GetError();
    }

    SDL_Surface* balancerSurf = IMG_Load("Resource/Balancer.png");
    balancerTX                = SDL_CreateTextureFromSurface(
        EngineModule::Viewport::getRenderer(), balancerSurf);

    SDL_FreeSurface(balancerSurf);

    int screenW;
    int screenH;
    SDL_GetWindowSize(EngineModule::Viewport::getWindow(), &screenW, &screenH);
    setSizeX(balancerSurf->w);
    setSizeY(balancerSurf->h);
    setX(screenW / 2 - getSizeX() / 2);
    setY(screenH / 2 + getSizeY() / 2 - 60);

    cupArea  = {283, 10, 340, 400};
    cup2Area = {655, 10, 340, 400};

    initTextureFromWeight();
}

void GameModule::Balancer::render() {
    SDL_Rect srcTX{0, 0, getSizeX(), getSizeY()};
    SDL_Rect destTX{getX(), getY(), getSizeX(), getSizeY()};
    SDL_RenderCopy(
        EngineModule::Viewport::getRenderer(), balancerTX, &srcTX, &destTX);

    SDL_SetRenderDrawColor(
        EngineModule::Viewport::getRenderer(), 230, 10, 10, 255);
    SDL_RenderDrawRect(EngineModule::Viewport::getRenderer(), &cupArea);
    SDL_RenderDrawRect(EngineModule::Viewport::getRenderer(), &cup2Area);

    int W, H;
    SDL_QueryTexture(weight1Tx, NULL, NULL, &W, &H);
    SDL_Rect srcWg1{0, 0, W, H};
    SDL_Rect destWg1{490, 467, W, H};
    SDL_RenderCopy(
        EngineModule::Viewport::getRenderer(), weight1Tx, &srcWg1, &destWg1);

}

void GameModule::Balancer::OnLButtonUp(int mX, int mY) {
    weighCups();
}

void GameModule::Balancer::weighCups() {
    std::vector<Weighty*> weights = game->getWeights();
    weight1                       = 0;
    weight2                       = 0;
    for (auto wg : weights) {
        if (!(wg->getX() + wg->getSizeX() < cupArea.x ||
              wg->getY() + wg->getSizeY() < cupArea.y ||
              wg->getX() > cupArea.x + cupArea.w ||
              wg->getY() > cupArea.y + cupArea.h)) {
            weight1 += wg->getWeight();
        }

        if (!(wg->getX() + wg->getSizeX() < cup2Area.x ||
              wg->getY() + wg->getSizeY() < cup2Area.y ||
              wg->getX() > cup2Area.x + cup2Area.w ||
              wg->getY() > cup2Area.y + cup2Area.h)) {
            weight2 += wg->getWeight();
        }
    }

    initTextureFromWeight();
}

void GameModule::Balancer::initTextureFromWeight() {
    TTF_Font* font = TTF_OpenFont("Resource/mariad.OTF", 40);
    if (!font) {
        std::cerr << "[WARNING]: Failed to load font: " << TTF_GetError();
    }

    int         Kg  = (int)weight1;
    int         Gr  = (int)(weight1 * 100) % 100;
    std::string str = std::to_string(Kg);
    str += "." + std::to_string(Gr);

    if (weight1 < weight2) {
        str += " < ";
    }else if (weight1 > weight2) {
        str += " > ";
    }
    else {
        str += " = ";
    }

    Kg  = (int)weight2;
    Gr  = (int)(weight2 * 100) % 100;
    str += std::to_string(Kg);
    str += "." + std::to_string(Gr);

    SDL_Surface* weightSurf =
        TTF_RenderText_Solid(font, str.c_str(), SDL_Color{0, 0, 0});
    weight1Tx = SDL_CreateTextureFromSurface(
        EngineModule::Viewport::getRenderer(), weightSurf);

    TTF_CloseFont(font);
    SDL_FreeSurface(weightSurf);
}
