#include "ColorGenerator.h"
#include "World.h"
#include "Maths.h"

ColorGenerator::ColorGenerator() {
	colorProfile.insert(pair<float, Color>(-6.0f, SEA_COLOR));
	colorProfile.insert(pair<float, Color>(-2.0f, COAST_COLOR));
	colorProfile.insert(pair<float, Color>(4.0f, BACK_COLOR));
	colorProfile.insert(pair<float, Color>(10.5f, SNOW_COLOR));
}

Color ColorGenerator::getColor(float height, WorldConfigs configs) {
	//����altitude
	float factor = World::MAX_ALTITUDE / (configs.getMaxHeight() - configs.getWaterHeight());
	float aboveWater = height - configs.getWaterHeight();
	float altitude = factor * aboveWater;

	//����colorProfile���ҵ�height��������ɫ����
	map<float, Color>::iterator it, previous, next;
	for (it = colorProfile.begin(), previous = colorProfile.begin(); it != colorProfile.end(); it++) {
		if (it->first > altitude) {
			next = it;
			break;
		}
		previous = it;
	}
	float blend = Maths::clamp((altitude - previous->first) / (next->first - previous->first), 0, 1);
	return Color::interpolateColors(previous->second, next->second, blend);
}
