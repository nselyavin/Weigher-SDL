#pragma once
#include <SDL.h>
#include "EngineModule/Actor.h"

namespace GameModule {
	enum class SceneState;
	class Button;

	class Menu : public EngineModule::Actor{
	public:
		Menu(std::string nodeName);
		void init();
		void render() override;
		void OnExit() override;

		void setState(SceneState val);
		SceneState getState();

	private:
		SDL_Texture* logo;
		SDL_Texture* bg;
		Button* start;
		Button* exit;
		Button* yes;
		Button* no;
		SceneState state;
	};
}
