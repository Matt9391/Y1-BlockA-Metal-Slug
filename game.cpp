// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "lib/json.hpp"

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------

void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y);
// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
nlohmann::json data;

Surface* bg = new Surface("assets/bg.png");
Surface* bg2 = new Surface("assets/collisionTile.png");

void Game::Init()
{
	// anything that happens only once at application start goes here
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

int b = 0;
// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float /* deltaTime */ )
{
	//screen->Clear(0xff0000);
	if (GetAsyncKeyState(VK_LEFT)) b-= 10;
	if (GetAsyncKeyState(VK_RIGHT)) b+= 10;

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

				drawTile(8, srcCol, srcRow, screen, bg, destX + b, destY);
			}
		}
}


void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y) {

	//check if the tile is outside the screen
	if (x + tileSize < 0 || y + tileSize < 0 || x > screen->width || y > screen->height)
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
	if (x + tileSize > screen->width)  maxX = screen->width - x;
	if (y + tileSize > screen->height) maxY = screen->height - y;

	//get pointers to the source tile and destination on screen
	uint* source = tileset->pixels + tx * tileSize + (ty * tileSize) * tileset->width;
	//add the clipping offsets
	source += dy * tileset->width;
	//set destination on screen with clipping offsets
	uint* destination = screen->pixels + x + (y + dy) * screen->width;

	//"transparent" pixel value, actually its magenta because it's easy to visualize in photoshop
	const uint transparent = 0xFFFF00FF;

	//for each pixel in the tile area
	for (int i = dy; i < maxY; i++) {
		for (int j = dx; j < maxX; j++) {
			//if the pixel is not "transparent" copy it to the screen
			if (source[j] != transparent)
				destination[j] = source[j];
		}

		//then move to the next row
		source += tileset->width;
		destination += screen->width;
	}
}