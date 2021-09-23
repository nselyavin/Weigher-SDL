#include "TransformComponent.h"

using namespace EngineModule;

void TransformComponent::setX(float val) {
    pos.first = val;
}

void EngineModule::TransformComponent::setY(float val) {
    pos.second = val;
}

void EngineModule::TransformComponent::setScaleX(float val) {
    scale.first = val;
}

void EngineModule::TransformComponent::setScaleY(float val) {
    scale.second = val;
}

void EngineModule::TransformComponent::setSizeX(float val) {
    size.first = val;
}

void EngineModule::TransformComponent::setSizeY(float val) {
    size.second = val;
}

float EngineModule::TransformComponent::getX() {
    return pos.first;
}

float EngineModule::TransformComponent::getY() {
    return pos.second;
}

float EngineModule::TransformComponent::getScaleX() {
    return scale.first;
}

float EngineModule::TransformComponent::getScaleY() {
    return scale.second;
}

float EngineModule::TransformComponent::getSizeX() {
    return size.first;
}

float EngineModule::TransformComponent::getSizeY() {
    return size.second;
}

std::pair<float, float> TransformComponent::getPos() const {
    return pos;
}

std::pair<float, float> TransformComponent::getScale() const {
    return scale;
}

std::pair<float, float> TransformComponent::getSize() const {
    return size;
}
