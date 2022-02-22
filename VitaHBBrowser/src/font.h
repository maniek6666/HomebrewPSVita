#pragma once


#include <string>
#include <unordered_map>
#include "shapes.h"
#include "macros.h"

#define FONT_DIR VHBB_RESOURCES "/fonts/"

class Font {
public:
	Font(const std::string &path, unsigned int fSize);

	int Draw(const Point &pt, const std::string &text, unsigned int color = COLOR_WHITE,
	         unsigned int maxWidth = 0, unsigned int maxHeight = 0);
	
	int DrawClip(const Point &pt, const std::string &text, const Rectangle &clipRect, unsigned int color=COLOR_WHITE);
	int DrawCentered(const Rectangle &rect, const std::string& text, unsigned int color = COLOR_WHITE, bool clip = false,
	                 int offsetX = 0, int offsetY = 0);
	int DrawCenteredVertical(const Rectangle &rect, const std::string& text, unsigned int color = COLOR_WHITE,
	                         bool clip = false, int offsetX = 0, int offsetY = 0);
	std::string FitString(const std::string& text, int maxWidth);

	Dimensions BoundingBox(const std::string& text);
	inline unsigned int BaselineOffset() const { return size / 4; }
	inline double BaselineOffsetF() const { return size / 4.0; }
	inline unsigned int getSize() const { return size; }

	static std::unordered_map<std::pair<std::string, unsigned int>, vita2d_font*> fontCache;
private:
	vita2d_font *font;
	unsigned int size;
};
