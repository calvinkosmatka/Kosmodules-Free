#pragma once
#include "Kosmodules.hpp"


struct PointyKnob : RoundKnob {
	PointyKnob() {
		setSVG(SVG::load(assetPlugin(pluginInstance, "res/pointyknob.svg")));
		removeChild(shadow);
		// logic in step prevents smoothing, might as well turn it off and save some cpu
		// no way to check for smoothing due to scope of engine
		smooth = false;
	}
	void step() override {
		//if parameter changes out from under it (distribution changes)
		if (value != module->params[paramId].value) {
			this->value = clamp(module->params[paramId].value, fminf(minValue, maxValue), fmaxf(minValue, maxValue));
			dirty = true;	
		}
		RoundKnob::step();
	}
};
struct PointyKnobSnap : PointyKnob {
	PointyKnobSnap() {
		snap = true;
	}
};
struct PointyKnobSmall : PointyKnob {
	PointyKnobSmall() {
		setSVG(SVG::load(assetPlugin(pluginInstance, "res/pointyknobsmall.svg")));
	}
};
struct PointyKnobTiny : PointyKnob {
	PointyKnobTiny() {
		setSVG(SVG::load(assetPlugin(pluginInstance, "res/pointyknobtiny.svg")));
	}
};
struct HexInJack : SVGPort {
	HexInJack() {
		removeChild(shadow);
		setSVG(SVG::load(assetPlugin(pluginInstance, "res/jack.svg")));
	}
};
struct HexOutJack : HexInJack {
	HexOutJack() {
		setSVG(SVG::load(assetPlugin(pluginInstance, "res/outjack.svg")));
	}
};
template <typename BASE>
struct OSFLight : BASE {
	OSFLight() {
		this->box.size = Vec(5,5);
	}
};
struct GYRLight : GrayModuleLightWidget {
	GYRLight() {
		addBaseColor(COLOR_GREEN);
		addBaseColor(COLOR_YELLOW);
		addBaseColor(COLOR_RED);
	}
};
struct OSFModeSwitch_Mir: SVGSwitch, ToggleSwitch {
	OSFModeSwitch_Mir() {
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/osf_n.svg")));
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/osf_f.svg")));
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/osf_m.svg")));
	}
	void step() override {
		//if mode changes out from under it
		if (value != module->params[paramId].value) {
			this->value = module->params[paramId].value;
			EventChange e;
			onChange(e);
		}
		SVGSwitch::step();
	}
};
struct OSFSwitch : SVGSwitch, ToggleSwitch {
	OSFSwitch() {
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/osf_n.svg")));
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/osf_f.svg")));
	}
};
struct JuliaButton : SVGSwitch, MomentarySwitch {
	JuliaButton() {
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/JuliaButton_0.svg")));
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/JuliaButton_3.svg")));
	}
};
struct JuliaButtonTiny : SVGSwitch, MomentarySwitch {
	JuliaButtonTiny() {
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/JuliaButton_0_tiny.svg")));
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/JuliaButton_3_tiny.svg")));
	}
};
struct JuliaSwitch : SVGSwitch, ToggleSwitch {
	JuliaSwitch() {
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/JuliaButton_0.svg")));
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/JuliaButton_3.svg")));
	}
};
struct JuliaSwitchTiny : SVGSwitch, ToggleSwitch {
	JuliaSwitchTiny() {
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/JuliaButton_0_tiny.svg")));
		addFrame(SVG::load(assetPlugin(pluginInstance, "res/JuliaButton_3_tiny.svg")));
	}
};
struct JuliaScrew : SVGScrew {
	JuliaScrew() {
		sw->setSVG(SVG::load(assetPlugin(pluginInstance, "res/screw.svg")));
		box.size = sw->box.size;
	}
};
struct NumberDisplay : TransparentWidget{
	std::shared_ptr<Font> font;
	int *number;
	NumberDisplay(int *number, std::shared_ptr<Font> font){
		this->number = number;

		this->font = font;
	}
		
	void draw(NVGcontext *vg) override {
		char text[5];
		snprintf(text, sizeof(text), "%d", *number);
		nvgFontSize(vg, 15);
		nvgFontFaceId(vg, font->handle);
		nvgFillColor(vg, nvgRGBA(0x00, 0x00, 0x00, 0xff));
		nvgText(vg, 2, 18.75, text, NULL);	
	}
};
