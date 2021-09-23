#include "Actor.h"
#include "Root.h"

using namespace EngineModule;
Actor::Actor(std::string name) : name{name} {
    if(name == "root"){
        parent = nullptr;
    } else {
        Root::getRoot()->addChild(this);
    }
    isActive = true;
}


void Actor::render() {}

void Actor::onDestroy() {}

EngineModule::Actor::~Actor()
{
}

void Actor::destroy() {
    onDestroy();

    while (!childs.empty()) {
        Actor* tmp = childs.back();
        tmp->destroy();
        childs.pop_back();
        delete tmp;
    }
}

void Actor::addChild(Actor* newChild) {
    for (auto& child : childs) {
        if (child == newChild) {
            std::cerr << "[WARNING]: child(" << newChild->getName() << "{" << newChild
                      << "}) already added to " << parent;
            return;
        }
    }
    newChild->setParent(this);
    childs.push_back(newChild);
}

void Actor::removeChild(Actor* child) {
    for (std::vector<Actor*>::iterator it = childs.begin(); it < childs.end();
         ++it) {
        if (*it == child) {
            (*it)->setParent(nullptr);
            childs.erase(it);
            return;
        }
        std::cerr << "[WARNING]: child(" << child << "{" << child << "}) not found for "
                  << parent;
    }
}

Actor* Actor::find(std::string name) const {
    for (auto& child : childs) {
        if (child->getName() == name) {
            return child;
        }
    }
    return nullptr;
}

Actor* Actor::find(Actor* actor) const {
    for (auto& child : childs) {
        if (child == actor) {
            return child;
        }
    }
    return nullptr;
}

void EngineModule::Actor::setParent(Actor* newParent) {
    if (parent == nullptr) {
        parent = newParent;
        return;
    }

    std::vector<Actor*>& childs = this->parent->getChilds();
    for (std::vector<Actor*>::iterator it = childs.begin(); it < childs.end();
        ++it) {
        if (*it == this) {
            childs.erase(it);
            break;
        }
    }
    parent = newParent;
}

void EngineModule::Actor::setActive(bool val)
{
    isActive = val;
}

bool EngineModule::Actor::getActive() const
{
    return isActive;
}

Actor* EngineModule::Actor::getParent() const {
    return parent;
}

std::string Actor::getName() const {
    return name;
}

std::vector<Actor*>& EngineModule::Actor::getChilds() {
    return childs;
}
