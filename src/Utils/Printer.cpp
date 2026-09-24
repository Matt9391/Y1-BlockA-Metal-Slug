#include "precomp.h"
#include <Printer.h>
#include <HUDText.h>




Printer::Printer(){}

void Printer::drawText(const HUDText& text, Surface* font, Surface* screen) {
	if (font == nullptr) {
		printf("Font not initialized yet! Initialize it before using");
		return;
	}

	int nLines = 0;
	char** lines = splitLines(text.text, nLines);

	int size = (text.resourceId == ID_FONT_GREY || text.resourceId == ID_FONT_ORANGE) ? 18 : 9;
	float4 fontSize(size, size, size, size);

	//check if the text is outside the screen bounds
	if (text.pos.x + fontSize.x * text.scale < 0 || text.pos.y + fontSize.y * text.scale < 0 || text.pos.x > screen->width|| text.pos.y > screen->height)
		return;


	//clipping variables
	int dx = 0, dy = 0;
	//clip position and size if the text is partially outside the screen
	if (text.pos.x < 0) dx = int(-text.pos.x);
	if (text.pos.y < 0) dy = int(-text.pos.y);
	if (text.pos.x + fontSize.x > screen->width)  fontSize.w = float(screen->width - text.pos.x);
	if (text.pos.y + fontSize.y > screen->height) fontSize.z = float(screen->height - text.pos.y);


	int lineCounter = 0;


	for (int i = 0; i < nLines; i++) {
		HUDText line;

		strcpy(line.text, lines[i]);
		line.pos = text.pos + vec2(0, float(size * lineCounter * text.scale));
		line.scale = text.scale;

		drawLine(
			line,
			fontSize,
			vec2(float(dx), float(dy)),
			font,
			screen
		);

		lineCounter++;
	}

	for (int i = 0; i < MAXLINES; i++)
		delete[] lines[i];

	delete[] lines;
}

void Printer::drawLine(const HUDText& text, const float4& fontSize, const vec2& clipValue, Surface* font, Surface* screen) {
	int count = 0;
	printf("w: %d\n", (*font).width);

	for (int i = 0; text.text[i] != '\0'; i++) {
		char character = text.text[i];
		//get character index in the font surface
		int index = int(character) - 32;
		//get source based on character index
		uint* source = (*font).pixels + index * int(fontSize.y);
		//add clipping offset
		source += int(clipValue.y) * (*font).width;

		//set destination on screen with clipping offsets and line offset
		//get the buffer off the screen and the calculate the position based on character count and line counter
		uint* destination = screen->pixels + int(text.pos.x + fontSize.x * text.scale * count) +
			int(text.pos.y + clipValue.y) * screen->width;

		vec2 fontSize2D = vec2(fontSize.w, fontSize.z);
		drawChar(clipValue, fontSize2D, text.scale, source, destination, font, screen->width);

		count++;
	}

}

void Printer::drawChar(const vec2& start,const vec2& end,float scale,uint* source,uint* destination,Surface* font,const int& screenWidth){
	int destWidth = int(end.x * scale);
	int destHeight = int(end.y * scale);

	for (int y = 0; y < destHeight; y++)
	{
		int sourceY = int(y / scale);

		for (int x = 0; x < destWidth; x++)
		{
			int sourceX = int(x / scale);

			uint pixel = source[sourceY * font->width + sourceX];

			if (pixel != 0xFFb5e61d)
			{
				destination[x + y * screenWidth] = pixel;
			}
		}
	}
}

//split string into multiple lines based on '\n' character
char** Printer::splitLines(const char* text, int& lineCount) {
	char** lines = new char*[MAXLINES];

	for (int i = 0; i < MAXLINES; i++) {
		lines[i] = new char[MAXLINEWIDTH];
	}

	char buffer[MAXLINEWIDTH];
	int j = 0;
	lineCount = 0;

	for (int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == '\n')
		{
			buffer[j] = '\0';
			strcpy(lines[lineCount++], buffer);

			j = 0;
		}
		else
		{
			if (j < MAXLINEWIDTH - 1)
				buffer[j++] = text[i];
		}
	}

	if (j > 0 && lineCount < MAXLINES)
	{
		buffer[j] = '\0';
		strcpy(lines[lineCount++], buffer);
	}

	return lines;
}

