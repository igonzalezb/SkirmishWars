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

	passButton = al_load_bitmap("resources/images/PASS.png");
	if (!passButton)
	{
		printf("Failed to create pass button!\n");
	}

	menuFont = al_load_font(FONT_MENU, 30, 0);
	if (!menuFont) {
		fprintf(stderr, "failed to create menuFont!\n");
	}

	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			bitmapArray[i][j] = NULL;
			unitsArray[i][j] = NULL;
		}
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

void MapGraphics::showMap(Game* gameInfo)
{
	al_clear_to_color(al_map_rgb(0.0, 170.0, 0.0));
	al_draw_text(menuFont, al_map_rgb(255, 255, 255), M_WIDTH + 10, 0.0, 0.0, "MONEY: $5");
	//al_draw_text(menuFont, al_map_rgb(255, 255, 255), M_WIDTH + 10, al_get_font_line_height(menuFont), 0.0, "MONEY: $5");
	
	al_draw_scaled_bitmap(attackButton, 0.0, 0.0,
		al_get_bitmap_width(attackButton), al_get_bitmap_height(attackButton),
		M_WIDTH, al_get_font_line_height(menuFont), R_WIDTH, M_HEIGHT / 8.0, 0);
	
	al_draw_scaled_bitmap(passButton, 0.0, 0.0,
		al_get_bitmap_width(passButton), al_get_bitmap_height(passButton),
		M_WIDTH, al_get_font_line_height(menuFont) + (M_HEIGHT / 8.0), R_WIDTH, M_HEIGHT / 8.0, 0);

	al_draw_scaled_bitmap(purchaseButton, 0.0, 0.0,
		al_get_bitmap_width(purchaseButton), al_get_bitmap_height(purchaseButton),
		M_WIDTH, al_get_font_line_height(menuFont) + (M_HEIGHT / 8.0)*2, R_WIDTH, M_HEIGHT / 8.0, 0);

	/*list<Unit>::iterator iterator1 = gameInfo->data->getUnitList().begin();

	for (int i = 0; i < 9; i++) {
		string currItem;
		advance(iterator1, i);

		currItem = iterator1->getName() + "$";
		currItem += iterator1->getCost();
		

		al_draw_text(menuFont, al_map_rgb(255, 255, 255), M_WIDTH + 10,
			al_get_font_line_height(menuFont) + al_get_font_descent(menuFont) + al_get_font_ascent(menuFont)*i + al_get_bitmap_height(attackButton) + al_get_bitmap_height(purchaseButton), 0.0,
			currItem.c_str());
	}*/

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
				
				
				//ACA VA LO DE IS SELECTED!!
				//gameInfo->myMap->possibleMoves(gameInfo->myMap->getTile(i, j)->getUnit(), i, j);	//Esto no va aca!!
				//for (int p = 0; p < (FILA); p++) {
				//	for (int q = 0; q < (COLUMNA); q++) {
				//		if (gameInfo->myMap->canMove[p][q]) {
				//			al_draw_rectangle(q*T_WIDTH, p* T_HEIGHT,
				//				(q*T_WIDTH) + T_WIDTH,
				//				(p* T_HEIGHT) + T_HEIGHT,
				//				al_color_name("green"), 4.0);
				/*		}
					}
				}*/
			}
		}
	}

	al_flip_display();
}

void MapGraphics::loadBitmaps(Map * map)
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			
			if (bitmapArray[i][j] != NULL) { al_destroy_bitmap(bitmapArray[i][j]);; }
			if (unitsArray[i][j] != NULL) { al_destroy_bitmap(unitsArray[i][j]); }
			unitsArray[i][j] = NULL;
			bitmapArray[i][j] = NULL;


#ifndef NOFOG
			if (!(map->getTile(i, j)->getFog())) {
#endif // NOFOG
				//despues rechequear lo del fog segun el equipo
				if ((map->getTile(i, j)->getUnit() != NULL)) {
					unitsArray[i][j] = al_load_bitmap(map->getTile(i, j)->getUnit()->getPath().c_str());
					//cout << "path de la unit " << map->getTile(i, j)->getUnit()->getPath() << endl;
				}
				if ((map->getTile(i, j)->getBuilding() != NULL))
					bitmapArray[i][j] = al_load_bitmap(map->getTile(i, j)->getBuilding()->getPath().c_str());

				else if(map->getTile(i,j)->getTerrain() != NULL)
					bitmapArray[i][j] = al_load_bitmap(map->getTile(i, j)->getTerrain()->getPath().c_str());
				
				if (!bitmapArray[i][j])
				{
					printf("Failed to load Bitmap [%d][%d]\n", i, j);
				}
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

ALLEGRO_DISPLAY* MapGraphics::getDisplay()
{
	return display;
}

eventCode MapGraphics::dispatchClick(int x, int y, Game * gameInfo)
{
	if (((0.0 < x) && (x < M_WIDTH)) && ((0.0 < y) && (y < M_HEIGHT)))
	{
		//Se cliqueo dentro del mapa
		for (int i = 0; i < (FILA); i++) {
			for (int j = 0; j < (COLUMNA); j++) {

				if (((((T_WIDTH * j) < x) && (x < ((T_WIDTH * j) + T_WIDTH)))) &&
					((((T_HEIGHT * i) < y) && (y < ((T_HEIGHT * i) + T_HEIGHT)))))
				{
					//Se cliqueo en la posicion ij (i:fila(16). j:col(12))
#ifdef DEBUG
					cout << "SE APRETO la fila:" << i << " , columna " << j << endl;
#endif // DEBUG
					gameInfo->setTileSelected(i, j);

					return TILE;
				}
			}
		}
	}

	else if ((((M_WIDTH < x) && (x < al_get_display_width(display)))) && 
		((al_get_font_line_height(menuFont) < y) && (y < (al_get_font_line_height(menuFont) + (M_HEIGHT / 8.0)))))
	{
		//Se apreto ATTACK
#ifdef DEBUG
		cout << "Se apreto Attack" << endl;
#endif // DEBUG
		return BO_ATTACK;
	}
	else if (((M_WIDTH < x) && (x < al_get_display_width(display))) &&
		(((al_get_font_line_height(menuFont) + (M_HEIGHT / 8.0)) < y) && (y < ((al_get_font_line_height(menuFont) + (M_HEIGHT / 8.0)*2)))))
	{
		//Se apreto PASS
#ifdef DEBUG
		cout << "Se apreto Pass" << endl;
#endif // DEBUG
		return PASS;
	}

	else if (((M_WIDTH < x) && (x < al_get_display_width(display))) && 
		(((((al_get_font_line_height(menuFont) + (M_HEIGHT / 8.0) * 2))) < y) && (y < (((al_get_font_line_height(menuFont) + (M_HEIGHT / 8.0) * 3))))))
	{
		//Se apreto PURCHASE
#ifdef DEBUG
		cout << "Se apreto Purchase\n" << endl;
#endif // DEBUG
		return BO_PURCHASE;
	}
		
		//VOLER A PONER!!!!!!!!!!!!!!
//	for (int i = 1; i <= 9; i++) 
//	{
//		if(((M_WIDTH + 10 < x) && (x < al_get_display_width(display)))
//			&& (((al_get_font_line_height(menuFont) + al_get_font_descent(menuFont) + al_get_font_ascent(menuFont)*i + al_get_bitmap_height(attackButton) + al_get_bitmap_height(purchaseButton)) 
//				< y) && (y < 
//				(al_get_font_line_height(menuFont) + al_get_font_descent(menuFont) + al_get_font_ascent(menuFont)*i + al_get_bitmap_height(attackButton) + al_get_bitmap_height(purchaseButton)) + al_get_font_line_height(menuFont))))
//		{
//			// Se apreto para comprar la unidad de numero i de la lista
//		
//			list<Unit>::iterator it3 = gameInfo->data->getUnitList().begin();
//			advance(it3, i);
//			Unit *currUnit = new Unit(it3);
//			currUnit->setTeam(gameInfo->playerMe->getTeam());
//			gameInfo->setNewUnit(currUnit);
//		}
//			
//#ifdef DEBUG
//			cout << "Se apreto comprar la opcion" << i << endl;
//#endif // DEBUG
//			return NEW_UNIT;
//	
//	}
#ifdef DEBUG
	cout << "No se apreto nada relevante" << endl;
#endif // DEBUG

	return NO_EV;		//VER!!!!!
}