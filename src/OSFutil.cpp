#include "OSFutil.hpp"

json_t *OSFutil::toJson() {
	json_t *rootJ = json_object();
	json_object_set_new(rootJ, "cur_order", json_integer(cur_order));
	return rootJ;	
}

void OSFutil::fromJson(json_t *rootJ){
	json_t *orderJ = json_object_get(rootJ, "cur_order");
	cur_order = json_integer_value(orderJ);
}

float OSFutil::process(float input){
	float mir = 1.0;
	switch(cur_order) {
		case ORDER_OSF:
			input += offset_param;
			input *= scale_param;
			if (fold_param){
				if (mirror) 
					if (randomUniform() < .5)
			       			mir = -1.0;	
				return  mir * fabsf(input);
			}
			return input;
		case ORDER_OFS:
			input = input + offset_param;
			if (fold_param){
				if (mirror) 
					if (randomUniform() < .5)
			       			mir = -1.0;	
				input =  mir * fabsf(input);
			}
			return input * scale_param;
		case ORDER_SOF:
			input *= scale_param;
			input += offset_param;
			if (fold_param){
				if (mirror) 
					if (randomUniform() < .5)
			       			mir = -1.0;	
				return  mir * fabsf(input);
			}
			return input;
		case ORDER_SFO:
			input *= scale_param;
			if (fold_param){
				if (mirror) 
					if (randomUniform() < .5)
			       			mir = -1.0;	
				input =  mir * fabsf(input);
			}
			return input + offset_param;
		case ORDER_FOS:
			if (fold_param){
				if (mirror) 
					if (randomUniform() < .5)
			       			mir = -1.0;	
				input =  mir * fabsf(input);
			}
			input += offset_param;
			return input * scale_param;
		case ORDER_FSO:
			if (fold_param){
				if (mirror) 
					if (randomUniform() < .5)
			       			mir = -1.0;	
				input =  mir * fabsf(input);
			}
			input *= scale_param;
			return input + offset_param;
	}
}

float OSFutil::inv_process(float input, float *out2){
	*out2 = NAN;
	switch(cur_order) {
		case(ORDER_OSF):
			if (fold_param) {
				if (input<0 && !mirror)
					return NAN;
				*out2 = -input;
			}
			input /= scale_param;
			*out2 /= scale_param;
			*out2 -= offset_param;
			return input - offset_param;
		case(ORDER_OFS):
			input /= scale_param;
			if (fold_param) {
				if (input<0 && !mirror)
					return NAN;
				*out2 = -input;
			}
			*out2 -= offset_param;
			return input - offset_param;
		case(ORDER_SOF):
			if (fold_param) {
				if (input<0 && !mirror)
					return NAN;
				*out2 = -input;
			}
			input -= offset_param;
			*out2 -= offset_param;
			*out2 /= scale_param;
			return input / scale_param;
		case(ORDER_SFO):
			input -= offset_param;
			if (fold_param) {
				if (input<0 && !mirror)
					return NAN;
				*out2 = -input;
			}
			*out2 /= scale_param;
			return input / scale_param;
		case(ORDER_FOS):
			input /= scale_param;
			input -= offset_param;
			if (fold_param) {
				if (input<0 && !mirror)
					return NAN;
				*out2 = -input;
			}
			return input;
		case(ORDER_FSO):
			input -= offset_param;
			input /= scale_param;
			if (fold_param) {
				if (input<0 && !mirror)
					return NAN;
				*out2 = -input;
			}
			return input;
	}

}
