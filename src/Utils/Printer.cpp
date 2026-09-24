#include "precomp.h"
#include <Printer.h>
#include <HUDText.h>




Printer::Printer(Surface* fontSource) :
	font(fontSource),
	//counted manually from the font source image (not ideal)
	fontHeight(18),
	fontWidth(18)
{

}

void Printer::drawText(const HUDText& text, Surface* screen) {
	if (font == nullptr) {
		printf("Font not initialized yet! Initialize it before using");
		return;
	}

	int nLines = 0;
	char** lines = splitLines(text.text, nLines);

	//check if the text is outside the screen bounds
	if (text.pos.x + fontWidth * text.scale < 0 || text.pos.y + fontHeight * text.scale < 0 || text.pos.x > screen->width|| text.pos.y > screen->height)
		return;

	//clipping variables
	int dx = 0, dy = 0;
	vec2 fontSize = vec2(float(fontWidth), float(fontHeight));
	//clip position and size if the text is partially outside the screen
	if (text.pos.x < 0) dx = int(-text.pos.x);
	if (text.pos.y < 0) dy = int(-text.pos.y);
	if (text.pos.x + fontWidth > screen->width)  fontSize.x = float(screen->width - text.pos.x);
	if (text.pos.y + fontHeight > screen->height) fontSize.y = float(screen->height - text.pos.y);


	int lineCounter = 0;


	for (int i = 0; i < nLines; i++) {
		HUDText line;

		strcpy(line.text, lines[i]);
		line.pos = text.pos + vec2(0, float(this->fontHeight * lineCounter * text.scale));
		line.scale = text.scale;

		drawLine(
			line,
			fontSize,
			vec2(float(dx), float(dy)),
			screen
		);

		lineCounter++;
	}

	for (int i = 0; i < MAXLINES; i++)
		delete[] lines[i];

	delete[] lines;
}

void Printer::drawLine(const HUDText& text, const vec2& fontSize, const vec2& clipValue, Surface* screen) {
	int count = 0;
	printf("w: %d\n", (*font).width);

	for (int i = 0; text.text[i] != '\0'; i++) {
		char character = text.text[i];
		//get character index in the font surface
		int index = int(character) - 32;
		//get source based on character index
		uint* source = (*font).pixels + index * fontWidth;
		//add clipping offset
		source += int(clipValue.y) * (*font).width;

		//set destination on screen with clipping offsets and line offset
		//get the buffer off the screen and the calculate the position based on character count and line counter
		uint* destination = screen->pixels + int(text.pos.x + fontWidth * text.scale * count) +
			int(text.pos.y + clipValue.y) * screen->width;

		drawChar(clipValue, fontSize, text.scale, source, destination, screen->width);

		count++;
	}

}

void Printer::drawChar(const vec2& start, const vec2& end, int charScale, uint* source, uint* destination, const int& screenPitch) {
	//draw character pixel by pixel with scaling
	//si/sj are scale iterators

	//iterate through original rows
	for (int i = int(start.y); i < end.y; i++) {
		//for each row it iterates scale times the same row
		for (int si = 0; si < charScale; si++) {
			//jIndex is the index of the pixel needed to be drawn
			int jIndex = 0;

			//iterate through original columns
			for (int j = int(start.x); j < end.x * charScale; j += charScale) {

				//for each column it iterates scale times the same column
				for (int sj = 0; sj < charScale; sj++) {

					//if the source pixel is not black (transparent) copy it to the screen
					//black pixel used for transparent/void pixels in the font sprite
					if (source[jIndex] != 0x0)
						destination[j + sj] = source[jIndex];
				}
				jIndex++;
			}
			destination += screenPitch;
		}
		source += (*font).width;
	}
}

vec2 Printer::getFontSize() const {
	return vec2(float(fontWidth), float(fontHeight));
}

//split string into multiple lines based on '\n' character
char**  Printer::splitLines(const char* text, int& lineCount) {
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

