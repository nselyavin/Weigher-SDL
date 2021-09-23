#include "Root.h"


using namespace EngineModule;

Root* Root::root{};

Root::Root(std::string name) : Actor{name} {

}

EngineModule::Root::~Root()
{
	root->destroy();
}

Root* EngineModule::Root::getRoot()
{
	if (root) {
		return root;
	}

	Actor* tmp = new Root{ "root" };
	root = dynamic_cast<Root*>(tmp);
	return root;
}
