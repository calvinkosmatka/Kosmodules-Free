#include "Kosmodules.hpp"

rack::Plugin *pluginInstance;

void init(rack::Plugin *p) {
	pluginInstance = p;

	p->addModel(modelOSF);
}
