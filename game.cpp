#include "game.h"
#include "surface.h"

#include <cstdio> //printf
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <Windows.h>
namespace Tmpl8
{
	void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y);
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	nlohmann::json data;

	Surface* bg = new Surface("assets/bg.png");
	
	void Game::Init()
	{
		std::ifstream map("assets/gameMap.tmj");
		nlohmann::json data = nlohmann::json::parse(map);

		nlohmann::json layer0 = data.at("layers").at(0);
		nlohmann::json tileData = layer0.at("data");

		int width = layer0.at("width").get<int>();
		int height = layer0.at("height").get<int>();

		int firstgid = data.at("tilesets").at(0).at("firstgid").get<int>();
		int columns = 519; // <- set this to your tileset's actual "columns" value

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int tileId = tileData.at(i * width + j).get<int>();
				if (tileId == 0) continue; // empty tile, nothing to draw

				int localId = tileId - firstgid;
				int srcCol = localId % columns;
				int srcRow = localId / columns;

				int destX = j * 8;
				int destY = i * 8;

				drawTile(8, srcCol, srcRow, screen, bg, destX, destY);
			}
		}
	}


	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}


	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		//screen->Clear(0);



		for (int i = 0; i < 50;i++) {
			for (int j = 0; j < 50; j++) {

			}
		}
		// print something in the graphics window
		screen->Print("hello world", 2, 2, 0xffffff);
		// print something to the text window

	}

	void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y) {

		//check if the tile is outside the screen
		if (x + tileSize < 0 || y + tileSize < 0 || x > screen->GetWidth() || y > screen->GetHeight())
			return;

		//check for void pixel, I chose 'gg' and 'aj' as void pixel based on the tilesetGuide
		//if ((tx + 'a' == this->voidChar[0]) && (ty + 'a' == this->voidChar[1]))
		//	return;

		//clip position and size if the tile is partially outside the screen
		int dx = 0, dy = 0;
		int maxX = tileSize, maxY = tileSize;

		//set clipping values
		if (x < 0) dx = -x;
		if (y < 0) dy = -y;
		if (x + tileSize > screen->GetWidth())  maxX = screen->GetWidth() - x;
		if (y + tileSize > screen->GetHeight()) maxY = screen->GetHeight() - y;

		//get pointers to the source tile and destination on screen
		Pixel* source = tileset->GetBuffer() + tx * tileSize + (ty * tileSize) * tileset->GetPitch();
		//add the clipping offsets
		source += dy * tileset->GetPitch();
		//set destination on screen with clipping offsets
		Pixel* destination = screen->GetBuffer() + x + (y + dy) * screen->GetPitch();

		//"transparent" pixel value, actually its magenta because it's easy to visualize in photoshop
		const Pixel transparent = 0xFFFF00FF;

		//for each pixel in the tile area
		for (int i = dy; i < maxY; i++) {
			for (int j = dx; j < maxX; j++) {
				//if the pixel is not "transparent" copy it to the screen
				if (source[j] != transparent)
					destination[j] = source[j];
			}

			//then move to the next row
			source += tileset->GetPitch();
			destination += screen->GetPitch();
		}
	}
};