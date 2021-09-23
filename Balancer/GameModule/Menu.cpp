#include "Menu.h"
#include "GameModule/Button.h"
#include "EngineModule/Viewport.h"
#include <SDL_image.h>
#include "GameModule/EStates.h"

using namespace GameModule;

GameModule::Menu::Menu(std::string nodeName)
    : Actor{nodeName}, state{SceneState::NOTHING} {

    init();
}

void GameModule::Menu::init() {
    SDL_Surface* windowSurface = IMG_Load("Resource\\bgMenu.jpg");
    printf("%s \n", IMG_GetError());
    bg = SDL_CreateTextureFromSurface(EngineModule::Viewport::getRenderer(),
                                      windowSurface);
    SDL_FreeSurface(windowSurface);

    SDL_Surface* logoSurface = IMG_Load("Resource\\logo.png");
    printf("%s \n", IMG_GetError());
    logo = SDL_CreateTextureFromSurface(EngineModule::Viewport::getRenderer(),
        logoSurface);
    SDL_FreeSurface(logoSurface);

    start = new Button{"start", "start.png"};
    addChild(start);

    int w, h;
    SDL_GetWindowSize(EngineModule::Viewport::getWindow(), &w, &h);

    start->setX(w / 5);
    start->setY(h / 3);
    start->setOnClickCallback([this]() {
        this->setState(SceneState::PLAY_GAME);
    });

    exit = new Button{"exit", "exit.png"};
    addChild(exit);
    exit->setX(w / 5);
    exit->setY(h / 2);
    exit->setOnClickCallback([this]() {
        this->setState(SceneState::CONFIRM);
    });

    yes = new Button{"yes", "yes.png"};
    addChild(yes);
    yes->setX(w / 3);
    yes->setY(h / 2);
    yes->setOnClickCallback([this]() {
        this->setState(SceneState::EXIT);
    });

    no = new Button{ "no", "no.png" };
    addChild(no);
    no->setX(w / 2);
    no->setY(h / 2);
    no->setOnClickCallback([this]() {
        this->setState(SceneState::NOTHING);
        });
}

void GameModule::Menu::render() {
    SDL_Rect screenSize{ 0, 0, 1280, 720 };
    SDL_RenderCopy(
        EngineModule::Viewport::getRenderer(), bg, &screenSize, NULL);

    int w, h;
    SDL_QueryTexture(logo, NULL, NULL, &w, &h);
    SDL_Rect srcRect{ 0, 0, w, h };
    SDL_Rect destRect{ start->getX() - 20, start->getY() - 2*h, w, h };
    SDL_RenderCopy(
        EngineModule::Viewport::getRenderer(), logo, &screenSize, &destRect);

    if (state == SceneState::CONFIRM) {
        start->setActive(false);
        exit->setActive(false);
        yes->setActive(true);
        no->setActive(true);
        return;
    }

    start->setActive(true);
    exit->setActive(true);
    yes->setActive(false);
    no->setActive(false);
}

void GameModule::Menu::OnExit() {
    state = SceneState::EXIT;
}

void GameModule::Menu::setState(SceneState val) {
    state = val;
}

SceneState GameModule::Menu::getState() {
    return state;
}
