// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"

using namespace Tmpl8;

// constructor
Sprite::Sprite( Surface* surface, unsigned int frameCount ) :
	width( surface->width / frameCount ),
	height( surface->height ),
	numFrames( frameCount ),
	currentFrame( 0 ),
	flags( 0 ),
	start( new unsigned int* [frameCount] ),
	reverseStart( new unsigned int* [frameCount]),
	surface( surface ),
	reverseSurface(new Surface(surface->width, surface->height))
{
	InitializeStartData(start, GetBuffer());

	for (int f = 0; f < numFrames; f++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				reverseSurface->pixels[f * width + x + y * surface->width] = 
					surface->pixels[f * width + (width - 1 - x) + y * surface->width];
			}
		}
	}

	InitializeStartData(reverseStart, GetReverseBuffer());
}

// destructor
Sprite::~Sprite()
{
	delete surface;
	delete reverseSurface;
	for (unsigned int i = 0; i < numFrames; i++) delete start[i];
	delete start;
}

// draw sprite to target surface
void Sprite::Draw( Surface* target, int x, int y, bool flipped)
{
	//check if in bounds
	if (x < -width || x >( target->width + width )) return;
	if (y < -height || y >( target->height + height )) return;
	//set the starting coordinate and ending coordinate of drawing
	int x1 = x, x2 = x + width;
	int y1 = y, y2 = y + height;
	//gets the correct index based on the current frame at the top of the sprite
	uint* src = nullptr;
	if (flipped) {
		src = GetReverseBuffer() + currentFrame * width;

	}
	else {
		src = GetBuffer() + currentFrame * width;
	}

	//clip parts out of bounds
	if (x1 < 0) src += -x1, x1 = 0;
	if (x2 > target->width) x2 = target->width;
	if (y1 < 0) src += -y1 * width * numFrames, y1 = 0;
	if (y2 > target->height) y2 = target->height;

	uint* dest = target->pixels;
	
	int xs;

	if (x2 > x1 && y2 > y1)
	{
		//gets the correct pixel where to draw on the screen
		unsigned int addr = y1 * target->width + x1;
		//width and height of the sprite
		const int w = x2 - x1;
		const int h = y2 - y1;

		for (int j = 0; j < h; j++)
		{
			const int line = j + (y1 - y);
			int lsx = 0;
			if (flipped)
				lsx = reverseStart[currentFrame][line] + x;
			else
				lsx = start[currentFrame][line] + x;
			xs = (lsx > x1) ? lsx - x1 : 0;
			for (int i = xs; i < w; i++)
			{
				const uint c1 = *(src + i);
				if (c1 & 0xff000000 && c1 & 0xffffff) *(dest + addr + i) = c1;
			}
			addr += target->width;
			src += width * numFrames;
		}

		
	}
}

// draw scaled sprite
void Sprite::DrawScaled(Surface* target, int x, int y, int scaleFactor, bool flipped)
{
	//check if in bounds
	if (x < -width * scaleFactor || x > (target->width + width * scaleFactor)) return;
	if (y < -height * scaleFactor || y >(target->height + height * scaleFactor)) return;
	//set the starting coordinate and ending coordinate of drawing
	int x1 = x, x2 = x + (width * scaleFactor);
	int y1 = y, y2 = y + (height * scaleFactor);
	//gets the correct index based on the current frame at the top of the sprite
	uint* src = nullptr;

	if (flipped) {
		src = GetReverseBuffer() + currentFrame * width;

	}
	else {
		src = GetBuffer() + currentFrame * width;
	}

	//clip parts out of bounds
	if (x1 < 0) src += -x1 / scaleFactor, x1 = 0;
	if (x2 > target->width) x2 = target->width;
	if (y1 < 0) src += -y1 / scaleFactor * width * numFrames, y1 = 0;
	if (y2 > target->height) y2 = target->height;

	uint* dest = target->pixels;

	int xs;

	if (x2 > x1 && y2 > y1)
	{
		//gets the correct pixel where to draw on the screen
		unsigned int addr = y1 * target->width + x1;
		//width and height of the sprite
		const int w = x2 - x1;
		const int h = y2 - y1;

		int lastLine = 0;
		int line = 0;

		for (int j = 0; j < h; j++)
		{
			lastLine = line;
			line = (j + (y1 - y)) / scaleFactor;
			int lsx = 0;
			if(flipped)
				lsx = reverseStart[currentFrame][line] * scaleFactor + x;
			else
				lsx = start[currentFrame][line] * scaleFactor + x;
			xs = (lsx > x1) ? lsx - x1 : 0;
			for (int i = xs; i < w; i++)
			{
				const uint c1 = *(src + i / scaleFactor);
				if (c1 & 0xff000000 && c1 & 0xffffff) *(dest + addr + i) = c1;
			}
			addr += target->width;
			if(lastLine != line)
				src += width * numFrames;
		}
		
	}
}



void Sprite::DrawScaled( int x1, int y1, int w, int h, Surface* target )
{
	if (width == 0 || height == 0) return;
	for (int x = 0; x < w; x++) for (int y = 0; y < h; y++)
	{
		int u = (int)((float)x * ((float)width / (float)w));
		int v = (int)((float)y * ((float)height / (float)h));
		uint color = GetBuffer()[u + v * width * numFrames];
		if (color & 0xffffff) target->pixels[x1 + x + ((y1 + y) * target->width)] = color;
	}
}

// prepare sprite outline data for faster rendering
void Sprite::InitializeStartData(unsigned int** start, uint* buffer)
{
	for (unsigned int f = 0; f < numFrames; ++f)
	{
		start[f] = new unsigned int[height];
		for (int y = 0; y < height; ++y)
		{
			start[f][y] = width;
			uint* addr = buffer + f * width + y * width * numFrames;
			for (int x = 0; x < width; ++x) if (addr[x])
			{
				start[f][y] = x;
				break;
			}
		}
	}
}