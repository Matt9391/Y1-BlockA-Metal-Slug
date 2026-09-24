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
	Printer();

	void drawText(const HUDText& text, Surface* font, Surface* screen);

private:
	//split string into multiple lines based on '\n' character
	char** splitLines(const char* text, int& lineCount);
	void drawLine(const HUDText& text, const float4& fontSize, const vec2& clipValue, Surface* font, Surface* screen);
	void drawChar(const vec2& start, const vec2& end, float charScale, uint* source, uint* destination, Surface* font, const int& screenWidth);

	const int MAXLINES = 10;
	static const int MAXLINEWIDTH = 100;
};