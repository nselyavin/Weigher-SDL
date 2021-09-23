#pragma once
#include <iostream>

namespace EngineModule {
    class TransformComponent {
    protected:
        TransformComponent() = default;

    public:
        void setX(float val);
        void setY(float val);
        void setScaleX(float val);
        void setScaleY(float val);
        void setSizeX(float val);
        void setSizeY(float val);

        float getX();
        float getY();
        float getScaleX();
        float getScaleY();
        float getSizeX();
        float getSizeY();

        std::pair<float, float> getPos() const;

        std::pair<float, float> getScale() const;

        std::pair<float, float> getSize() const;

    private:
        std::pair<float, float> pos;
        std::pair<float, float> scale{1.0f, 1.0f};
        std::pair<float, float> size;
    };

} // namespace EngineModule