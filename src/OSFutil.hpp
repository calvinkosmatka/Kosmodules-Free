#pragma once
#include "Kosmodules.hpp"

struct OSFutil{
	enum orders {
		ORDER_OSF,
		ORDER_OFS,
		ORDER_SOF,
		ORDER_SFO,
		ORDER_FOS,
		ORDER_FSO,
		NUM_ORDERS
	};
	float scale_param = 0;
	float offset_param = 1;
	bool fold_param = false;
	bool mirror = false;
	int cur_order = ORDER_OSF;
	json_t *dataToJson();
	void dataFromJson(json_t *rootJ);
	float process(float input);
	float inv_process(float input, float *out2);
};
