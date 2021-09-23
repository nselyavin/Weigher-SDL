// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <stdio.h>

#include "EngineModule/Actor.h"
#include "EngineModule/Root.h"
#include "EngineModule/Viewport.h"
#include "GameModule/Game.h"
#include "GameModule/Menu.h"
#include "GameModule/EStates.h"

using namespace EngineModule;
using namespace GameModule;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void mainRender(Actor* actor) {
    // Если объект не активен, то он и его наследники не рендерятся 
    if (!actor->getActive()) {
        return;
    }
    actor->render();
    for (const auto& child : actor->getChilds()) {
        mainRender(child);
    }
}

// Обход по всем объектам в дереве
void mainEventLoop(Actor* actor, SDL_Event* e) {
    // Если объект не активен, то он и его наследники не реагируют на события
    if (!actor->getActive()) {
        return;
    }
    actor->OnEvent(e);

    for (const auto& child : actor->getChilds()) {
        mainEventLoop(child, e);
    }
}

int main(int argc, char* args[]) {
    setlocale(LC_ALL, "Russian");
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "[ERROR]: failed to init SDL\n";
        return -1;
    }

    if (Viewport::init("Balancer", SCREEN_WIDTH, SCREEN_HEIGHT) < 0) {
        std::cerr << "[ERROR]: failed to create window\n";
        return -1;
    }

    SDL_Window*   window{Viewport::getWindow()};
    SDL_Renderer* renderer{Viewport::getRenderer()};
    SDL_Event     Event;
    Root*         storage{Root::getRoot()};
    Actor*        root{storage->getRoot()};
    bool          quit{};

    Menu menu{"menu"};
    root->addChild(&menu);

    Game game{"game"};
    game.setActive(false);
    root->addChild(&game);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    while (!quit) {
        switch (menu.getState()) {
            case SceneState::EXIT: {
                quit = true;
                break;
            }
            case SceneState::PLAY_GAME: {
                menu.setActive(false);
                game.setActive(true);
                switch (game.getState()) {
                    case SceneState::EXIT_TO_MENU: {
                        menu.setActive(true);
                        menu.setState(SceneState::NOTHING);
                        game.setActive(false);
                        break;
                    }
                    case SceneState::EXIT: {
                        quit = true;
                        break;
                    }
                }
                game.setState(SceneState::NOTHING);
                break;
            }
        }

        while (SDL_PollEvent(&Event) != 0) {
            mainEventLoop(root, &Event);
        }

        SDL_RenderClear(renderer);
        mainRender(root);
        SDL_RenderPresent(renderer);

        SDL_Delay(30.3);
    }

    SDL_Quit();
    return 0;
}
