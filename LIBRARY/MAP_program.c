#include "STD_TYPES.h"
#include "MAP_interface.h"

s32 MAP_s32GetInputValue(s32 InputRangMin,s32 InputRangMax,s32 OutputRangMin,s32 OuputRangMax,s32 InputValue){
	s32 y;
	y=(((OuputRangMax-OutputRangMin)*(InputValue-InputRangMin))/(InputRangMax-InputRangMin))+OutputRangMin;
	return y;
}
