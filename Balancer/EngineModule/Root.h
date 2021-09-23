#pragma once
#include <string>
#include "Actor.h"

namespace EngineModule {

	class Root : public Actor {
		Root(std::string nodeName);
	public:
		~Root();
		static Root* getRoot();

	private:
		static Root* root;

	};
}
