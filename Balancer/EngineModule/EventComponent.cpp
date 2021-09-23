#include "EventComponent.h"

using namespace EngineModule;

EngineModule::EventComponent::EventComponent() {}

EngineModule::EventComponent::~EventComponent() {}

void EngineModule::EventComponent::OnEvent(SDL_Event* Event) {
    switch (Event->type) {

        case SDL_KEYDOWN: {
            OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod);
            break;
        }

        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod);
            break;
        }

        case SDL_MOUSEMOTION: {
            OnMouseMove(
                Event->motion.x,
                Event->motion.y,
                Event->motion.xrel,
                Event->motion.yrel,
                (Event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
                (Event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
                (Event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch (Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x, Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP: {
            switch (Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x, Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_QUIT: {
            OnExit();
            break;
        }

        case SDL_SYSWMEVENT: {
            // Ignore
            break;
        }

        case SDL_WINDOWEVENT: {
            switch (Event->window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    OnResize(Event->window.windowID,
                             Event->window.data1,
                             Event->window.data2);
                case SDL_WINDOWEVENT_FOCUS_GAINED: {
                    OnInputFocus();
                }
                case SDL_WINDOWEVENT_FOCUS_LOST: {
                    OnInputBlur();
                }
            }
            break;
        }

        default: {
            OnUser(Event->user.type,
                   Event->user.code,
                   Event->user.data1,
                   Event->user.data2);
            break;
        }
    }
}

void EngineModule::EventComponent::OnInputFocus() {}

void EngineModule::EventComponent::OnInputBlur() {}

void EngineModule::EventComponent::OnKeyDown(SDL_Keycode sym, Uint16 mod) {}

void EngineModule::EventComponent::OnKeyUp(SDL_Keycode sym, Uint16 mod) {}

void EngineModule::EventComponent::OnMouseFocus() {}

void EngineModule::EventComponent::OnMouseBlur() {}

void EngineModule::EventComponent::OnMouseMove(
    int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {}

void EngineModule::EventComponent::OnLButtonDown(int mX, int mY) {}

void EngineModule::EventComponent::OnLButtonUp(int mX, int mY) {}

void EngineModule::EventComponent::OnRButtonDown(int mX, int mY) {}

void EngineModule::EventComponent::OnRButtonUp(int mX, int mY) {}

void EngineModule::EventComponent::OnMButtonDown(int mX, int mY) {}

void EngineModule::EventComponent::OnMButtonUp(int mX, int mY) {}

void EngineModule::EventComponent::OnMinimize() {}

void EngineModule::EventComponent::OnRestore() {}

void EngineModule::EventComponent::OnResize(int winId, int w, int h) {}

void EngineModule::EventComponent::OnExpose() {}

void EngineModule::EventComponent::OnExit() {}

void EngineModule::EventComponent::OnUser(Uint8 type,
                                          int   code,
                                          void* data1,
                                          void* data2) {}
