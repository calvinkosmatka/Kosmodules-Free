#pragma once
#include "Kosmodules.hpp"

struct PointyKnob : RoundKnob {
	PointyKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/pointyknob.svg")));
		removeChild(shadow);
		// logic in step prevents smoothing, might as well turn it off and save some cpu
		// no way to check for smoothing due to scope of engine
		smooth = false;
	}
	void step() override {
		//if parameter changes out from under it (distribution changes)
		if (value != paramQuantity->getValue()) {
			this->value = clamp(paramQuantity->getValue(), paramQuantity->getMinValue(), paramQuantity->getMaxValue());
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
		removeChild(shadow);
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
struct OSFModeSwitch_Mir: SvgSwitch, ToggleSwitch {
	OSFModeSwitch_Mir() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_n.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_f.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_m.svg")));
	}
	void step() override {
		//if mode changes out from under it
		if (value != paramQuantity->getValue()) {
			value = paramQuantity->getValue();
			event::Change e;
			onChange(e);
		}
		SvgSwitch::step();
	}
};
struct OSFSwitch : SvgSwitch, ToggleSwitch {
	OSFSwitch() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_n.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/osf_f.svg")));
	}
};
struct JuliaButton : SvgSwitch, MomentarySwitch {
	JuliaButton() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_3.svg")));
	}
};
struct JuliaButtonTiny : SvgSwitch, MomentarySwitch {
	JuliaButtonTiny() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_0_tiny.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_3_tiny.svg")));
	}
};
struct JuliaSwitch : SvgSwitch, ToggleSwitch {
	JuliaSwitch() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_3.svg")));
	}
};
struct JuliaSwitchTiny : SvgSwitch, ToggleSwitch {
	JuliaSwitchTiny() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_0_tiny.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JuliaButton_3_tiny.svg")));
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
		
	void draw(NVGcontext *vg) override {
		char text[5];
		snprintf(text, sizeof(text), "%d", *number);
		nvgFontSize(vg, 15);
		nvgFontFaceId(vg, font->handle);
		nvgFillColor(vg, nvgRGBA(0x00, 0x00, 0x00, 0xff));
		nvgText(vg, 2, 18.75, text, NULL);	
	}
};
