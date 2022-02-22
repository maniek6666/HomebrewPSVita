#pragma once



#include "View.h"
#include <texture.h>

class Background : public View
{
public:
	Background();

	int Display() override;
private:
	Texture img_bg;
};

