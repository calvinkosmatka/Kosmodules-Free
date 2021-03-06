#pragma once
#include "Kosmodules.hpp"

struct PointyKnob : RoundKnob {
	PointyKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/pointyknob.svg")));
		fb->removeChild(shadow);
	}
};
struct PointyKnobSnap : PointyKnob {
	PointyKnobSnap() {
		snap = true;
	}
};
struct PointyKnobSmall : PointyKnob {
	PointyKnobSmall() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/pointyknobsmall.svg")));
	}
};
struct PointyKnobTiny : PointyKnob {
	PointyKnobTiny() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/pointyknobtiny.svg")));
	}
};
struct HexInJack : SvgPort {
	HexInJack() {
		fb->removeChild(shadow);
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/jack.svg")));
	}
};
struct HexOutJack : HexInJack {
	HexOutJack() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/outjack.svg")));
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
		addBaseColor(SCHEME_GREEN);
		addBaseColor(SCHEME_YELLOW);
		addBaseColor(SCHEME_RED);
	}
};
struct OSFModeSwitch_Mir: SvgSwitch {
	OSFModeSwitch_Mir() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_n.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_f.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_m.svg")));
		fb->removeChild(shadow);
	}
};
struct OSFSwitch : SvgSwitch {
	OSFSwitch() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_n.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_f.svg")));
		fb->removeChild(shadow);
	}
};
struct JuliaButton : SvgSwitch {
	JuliaButton() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_3.svg")));
		fb->removeChild(shadow);
	}
};
struct JuliaButtonTiny : SvgSwitch {
	JuliaButtonTiny() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_0_tiny.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_3_tiny.svg")));
		fb->removeChild(shadow);
	}
};
struct JuliaSwitch : SvgSwitch {
	JuliaSwitch() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_3.svg")));
		fb->removeChild(shadow);
	}
};
struct JuliaSwitchTiny : SvgSwitch {
	JuliaSwitchTiny() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_0_tiny.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_3_tiny.svg")));
		fb->removeChild(shadow);
	}
};
struct JuliaScrew : SvgScrew {
	JuliaScrew() {
		sw->setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/screw.svg")));
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
		
	void draw(const DrawArgs& args) override {
		char text[5];
		snprintf(text, sizeof(text), "%d", *number);
		nvgFontSize(args.vg, 15);
		nvgFontFaceId(args.vg, font->handle);
		nvgFillColor(args.vg, nvgRGBA(0x00, 0x00, 0x00, 0xff));
		nvgText(args.vg, 2, 18.75, text, NULL);	
	}
};
