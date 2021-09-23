#include "Game.h"
#include <iostream>
#include <SDL_image.h>
#include "EngineModule/Viewport.h"
#include "GameModule/Balancer.h"
#include "GameModule/Weighty.h"
#include "GameModule/Button.h"
#include "GameModule/EStates.h"

using namespace GameModule;

GameModule::Game::Game(std::string name)
    : Actor{name}, state{SceneState::NOTHING} {

    window   = EngineModule::Viewport::getWindow();
    renderer = EngineModule::Viewport::getRenderer();
    init();
}

void GameModule::Game::init() {
    /*
        В этой функции определяются все игровые компоненты: задний фон, веса,
       кнопки и тд.
    */
    SDL_Surface* windowSurface = IMG_Load("Resource\\bg.jpg");
    printf("%s \n", IMG_GetError());
    bg = SDL_CreateTextureFromSurface(renderer, windowSurface);
    SDL_FreeSurface(windowSurface);

    balancer = new Balancer{"balancer", this};
    addChild(balancer);

    Weighty* weighty = new Weighty("weighty1", "gruz1.jpg");
    addChild(weighty);
    weighty->setTitle(L"Весы");
    weighty->setX(100);
    weighty->setY(610);
    weighty->setWeight(50);

    Weighty* weighty2 = new Weighty("weighty2", "gruz1.jpg");
    addChild(weighty2);
    weighty2->setTitle(L"Хиря2");
    weighty2->setX(200);
    weighty2->setY(610);
    weighty2->setWeight(100.23);

    Weighty* weighty3 = new Weighty("weighty3", "gruz1.jpg");
    addChild(weighty3);
    weighty3->setTitle(L"Хиря3");
    weighty3->setX(300);
    weighty3->setY(610);
    weighty3->setWeight(100.23);

    Weighty* cat = new Weighty("cat", "cat.jpg");
    addChild(cat);
    cat->setTitle(L"Кiт");
    cat->setX(400);
    cat->setY(610);
    cat->setWeight(15);

    weights.push_back(weighty);
    weights.push_back(weighty2);
    weights.push_back(weighty3);
    weights.push_back(cat);

    menuButton = new Button{"menuButton", "menuButton.png"};
    addChild(menuButton);
    menuButton->setOnClickCallback([&state=state]() {
        state = SceneState::EXIT_TO_MENU;
        });
    menuButton->setX(1190);
    menuButton->setY(10);
}


void GameModule::Game::loop() {}

void Game::OnLButtonUp(int mX, int mY) {
    auto childs = getChilds();
    for (size_t i = 1; i < childs.size(); ++i) {
        if (abs(childs[i - 1]->getX() - childs[i]->getX()) < 3 &&
            abs(childs[i - 1]->getY() - childs[i]->getY()) < 3) {
            childs[i]->setX(childs[i]->getX() + 30);
            childs[i]->setY(childs[i]->getY() + 30);
        }
    }
}

void GameModule::Game::setState(SceneState state) {
    this->state = state;
}

std::vector<Weighty*>& GameModule::Game::getWeights() {
    return weights;
}

SceneState GameModule::Game::getState() {
    return state;
}

void GameModule::Game::render() {
    SDL_Rect screenSize{0, 0, 1280, 720};
    SDL_RenderCopy(renderer, bg, &screenSize, NULL);
}

void GameModule::Game::OnExit() {
    state = SceneState::EXIT;
}
