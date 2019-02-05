#include "MapGraphics.h"

MapGraphics::MapGraphics(ALLEGRO_DISPLAY * display)
{
	this->display = display;

	if (!al_reserve_samples(RESERVED_SAMPLES))
	{
		printf("failed to reserve samples!\n");
	}
	
	attackButton = al_load_bitmap("resources/images/buttons/AttackButton.png");
	if(!attackButton)
	{
		printf("Failed to create attack button!\n");
	}

	purchaseButton = al_load_bitmap("resources/images/buttons/PurchaseButton.png");
	if (!purchaseButton)
	{
		printf("Failed to create purchase button!\n");
	}

	passButton = al_load_bitmap("resources/images/buttons/PassButton.png");
	if (!passButton)
	{
		printf("Failed to create pass button!\n");
	}

	

	menuFont = al_load_font(FONT_MENU, 30, 0);
	if (!menuFont) {
		printf("failed to create menuFont!\n");
	}

	hpFont = al_load_font(FONT_MENU, 20, 0);
	if (!hpFont) {
		printf("failed to create menuFont!\n");
	}


	beep = al_load_sample("resources/sounds/beep.wav");

	if (!beep) {
		printf("Failed to create sound beep!\n");
	}

	gameover = al_load_sample("resources/sounds/game_over.wav");

	if (!gameover) {
		printf("Failed to create sound game_over!\n");
	}

	backgroundMusic = al_load_sample("resources/sounds/backgroundMusic.wav");

	if (!backgroundMusic) {
		printf("Failed to create background music!\n");
	}

	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			bitmapArray[i][j] = NULL;
			unitsArray[i][j] = NULL;
		}
	}

	attackWarningShown = false;
	purchaseWarningShown = false;

	warningsOnOff = true;
	soundEffectsOnOff = true;
	backgroundMusicOnOff = true;

	
}

MapGraphics::~MapGraphics()
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			al_destroy_bitmap(bitmapArray[i][j]);
			if (unitsArray[i][j] != NULL) { al_destroy_bitmap(unitsArray[i][j]); }
		}
	}
	al_destroy_bitmap(attackButton);
	al_destroy_bitmap(passButton);
	al_destroy_bitmap(purchaseButton);
	al_destroy_font(menuFont);
	al_destroy_display(display);

}

void MapGraphics::showMap(Resources* data, Map* myMap, int player_money, TeamNumber my_team, unsigned int time)
{
	al_clear_to_color(al_map_rgb(0.0, 170.0, 0.0));

	//Imprimo en pantalla el dinero y tiempo
	if((time == 10) || (time == 30) || (time == 0)){
		al_draw_textf(menuFont, al_color_name("red"), M_WIDTH(display) + 20, 0.0, 0.0, (("Time Left: ") + to_string(time)).c_str());
		playThirtySecSound();
	
	}
	else
		al_draw_textf(menuFont, al_color_name("white"), M_WIDTH(display) + 20, 0.0, 0.0, (("Time Left: ") + to_string(time)).c_str());
		
	
	al_draw_textf(menuFont, al_map_rgb(255, 255, 255), al_get_display_width(display) - al_get_text_width(menuFont, ("$ " + to_string(player_money)).c_str()), 0.0, 0.0, ("$" + to_string(player_money)).c_str());
	
	//Imprimo el boton ATTACK en la pantalla
	al_draw_scaled_bitmap(attackButton, 0.0, 0.0,
		al_get_bitmap_width(attackButton), al_get_bitmap_height(attackButton),
		M_WIDTH(display), al_get_font_line_height(menuFont), R_WIDTH, M_HEIGHT(display) / 9.0, 0);
	
	//Imprimo el boton PASS en la pantalla
	al_draw_scaled_bitmap(passButton, 0.0, 0.0,
		al_get_bitmap_width(passButton), al_get_bitmap_height(passButton),
		M_WIDTH(display), al_get_font_line_height(menuFont) + (M_HEIGHT(display) / 9.0), R_WIDTH, M_HEIGHT(display) / 9.0, 0);

	//Imprimo el boton PURCHASE en la pantalla
	al_draw_scaled_bitmap(purchaseButton, 0.0, 0.0,
		al_get_bitmap_width(purchaseButton), al_get_bitmap_height(purchaseButton),
		M_WIDTH(display), al_get_font_line_height(menuFont) + (M_HEIGHT(display) / 9.0)*2, R_WIDTH, M_HEIGHT(display) / 9.0, 0);

	//Imprimo en la pantalla la lista de unidades para comprar
	list<Unit>::iterator iterator1 = data->getUnitList().begin();
	for (int i = 0; i < 9; i++) {
		string currItem;
		currItem = iterator1->getName() + ": $";
		currItem += iterator1->getCost();
		al_draw_text(menuFont, al_map_rgb(255, 255, 255), M_WIDTH(display) + 20,
			(al_get_font_line_height(menuFont) + (M_HEIGHT(display) / 9.0) * 3) + (al_get_font_ascent(menuFont) * i), 0.0,
			currItem.c_str());
		if (i < 8)
		{
			advance(iterator1, 1);
		}
	}

	

	//Imprimo en la pantalla todos los terrenos y buildings
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {

			al_draw_scaled_bitmap(bitmapArray[i][j], 0.0, 0.0,
				al_get_bitmap_width(bitmapArray[i][j]), al_get_bitmap_height(bitmapArray[i][j]),
				j*T_WIDTH(display), i* T_HEIGHT(display), T_WIDTH(display), T_HEIGHT(display), 0);
			if ((myMap->getTile(i, j)->getBuilding() != NULL) &&
				(myMap->getTile(i, j)->isSelected()) && (!myMap->getTile(i, j)->getFog()))
			{
				al_draw_filled_rectangle((j*T_WIDTH(display)) + ((T_WIDTH(display)) / 1.5) - al_get_text_width(hpFont, to_string(myMap->getTile(i, j)->getBuilding()->getCp()).c_str())/2,
					(i* T_HEIGHT(display)) + (T_HEIGHT(display)) / 2,
					(j*T_WIDTH(display)) + ((T_WIDTH(display)) / 1.5) + al_get_text_width(hpFont, to_string(myMap->getTile(i, j)->getBuilding()->getCp()).c_str())*(1.5),
					(i* T_HEIGHT(display)) + (T_HEIGHT(display)) / 2 + al_get_font_line_height(hpFont), al_color_name("white"));
				al_draw_text(hpFont, al_color_name("black"),
					(j*T_WIDTH(display)) + (T_WIDTH(display))/1.5, (i* T_HEIGHT(display)) + (T_HEIGHT(display))/2, 0.0,
					to_string(myMap->getTile(i, j)->getBuilding()->getCp()).c_str());

			}

		}
	}
	//Imprimo en la pantalla todas las unidades, hp, cp y possible moves
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			
			if (unitsArray[i][j] != NULL) {
				al_draw_scaled_bitmap(unitsArray[i][j], 0.0, 0.0,
					al_get_bitmap_width(unitsArray[i][j]), al_get_bitmap_height(unitsArray[i][j]),
					j*T_WIDTH(display), i* T_HEIGHT(display), T_WIDTH(display) / 1.3, T_HEIGHT(display) / 1.3, 0);
				
				if (myMap->getTile(i, j)->isSelected())
				{
					
					if ((myMap->getTile(i, j)->getUnit()->getTeam() == my_team))
					{
						myMap->possibleMoves(myMap->getTile(i, j)->getUnit(), i, j);
						myMap->possibleAttack(myMap->getTile(i, j)->getUnit(), i, j, my_team);
						for (int p = 0; p < (FILA); p++)
						{
							for (int q = 0; q < (COLUMNA); q++)
							{
								if (myMap->canMove[p][q])
								{
									al_draw_rectangle(q*T_WIDTH(display), p* T_HEIGHT(display),
										(q*T_WIDTH(display)) + T_WIDTH(display),
										(p* T_HEIGHT(display)) + T_HEIGHT(display),
										al_color_name("green"), 3.0);
								}
								if (myMap->canAttack[p][q])
								{
									
									al_draw_filled_circle((q*T_WIDTH(display)) + T_WIDTH(display)/2, (p* T_HEIGHT(display)) + T_HEIGHT(display)/2, T_HEIGHT(display) / 3,al_color_name("red"));
									//al_draw_rectangle(q*T_WIDTH(display), p* T_HEIGHT(display),
									//	(q*T_WIDTH(display)) + T_WIDTH(display),
									//	(p* T_HEIGHT(display)) + T_HEIGHT(display),
									//	al_color_name("red"), 3.0);
								}
							}
						}
					}
					
					if (!myMap->getTile(i, j)->getFog())
					{
						al_draw_filled_rectangle((j*T_WIDTH(display)) - al_get_text_width(hpFont, (to_string(myMap->getTile(i, j)->getUnit()->getHp())).c_str()) / 2,
							(i* T_HEIGHT(display)),
							(j*T_WIDTH(display)) + al_get_text_width(hpFont, (to_string(myMap->getTile(i, j)->getUnit()->getHp())).c_str())*1.5,
							(i* T_HEIGHT(display)) + al_get_font_line_height(hpFont), al_color_name("white"));

						al_draw_text(hpFont, al_color_name("black"),
							(j*T_WIDTH(display)), i* T_HEIGHT(display), ALLEGRO_ALIGN_LEFT,
							(to_string(myMap->getTile(i, j)->getUnit()->getHp())).c_str());
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

void MapGraphics::setDisplayName(string _name)
{
	al_set_window_title(display, _name.c_str());
}

void MapGraphics::showDice(int _dice)
{
	if (diceFace != NULL) { al_destroy_bitmap(diceFace); }

	string _path = DICE_FACE_PATH;
	_path += to_string(_dice);
	_path += ".png";
	diceFace = al_load_bitmap(_path.c_str());
	if (!diceFace)
	{
		cout << "ERROR loading dice Image" << endl;
	}
	else
	{
		int dx = ((al_get_display_width(display) / 2) - (al_get_bitmap_width(diceFace) / 8 / 2));
		int dy = ((al_get_display_height(display) / 2) - (al_get_bitmap_height(diceFace) / 8 / 2));


		al_draw_scaled_bitmap(diceFace, 0.0, 0.0, al_get_bitmap_width(diceFace), al_get_bitmap_height(diceFace), dx, dy, (al_get_display_width(display) / 8), (al_get_display_height(display) / 8), 0.0);


		al_flip_display();
	}

}

void MapGraphics::playTenSecSound()
{
	if(soundEffectsOnOff)
		al_play_sample(beep, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void MapGraphics::playThirtySecSound()
{
	if (soundEffectsOnOff)
		al_play_sample(beep, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void MapGraphics::playOneMinSound()
{
	if (soundEffectsOnOff)
		al_play_sample(beep, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void MapGraphics::playGameOverSound()
{
	if (soundEffectsOnOff)
		al_play_sample(gameover, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

ALLEGRO_DISPLAY* MapGraphics::getDisplay()
{
	return display;
}

bool MapGraphics::doIwantToPlayAgain()
{
	int button = al_show_native_message_box(
		NULL,
		"GAME OVER",
		"Do you want to play again?",
		NULL, NULL, ALLEGRO_MESSAGEBOX_YES_NO);

	if (button == 1)
	{
		
		return true;
	}
	else
		return false;
}

void MapGraphics::setAttackWarningShown(bool a)
{
	attackWarningShown = a;
}

bool MapGraphics::wasPurchaseWarningShown()
{
	return purchaseWarningShown;
}

bool MapGraphics::wasAttackWarningShown()
{
	return attackWarningShown;
}

void MapGraphics::setPurchaseWarningShown(bool a)
{
	purchaseWarningShown = a;
}

ALLEGRO_FONT * MapGraphics::getMenuFont()
{
	return menuFont;
}

void MapGraphics::setBackgroundMusicOnOff(bool a)
{
	backgroundMusicOnOff = a;
}

bool MapGraphics::getBackgroundMusicOnOff()
{
	return backgroundMusicOnOff;
}

void MapGraphics::setSoundEffectsOnOff(bool a)
{
	soundEffectsOnOff = a;
}

void MapGraphics::setWarningsOnOff(bool a)
{
	warningsOnOff = a;
}

bool MapGraphics::getWarningsOnOff()
{
	return warningsOnOff;
}

ALLEGRO_SAMPLE * MapGraphics::getBackgroundSample()
{
	return backgroundMusic;
}
