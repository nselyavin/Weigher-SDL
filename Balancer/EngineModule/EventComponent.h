/*
 *	Documentation
 *	https://wiki.libsdl.org/SDL_Event
 */

#pragma once

#include <SDL.h>

namespace EngineModule {

    class EventComponent {
    protected:
        EventComponent();

    public:
        virtual ~EventComponent();

        virtual void OnEvent(SDL_Event* Event);

        virtual void OnInputFocus();

        virtual void OnInputBlur();

        virtual void OnKeyDown(SDL_Keycode sym, Uint16 mod);

        virtual void OnKeyUp(SDL_Keycode sym, Uint16 mod);

        virtual void OnMouseFocus();

        virtual void OnMouseBlur();

        virtual void OnMouseMove(int  mX,
                                 int  mY,
                                 int  relX,
                                 int  relY,
                                 bool Left,
                                 bool Right,
                                 bool Middle);

        virtual void OnLButtonDown(int mX, int mY);

        virtual void OnLButtonUp(int mX, int mY);

        virtual void OnRButtonDown(int mX, int mY);

        virtual void OnRButtonUp(int mX, int mY);

        virtual void OnMButtonDown(int mX, int mY);

        virtual void OnMButtonUp(int mX, int mY);

        virtual void OnMinimize();

        virtual void OnRestore();

        virtual void OnResize(int winId, int w, int h);

        virtual void OnExpose();

        virtual void OnExit();

        virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
    };
} // namespace EngineModule