#include "Weighty.h"
#include <SDL_image.h>

#include "EngineModule/Viewport.h"

using namespace GameModule;

GameModule::Weighty::Weighty(std::string nodeName, std::string imageName)
    : Actor{nodeName} {
    isForward = false;
    init(imageName);
}

void GameModule::Weighty::init(std::string imageName) {
    if (TTF_Init() < 0) {
        std::cerr << "[WARNING]: Failed to init TTF: " << TTF_GetError();
    }
    std::string  path     = "Resource/" + imageName;
    SDL_Surface* weigSurf = IMG_Load(path.c_str());
    if (!weigSurf) {
        std::cerr << "[WARNING]: Failed to load image: " << imageName;
    } else {
        sprite = SDL_CreateTextureFromSurface(
            EngineModule::Viewport::getRenderer(), weigSurf);
        setSizeX(weigSurf->w);
        setSizeY(weigSurf->h);

        SDL_FreeSurface(weigSurf);
    }

    setTitle(L"Весы");
    setWeight(0);

    setX(50);
    setY(50);
    setSizeX(80);
    setSizeY(80);
}

void GameModule::Weighty::render() {

    SDL_Rect outline{getX() - 3, getY() - 3, 80 + 6, 80 + 6};
    SDL_SetRenderDrawColor(
        EngineModule::Viewport::getRenderer(), 80, 80, 80, 255);
    SDL_RenderFillRect(EngineModule::Viewport::getRenderer(), &outline);

    int W, H;
    SDL_QueryTexture(sprite, NULL, NULL, &W, &H);
    SDL_Rect srcTX{0, 0, W, H};
    SDL_Rect destTX{getX(), getY(), getSizeX(), getSizeY()};
    SDL_RenderCopy(
        EngineModule::Viewport::getRenderer(), sprite, &srcTX, &destTX);

    SDL_QueryTexture(titleTx, NULL, NULL, &W, &H);
    SDL_Rect srcTitle{0, 0, W, H};
    SDL_Rect dstTitle{getX(), getY() - H - 3, W, H};
    SDL_RenderCopy(
        EngineModule::Viewport::getRenderer(), titleTx, &srcTitle, &dstTitle);

    SDL_QueryTexture(weighTx, NULL, NULL, &W, &H);
    SDL_Rect srcWg{ 0, 0, W, H };
    SDL_Rect dstWg{ getX(), getY() + getSizeY()+ 3, W, H };
    SDL_RenderCopy(
        EngineModule::Viewport::getRenderer(), weighTx, &srcWg, &dstWg);
}

void GameModule::Weighty::onDestroy() {}

void GameModule::Weighty::setWeight(float val) {
    weight         = val;
    TTF_Font* font = TTF_OpenFont("Resource/mariad.OTF", 16);
    if (!font) {
        std::cerr << "[WARNING]: Failed to load font: " << TTF_GetError();
    }

    int Kg = (int)weight;
    int Gr = (int)(weight * 100) % 100;
    std::string str = std::to_string(Kg);
    str += "." + std::to_string(Gr);
    SDL_Surface* wgSurf = TTF_RenderText_Solid(font, str.c_str(), SDL_Color{ 255, 255, 255 });

    weighTx = SDL_CreateTextureFromSurface(
        EngineModule::Viewport::getRenderer(), wgSurf);

    SDL_FreeSurface(wgSurf);
    TTF_CloseFont(font);
}

void GameModule::Weighty::setTitle(std::wstring title) {
    this->title    = title;
    TTF_Font* font = TTF_OpenFont("Resource/mariad.OTF", 16);
    if (!font) {
        std::cerr << "[WARNING]: Failed to load font: " << TTF_GetError();
    }

    SDL_Surface* titleSurf = TTF_RenderUNICODE_Blended(
        font,
        reinterpret_cast<Uint16 const*>(title.c_str()),
        SDL_Color{255, 255, 255});
    titleTx = SDL_CreateTextureFromSurface(
        EngineModule::Viewport::getRenderer(), titleSurf);

    SDL_FreeSurface(titleSurf);
    TTF_CloseFont(font);
}

float GameModule::Weighty::getWeight() {
    return weight;
}

std::wstring GameModule::Weighty::getTitle() {
    return title;
}

void GameModule::Weighty::OnLButtonDown(int mX, int mY) {
    if (getX() < mX && mX < getX() + 80) {
        if (getY() < mY && mY < getY() + 80) {
            isForward = true;
        }
    }
}

void GameModule::Weighty::OnLButtonUp(int mX, int mY) {
    isForward = false;
}

void GameModule::Weighty::OnMouseMove(
    int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    if (isForward) {
        setX(mX - 80 / 2);
        setY(mY - 80 / 2);
    }
}
