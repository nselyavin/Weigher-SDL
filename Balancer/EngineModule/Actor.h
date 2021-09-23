#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>

#include "EngineModule/TransformComponent.h"
#include "EngineModule/EventComponent.h"

namespace EngineModule {
    class Actor : public TransformComponent, public EventComponent {
    protected:
        Actor(std::string nodeName);
        Actor(const Actor&)  = delete;
        Actor(const Actor&&) = delete;
        
    public:
        virtual void onDestroy();
        virtual void render();

        ~Actor();
        void destroy();

        void addChild(Actor* newChild);
        void removeChild(Actor* child);

        Actor* find(std::string name) const;
        Actor* find(Actor* actor) const;

        void setParent(Actor* newParent);
        void setActive(bool val);
        bool getActive() const;

        Actor*               getParent() const;
        std::string          getName() const;
        std::vector<Actor*>& getChilds();

    private:
        bool                isActive;
        Actor*              parent;
        std::string         name;
        std::vector<Actor*> childs;
    };
} // namespace EngineModule