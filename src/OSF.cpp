#include "Kosmodules.hpp"
#include "dsp/digital.hpp"
#include "OSFutil.hpp"


struct OSF : Module {
	enum ParamIds {
		ORDER_PARAM,
		ORDER2_PARAM,
		O_PARAM,
		S_PARAM,
		F_PARAM,
		O2_PARAM,
		S2_PARAM,
		F2_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN_INPUT,
		IN2_INPUT,
		ORDER_INPUT,
		ORDER2_INPUT,
		O_INPUT,
		S_INPUT,
		F_INPUT,
		O2_INPUT,
		S2_INPUT,
		F2_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_OUTPUT,
		OUT2_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		O_G_LIGHT,
		O_Y_LIGHT,
		O_R_LIGHT,
		S_G_LIGHT,
		S_Y_LIGHT,
		S_R_LIGHT,
		F_G_LIGHT,
		F_Y_LIGHT,
		F_R_LIGHT,
		O2_G_LIGHT,
		O2_Y_LIGHT,
		O2_R_LIGHT,
		S2_G_LIGHT,
		S2_Y_LIGHT,
		S2_R_LIGHT,
		F2_G_LIGHT,
		F2_Y_LIGHT,
		F2_R_LIGHT,
		NUM_LIGHTS
	};
	SchmittTrigger orderTriggers[2];
	SchmittTrigger orderExtTriggers[2];
	SchmittTrigger foldTriggers[2];
	OSFutil osfs[2];
	
	OSF() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
		for (int i=0; i<2; i++) {
			lights[O_G_LIGHT + i * 9].setBrightness(1.0);
			lights[S_Y_LIGHT + i * 9].setBrightness(1.0);
			lights[F_R_LIGHT + i * 9].setBrightness(1.0);
		}
	}
	json_t *toJson() override {
		json_t *rootJ = json_object();
		json_object_set_new(rootJ, "osf1", osfs[0].toJson());
		json_object_set_new(rootJ, "osf2", osfs[1].toJson());
		return rootJ;
	}

	void fromJson(json_t *rootJ) override {
		json_t *osf1J = json_object_get(rootJ, "osf1");
		osfs[0].fromJson(osf1J);
		osfLights(0, O_G_LIGHT);
		json_t *osf2J = json_object_get(rootJ, "osf2");
		osfs[1].fromJson(osf2J);
		osfLights(1, O2_G_LIGHT);
	}
	void step() override;
	void osfLights(int osfIndex, int lightIndex);

};

void OSF::osfLights(int osfIndex, int lightIndex) {
	switch(osfs[osfIndex].cur_order){
		case OSFutil::ORDER_OSF:
			lights[lightIndex].setBrightness(1.0);
			lights[lightIndex + 1].setBrightness(0.0);
			lights[lightIndex + 2].setBrightness(0.0);
			lights[lightIndex + 3].setBrightness(0.0);
			lights[lightIndex + 4].setBrightness(1.0);
			lights[lightIndex + 5].setBrightness(0.0);
			lights[lightIndex + 6].setBrightness(0.0);
			lights[lightIndex + 7].setBrightness(0.0);
			lights[lightIndex + 8].setBrightness(1.0);
			break;
		case OSFutil::ORDER_OFS:
			lights[lightIndex].setBrightness(1.0);
			lights[lightIndex + 1].setBrightness(0.0);
			lights[lightIndex + 2].setBrightness(0.0);
			lights[lightIndex + 3].setBrightness(0.0);
			lights[lightIndex + 4].setBrightness(0.0);
			lights[lightIndex + 5].setBrightness(1.0);
			lights[lightIndex + 6].setBrightness(0.0);
			lights[lightIndex + 7].setBrightness(1.0);
			lights[lightIndex + 8].setBrightness(0.0);
			break;
		case OSFutil::ORDER_SOF:
			lights[lightIndex ].setBrightness(0.0);
			lights[lightIndex + 1].setBrightness(1.0);
			lights[lightIndex + 2].setBrightness(0.0);
			lights[lightIndex + 3].setBrightness(1.0);
			lights[lightIndex + 4].setBrightness(0.0);
			lights[lightIndex + 5].setBrightness(0.0);
			lights[lightIndex + 6].setBrightness(0.0);
			lights[lightIndex + 7].setBrightness(0.0);
			lights[lightIndex + 8].setBrightness(1.0);
			break;
		case OSFutil::ORDER_SFO:
			lights[lightIndex ].setBrightness(0.0);
			lights[lightIndex + 1].setBrightness(0.0);
			lights[lightIndex + 2].setBrightness(1.0);
			lights[lightIndex + 3].setBrightness(1.0);
			lights[lightIndex + 4].setBrightness(0.0);
			lights[lightIndex + 5].setBrightness(0.0);
			lights[lightIndex + 6].setBrightness(0.0);
			lights[lightIndex + 7].setBrightness(1.0);
			lights[lightIndex + 8].setBrightness(0.0);
			break;
		case OSFutil::ORDER_FOS:
			lights[lightIndex ].setBrightness(0.0);
			lights[lightIndex + 1].setBrightness(1.0);
			lights[lightIndex + 2].setBrightness(0.0);
			lights[lightIndex + 3].setBrightness(0.0);
			lights[lightIndex + 4].setBrightness(0.0);
			lights[lightIndex + 5].setBrightness(1.0);
			lights[lightIndex + 6].setBrightness(1.0);
			lights[lightIndex + 7].setBrightness(0.0);
			lights[lightIndex + 8].setBrightness(0.0);
			break;
		case OSFutil::ORDER_FSO:
			lights[lightIndex ].setBrightness(0.0);
			lights[lightIndex + 1].setBrightness(0.0);
			lights[lightIndex + 2].setBrightness(1.0);
			lights[lightIndex + 3].setBrightness(0.0);
			lights[lightIndex + 4].setBrightness(1.0);
			lights[lightIndex + 5].setBrightness(0.0);
			lights[lightIndex + 6].setBrightness(1.0);
			lights[lightIndex + 7].setBrightness(0.0);
			lights[lightIndex + 8].setBrightness(0.0);
			break;
	}
}

void OSF::step() {
	for (int i=0; i<2; i++) {
		if (orderTriggers[i].process(params[ORDER_PARAM + i].value) || orderExtTriggers[i].process(inputs[ORDER_INPUT + i].value)) {
			osfs[i].cur_order = (osfs[i].cur_order + 1) % OSFutil::NUM_ORDERS;;
			osfLights(i,O_G_LIGHT + i * 9); 
		}
		if (foldTriggers[i].process(inputs[F_INPUT + i * 3].value)) {
			params[F_PARAM + i * 3].value = (float) (((int) params[F_PARAM + i * 3].value + 1) % 2);
		}
		osfs[i].offset_param = params[O_PARAM + i * 3].value + inputs[O_INPUT + i * 3].value;
		osfs[i].scale_param = params[S_PARAM + i * 3].value + inputs[S_INPUT + i * 3].value;
		osfs[i].fold_param = ((int) params[F_PARAM + i * 3].value == 1);
		outputs[OUT_OUTPUT + i].value = clamp(osfs[i].process(inputs[IN_INPUT + i].value),-10.0f, 10.0f);
	}
}

struct OSFWidget : ModuleWidget {
	OSFWidget(OSF *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/OSF.svg")));
		// OSF1	
		addInput(Port::create<HexInJack>(Vec(30,180-140), Port::INPUT, module, OSF::ORDER_INPUT));
		addParam(ParamWidget::create<JuliaButton>(Vec(60,180-140), module, OSF::ORDER_PARAM, 0.0f, 1.0f, 0.0f));
		addInput(Port::create<HexInJack>(Vec(0,180-140), Port::INPUT, module, OSF::IN_INPUT));

		addInput(Port::create<HexInJack>(Vec(30,180-100), Port::INPUT, module, OSF::O_INPUT));
		addParam(ParamWidget::create<PointyKnob>(Vec(60,180-100), module, OSF::O_PARAM, -10.0, 10.0, 0.0));
		addChild(ModuleLightWidget::create<OSFLight<GYRLight>>(Vec(30,180-100), module, OSF::O_G_LIGHT));
		

		addInput(Port::create<HexInJack>(Vec(30,180-60), Port::INPUT, module, OSF::S_INPUT));
		addParam(ParamWidget::create<PointyKnob>(Vec(60,180-60), module, OSF::S_PARAM, -10.0, 10.0, 1.0));
		addChild(ModuleLightWidget::create<OSFLight<GYRLight>>(Vec(30,180-60), module, OSF::S_G_LIGHT));

		addInput(Port::create<HexInJack>(Vec(30,180-20), Port::INPUT, module, OSF::F_INPUT));
		addParam(ParamWidget::create<OSFSwitch>(Vec(60,180-20), module, OSF::F_PARAM, 0.0, 1.0, 0.0));
		addChild(ModuleLightWidget::create<OSFLight<GYRLight>>(Vec(30,180-20), module, OSF::F_G_LIGHT));
		addOutput(Port::create<HexOutJack>(Vec(0,180-20), Port::OUTPUT, module, OSF::OUT_OUTPUT));	
		// OSF2
		addInput(Port::create<HexInJack>(Vec(30,355-140), Port::INPUT, module, OSF::ORDER2_INPUT));
		addParam(ParamWidget::create<JuliaButton>(Vec(60,355-140), module, OSF::ORDER2_PARAM, 0.0f, 1.0f, 0.0f));
		addInput(Port::create<HexInJack>(Vec(0,355-140), Port::INPUT, module, OSF::IN2_INPUT));

		addInput(Port::create<HexInJack>(Vec(30,355-100), Port::INPUT, module, OSF::O2_INPUT));
		addParam(ParamWidget::create<PointyKnob>(Vec(60,355-100), module, OSF::O2_PARAM, -10.0, 10.0, 0.0));
		addChild(ModuleLightWidget::create<OSFLight<GYRLight>>(Vec(30,355-100), module, OSF::O2_G_LIGHT));

		addInput(Port::create<HexInJack>(Vec(30,355-60), Port::INPUT, module, OSF::S2_INPUT));
		addParam(ParamWidget::create<PointyKnob>(Vec(60,355-60), module, OSF::S2_PARAM, -10.0, 10.0, 1.0));
		addChild(ModuleLightWidget::create<OSFLight<GYRLight>>(Vec(30,355-60), module, OSF::S2_G_LIGHT));

		addInput(Port::create<HexInJack>(Vec(30,355-20), Port::INPUT, module, OSF::F2_INPUT));
		addParam(ParamWidget::create<OSFSwitch>(Vec(60,355-20), module, OSF::F2_PARAM, 0.0, 1.0, 0.0));
		addChild(ModuleLightWidget::create<OSFLight<GYRLight>>(Vec(30,355-20), module, OSF::F2_G_LIGHT));
		addOutput(Port::create<HexOutJack>(Vec(0,355-20), Port::OUTPUT, module, OSF::OUT2_OUTPUT));	

		// screws
		addChild(Widget::create<JuliaScrew>(Vec(0,365)));
		addChild(Widget::create<JuliaScrew>(Vec(75,0)));
	}
};
Model *modelOSF = Model::create<OSF, OSFWidget>("Kosmodules", "OSF", "Offset Scale Fold", ATTENUATOR_TAG, UTILITY_TAG);
