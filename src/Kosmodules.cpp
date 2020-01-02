#include "Kosmodules.hpp"

Plugin *pluginInstance;

void init(Plugin *p) {
	pluginInstance = p;

	p->addModel(modelOSF);
}
