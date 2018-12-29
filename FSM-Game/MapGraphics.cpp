#include "MapGraphics.h"

MapGraphics::MapGraphics()
{
	display = al_create_display(1000, 600);
	if (!display)
	{
		printf("Failed to create display!\n");
	}
	
	attackButton = al_load_bitmap("resources/images/AttackButton.png");
	if(!attackButton)
	{
		printf("Failed to create attack button!\n");
	}

	purchaseButton = al_load_bitmap("resources/images/purchase.png");
	if (!purchaseButton)
	{
		printf("Failed to create purchase button!\n");
	}

	menuFont = al_load_font(FONT_MENU, 30, 0);
	if (!menuFont) {
		fprintf(stderr, "failed to create menuFont!\n");
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

void MapGraphics::showMap(Map * map)
{
	al_clear_to_color(al_map_rgb(0.0, 170.0, 0.0));
	al_draw_text(menuFont, al_map_rgb(255, 255, 255), M_WIDTH + 10, 0.0, 0.0, "TIMER 00:00:00");
	al_draw_text(menuFont, al_map_rgb(255, 255, 255), M_WIDTH + 10, al_get_font_line_height(menuFont), 0.0, "MONEY: $5");
	
	al_draw_scaled_bitmap(attackButton, 0.0, 0.0,
		al_get_bitmap_width(attackButton), al_get_bitmap_height(attackButton),
		M_WIDTH, al_get_font_line_height(menuFont)*2, R_WIDTH, M_HEIGHT / 6.0, 0);

	al_draw_scaled_bitmap(purchaseButton, 0.0, 0.0,
		al_get_bitmap_width(purchaseButton), al_get_bitmap_height(purchaseButton),
		M_WIDTH, al_get_font_line_height(menuFont)*2 + al_get_bitmap_height(attackButton), R_WIDTH, M_HEIGHT / 6.0, 0);


	for (int i = 0; i < 9; i++) {
		al_draw_text(menuFont, al_map_rgb(255, 255, 255), M_WIDTH + 10,
			al_get_font_line_height(menuFont) + al_get_font_descent(menuFont) + al_get_font_ascent(menuFont)*i + al_get_bitmap_height(attackButton) + al_get_bitmap_height(purchaseButton), 0.0,
			purchaselist[i].c_str());
	}
	bool canMove[FILA][COLUMNA];

	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {

			al_draw_scaled_bitmap(bitmapArray[i][j], 0.0, 0.0,
				al_get_bitmap_width(bitmapArray[i][j]), al_get_bitmap_height(bitmapArray[i][j]),
				j*T_WIDTH, i* T_HEIGHT, T_WIDTH, T_HEIGHT, 0);

		}
	}
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			
			if (unitsArray[i][j] != NULL) {
				al_draw_scaled_bitmap(unitsArray[i][j], 0.0, 0.0,
					al_get_bitmap_width(unitsArray[i][j]), al_get_bitmap_height(unitsArray[i][j]),
					j*T_WIDTH, i* T_HEIGHT, T_WIDTH / 1.3, T_HEIGHT / 1.3, 0);
				
				map->possibleMoves(map->getTile(i, j)->getUnit(), i, j, canMove);	//Esto no va aca!!
				for (int p = 0; p < (FILA); p++) {
					for (int q = 0; q < (COLUMNA); q++) {
						if (canMove[p][q]) {
							al_draw_rectangle(q*T_WIDTH, p* T_HEIGHT,
								(q*T_WIDTH) + T_WIDTH,
								(p* T_HEIGHT) + T_HEIGHT,
								al_color_name("green"), 4.0);
						}
					}
				}
			}
		}
	}

	

	

	al_flip_display();
}

void MapGraphics::loadBitmaps(Map * map)
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {

#ifndef NOFOG
			if (!(map->getTile(i, j)->getFog())) {
#endif // NOFOG
				//despues rechequear lo del fog segun el equipo
				if ((map->getTile(i, j)->getUnit() != NULL))
					unitsArray[i][j] = al_load_bitmap(map->getTile(i, j)->getUnit()->getPath().c_str());
				else
					unitsArray[i][j] = NULL;
				if ((map->getTile(i, j)->getBuilding() != NULL))
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

//void MapGraphics::setMap(Map * map)
//{
//	this->map = map;
//}
