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
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			al_destroy_bitmap(bitmapArray[i][j]);
			if (unitsArray[i][j] != NULL) { al_destroy_bitmap(unitsArray[i][j]); }
		}
	}
}

void MapGraphics::showMap()
{
	for (int i = 0; i < (FILA) ; i++) {
		for (int j = 0; j < (COLUMNA); j++) {

			al_draw_scaled_bitmap(bitmapArray[i][j], 0.0, 0.0,
				al_get_bitmap_width(bitmapArray[i][j]), al_get_bitmap_height(bitmapArray[i][j]),
				j*T_WIDTH, i* T_HEIGHT, T_WIDTH, T_HEIGHT, 0);
			if(unitsArray[i][j] != NULL)
				al_draw_scaled_bitmap(unitsArray[i][j], 0.0, 0.0,
					al_get_bitmap_width(unitsArray[i][j]), al_get_bitmap_height(unitsArray[i][j]),
					j*T_WIDTH, i* T_HEIGHT, T_WIDTH, T_HEIGHT, 0);
		}
	}
	al_flip_display();
}

void MapGraphics::loadBitmaps()
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {

#ifndef NOFOG
			if (!(map->getTile(i, j)->getFog())) {
#endif // NOFOG
				//despues rechequear lo del fog segun el equipo
				if (map->getTile(i, j)->getUnit() != NULL)
					unitsArray[i][j] = al_load_bitmap(map->getTile(i, j)->getUnit()->getPath().c_str());
				else
					unitsArray[i][j] = NULL;
				if (map->getTile(i, j)->getBuilding() != NULL)
					bitmapArray[i][j] = al_load_bitmap(map->getTile(i, j)->getBuilding()->getPath().c_str());

				else
					bitmapArray[i][j] = al_load_bitmap(map->getTile(i, j)->getTerrain()->getPath().c_str());
				if (!bitmapArray[i][j] && !unitsArray[i][j])
					printf("Failed to load Bitmap [%d][%d]\n", i, j);
#ifndef NOFOG
		}

			else
			{
				unitsArray[i][j] = NULL;
				bitmapArray[i][j] = al_load_bitmap(FOG_IMAGE);
			}
#endif // NOFOG

		}
	}
}

void MapGraphics::setMap(Map * map)
{
	this->map = map;
}
