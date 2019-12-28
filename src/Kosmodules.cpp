#include "Kosmodules.hpp"


Plugin *pluginInstance;

void init(rack::Plugin *p) {
	pluginInstance = p;

	p->addModel(modelOSF);
}
