#include "MapGraphics.h"

MapGraphics::MapGraphics()
{
	display = al_create_display(800, 600);
	if (!display)
	{
		printf("Failed to create display!\n");
	}
	
}

MapGraphics::~MapGraphics()
{
}

void MapGraphics::showMap()
{
	for (int i = 0; i < (FILA) ; i++) {
		for (int j = 0; j < (COLUMNA); j++) {

			al_draw_scaled_bitmap(bitmapArray[i][j], 0.0, 0.0,
				al_get_bitmap_width(bitmapArray[i][j]), al_get_bitmap_height(bitmapArray[i][j]),
				j*T_WIDTH, i* T_HEIGHT, T_WIDTH, T_HEIGHT, 0);
		}
	}
	al_flip_display();
}

void MapGraphics::loadBitmaps()
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			if (map->getTile(i, j)->getUnit() != NULL)
				bitmapArray[i][j] = al_load_bitmap(map->getTile(i, j)->getUnit()->getPath().c_str());
			else if(map->getTile(i, j)->getBuilding() != NULL)
				bitmapArray[i][j] = al_load_bitmap(map->getTile(i, j)->getBuilding()->getPath().c_str());
			
			else
				bitmapArray[i][j] = al_load_bitmap(map->getTile(i, j)->getTerrain()->getPath().c_str());
			if (!bitmapArray[i][j])
				printf("Failed to loadBitmap[%d][%d]\n", i, j);
		}
	}
}

void MapGraphics::setMap(Map * map)
{
	this->map = map;
}
