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

ALLEGRO_DISPLAY* MapGraphics::getDisplay()
{
	return display;
}

eventCode MapGraphics::dispatchClick(int x, int y)
{
	if ((0.0 < x < M_WIDTH) && (0.0 < y < M_HEIGHT))	
	{
		//Se cliqueo dentro del mapa
		for (int i = 0; i < (FILA); i++) {
			for (int j = 0; j < (COLUMNA); j++) {  
			
				if (((T_WIDTH * j) < x < ((T_WIDTH * j) + T_WIDTH)) && 
					((T_HEIGHT * i) < y < ((T_HEIGHT * i) + T_HEIGHT)))
				{
					//Se cliqueo en la posicion ij (i:fila(16). j:col(12))
					switch (i)
					{
					case 0:
					{
						switch (j)
						{
						case 0: return A1; break;
						case 1: return A2; break;
						case 2:return A3; break;
						case 3:return A4; break;
						case 4:return A5; break;
						case 5:return A6; break;
						case 6:return A7; break;
						case 7:return A8; break;
						case 8:return A9; break;
						case 9:return A10; break;
						case 10:return A11; break;
						case 11:return A12; break;
						default:
							break;
						}
						break;
					}
					case 1:
					{
						switch (j)
						{
						case 0: return B1; break;
						case 1: return B2; break;
						case 2:return B3; break;
						case 3:return B4; break;
						case 4:return B5; break;
						case 5:return B6; break;
						case 6:return B7; break;
						case 7:return B8; break;
						case 8:return B9; break;
						case 9:return B10; break;
						case 10:return B11; break;
						case 11:return B12; break;
						default: break;
						}
						break;
					}
					case 2:
					{
						switch (j)
						{
						case 0:return C1; break;
						case 1:return C2; break;
						case 2:return C3; break;
						case 3:return C4; break;
						case 4:return C5; break;
						case 5:return C6; break;
						case 6:return C7; break;
						case 7:return C8; break;
						case 8:return C9; break;
						case 9:return C10; break;
						case 10:return C11; break;
						case 11:return C12; break;
						default: break;
						}
						break;
					}
					case 3:
					{
						switch (j)
						{
						case 0:return D1; break;
						case 1:return D2; break;
						case 2:return D3; break;
						case 3:return D4; break;
						case 4:return D5; break;
						case 5:return D6; break;
						case 6:return D7; break;
						case 7:return D8; break;
						case 8:return D9; break;
						case 9:return D10; break;
						case 10:return D11; break;
						case 11:return D12; break;
						default: break;
						}
						break;
					}
					case 4:
					{
						switch (j)
						{
						case 0:return E1; break;
						case 1:return E2; break;
						case 2:return E3; break;
						case 3:return E4; break;
						case 4:return E5; break;
						case 5:return E6; break;
						case 6:return E7; break;
						case 7:return E8; break;
						case 8:return E9; break;
						case 9:return E10; break;
						case 10:return E11; break;
						case 11:return E12; break;
						default: break;
						}
						break;
					}
					case 5:
					{
						switch (j)
						{
						case 0:return F1; break;
						case 1:return F2; break;
						case 2:return F3; break;
						case 3:return F4; break;
						case 4:return F5; break;
						case 5:return F6; break;
						case 6:return F7; break;
						case 7:return F8; break;
						case 8:return F9; break;
						case 9:return F10; break;
						case 10:return F11; break;
						case 11:return F12; break;
						default: break;
						}
						break;
					}
					case 6:
					{
						switch (j)
						{
						case 0:return G1; break;
						case 1:return G2; break;
						case 2:return G3; break;
						case 3:return G4; break;
						case 4:return G5; break;
						case 5:return G6; break;
						case 6:return G7; break;
						case 7:return G8; break;
						case 8:return G9; break;
						case 9:return G10; break;
						case 10:return G11; break;
						case 11:return G12; break;
						default: break;
						}
						break;
					}
					case 7:
					{
						switch (j)
						{
						case 0:return H1; break;
						case 1:return H2; break;
						case 2:return H3; break;
						case 3:return H4; break;
						case 4:return H5; break;
						case 5:return H6; break;
						case 6:return H7; break;
						case 7:return H8; break;
						case 8:return H9; break;
						case 9:return H10; break;
						case 10:return H11; break;
						case 11:return H12; break;
						default: break;
						}
						break;
					}
					case 8:
					{
						switch (j)
						{
						case 0:return I1; break;
						case 1:return I2; break;
						case 2:return I3; break;
						case 3:return I4; break;
						case 4:return I5; break;
						case 5:return I6; break;
						case 6:return I7; break;
						case 7:return I8; break;
						case 8:return I9; break;
						case 9:return I10; break;
						case 10:return I11; break;
						case 11:return I12; break;
						default: break;
						}
						break;
					}
					case 9:
					{
						switch (j)
						{
						case 0:return J1; break;
						case 1:return J2; break;
						case 2:return J3; break;
						case 3:return J4; break;
						case 4:return J5; break;
						case 5:return J6; break;
						case 6:return J7; break;
						case 7:return J8; break;
						case 8:return J9; break;
						case 9:return J10; break;
						case 10:return J11; break;
						case 11:return J12; break;
						default: break;
						}
						break;
					}
					case 10:
					{
						switch (j)
						{
						case 0:return K1; break;
						case 1:return K2; break;
						case 2:return K3; break;
						case 3:return K4; break;
						case 4:return K5; break;
						case 5:return K6; break;
						case 6:return K7; break;
						case 7:return K8; break;
						case 8:return K9; break;
						case 9:return K10; break;
						case 10:return K11; break;
						case 11:return K12; break;
						default: break;
						}
						break;
					}
					case 11:
					{
						switch (j)
						{
						case 0:return L1; break;
						case 1:return L2; break;
						case 2:return L3; break;
						case 3:return L4; break;
						case 4:return L5; break;
						case 5:return L6; break;
						case 6:return L7; break;
						case 7:return L8; break;
						case 8:return L9; break;
						case 9:return L10; break;
						case 10:return L11; break;
						case 11:return L12; break;
						default: break;
						}
						break;
					}
					case 12:
					{
						switch (j)
						{
						case 0:return M1; break;
						case 1:return M2; break;
						case 2:return M3; break;
						case 3:return M4; break;
						case 4:return M5; break;
						case 5:return M6; break;
						case 6:return M7; break;
						case 7:return M8; break;
						case 8:return M9; break;
						case 9:return M10; break;
						case 10:return M11; break;
						case 11:return M12; break;
						default: break;
						}
						break;
					}
					case 13:
					{
						switch (j)
						{
						case 0:return N1; break;
						case 1:return N2; break;
						case 2:return N3; break;
						case 3:return N4; break;
						case 4:return N5; break;
						case 5:return N6; break;
						case 6:return N7; break;
						case 7:return N8; break;
						case 8:return N9; break;
						case 9:return N10; break;
						case 10:return N11; break;
						case 11:return N12; break;
						default: break;
						}
						break;
					}
					case 14:
					{
						switch (j)
						{
						case 0:return O1; break;
						case 1:return O2; break;
						case 2:return O3; break;
						case 3:return O4; break;
						case 4:return O5; break;
						case 5:return O6; break;
						case 6:return O7; break;
						case 7:return O8; break;
						case 8:return O9; break;
						case 9:return O10; break;
						case 10:return O11; break;
						case 11:return O12; break;
						default: break;
						}
						break;
					}
					case 15:
					{
						switch (j)
						{
						case 0:return P1; break;
						case 1:return P2; break;
						case 2:return P3; break;
						case 3:return P4; break;
						case 4:return P5; break;
						case 5:return P6; break;
						case 6:return P7; break;
						case 7:return P8; break;
						case 8:return P9; break;
						case 9:return P10; break;
						case 10:return P11; break;
						case 11:return P12; break;
						default: break;
						}
						break;
					}
					default: break;
				}
			
			}
		}

	}

	else if ((M_WIDTH < x < al_get_display_width(display)) && 
		(al_get_font_line_height(menuFont) * 2 < y < (al_get_font_line_height(menuFont) * 2 + al_get_bitmap_height(attackButton))))
	{
		//Se apreto ATTACK
		return ATTACK;
	}
	else if ((M_WIDTH < x < al_get_display_width(display)) && 
		((al_get_font_line_height(menuFont) * 2 + al_get_bitmap_height(attackButton)) < y < (al_get_font_line_height(menuFont) * 2 + al_get_bitmap_height(attackButton) + al_get_bitmap_height(purchaseButton))))
	{
		//Se apreto PURCHASE
		return PURCHASE;
	}
		
		
	for (int i = 0; i < 9; i++) 
	{
		if((M_WIDTH + 10 < x < al_get_display_width(display))
			&& ((al_get_font_line_height(menuFont) + al_get_font_descent(menuFont) + al_get_font_ascent(menuFont)*i + al_get_bitmap_height(attackButton) + al_get_bitmap_height(purchaseButton)) 
				< y < 
				(al_get_font_line_height(menuFont) + al_get_font_descent(menuFont) + al_get_font_ascent(menuFont)*i + al_get_bitmap_height(attackButton) + al_get_bitmap_height(purchaseButton)) + al_get_font_line_height(menuFont)))
		{
			// Se apreto para comprar la unidad de numero i de la lista
			return 0;
		}
	
	
	}

	return 0;
}

//void MapGraphics::setMap(Map * map)
//{
//	this->map = map;
//}
