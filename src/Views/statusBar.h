#pragma once

#include <global_include.h>

#define STATUSBAR_HEIGHT 30

class StatusBar: public View {
public:
	StatusBar();
	~StatusBar();

	int HandleInput() override;
	int Display() override;

	
private:
	vita2d_font *font_25;
	vita2d_texture *img_statsbar_battery;

	#ifdef PSP2SHELL
	char vitaip[16] = {0};
	#endif
};
