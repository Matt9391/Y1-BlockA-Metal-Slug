//****************************************
//*** Printer.cpp - Debug Print Utility ***
//***
//*** An add on for the Template framework
//*** written by David Jones, 2026
//***
//****************************************
#pragma once

class Tmpl8::Surface;
class vec2;
struct HUDText;

typedef unsigned int uint;


class Printer
{

public:
	//initialize the font surface
	Printer(Surface* fontSource);

	void drawText(const HUDText& text, Surface* screen);
	vec2 getFontSize() const;
private:
	//split string into multiple lines based on '\n' character
	char** splitLines(const char* text, int& lineCount);
	void drawLine(const HUDText& text, const vec2& fontSize, const vec2& clipValue, Surface* screen);
	void drawChar(const vec2& start, const vec2& end, int charScale, uint* source, uint* destination, const int& screenPitch);

	//font surface and its character dimensions
	Surface* font;
	int fontHeight;
	int fontWidth;

	const int MAXLINES = 10;
	static const int MAXLINEWIDTH = 100;
};