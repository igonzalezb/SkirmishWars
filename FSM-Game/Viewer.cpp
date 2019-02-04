#include "Viewer.h"


Viewer::Viewer()
{
}

Viewer::~Viewer()
{
}

void Viewer::dispatch(genericEvent *ev, usefulInfo *Info)
{
	switch (ev->getEventType())
		{
		case I_START:
			on_IStart(ev, Info);
			break;
		case YOU_START:
			on_YouStart(ev, Info);
			break;
		case MOVE:
			on_Move(ev, Info);
			break;
		case PURCHASE:
			on_Purchase(ev, Info);
			break;
		case ATTACK:
			on_Attack(ev, Info);
			break;
		case PASS:
			on_Pass(ev, Info);
			break;
		case TILE:
			on_Tile(ev, Info);
			break;
		case R_YOU_START:
			on_RyouStart(ev, Info);
			break;
		case R_I_START:
			on_RIStart(ev, Info);
			break;
		case R_PASS:
			on_RPass(ev, Info);
			break;
		case R_MOVE:
			on_RMove(ev, Info);
			break;
		case R_PURCHASE:
			on_RPurchase(ev, Info);
			break;
		case R_ATTACK:
			on_RAttack(ev, Info);
			break;
		case R_YOU_WON:
			on_RYouWon(ev, Info);
			break;
		case R_PLAY_AGAIN:
			on_RplayAgain(ev, Info);
			break;
		case R_GAME_OVER:
			on_RgameOver(ev, Info);
			break;
		case R_ERROR_:
			on_Rerror_(ev, Info);
			break;
		case R_QUIT:
			on_Rquit(ev, Info);
			break;
		case ONE_MIN_TIMEOUT:
			on_OneMinTimeout(ev, Info);
			break;
		case TWO_HALF_MIN_TIMEOUT:
			on_TwoHalfMinTimeout(ev, Info);
			break;
		case TEN_SEC_LEFT:
			on_TenSecLeft(ev, Info);
			break;
		case THIRTY_SEC_LEFT:
			on_ThirtySecLeft(ev, Info);
			break;
		case ONE_SEC_TIMEOUT:
			on_OneSecTimeout(ev, Info);
			break;
		case YOU_WON:
			on_YouWon(ev, Info);
			break;
		case PLAY_AGAIN:
			on_PlayAgain(ev, Info);
			break;
		case GAME_OVER:
			on_GameOver(ev, Info);
			break;
		case QUIT:
			on_Quit(ev, Info);
			break;
		case ERR_DETECTED:
			on_Error_(ev, Info);
			break;
		default:
			break;
		}

		
	
}

void Viewer::on_IStart(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - YOUR TURN");
	Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));
	Info->gameInterface->graphics->setAttackWarningShown(false);
	Info->gameInterface->graphics->setPurchaseWarningShown(false);
	if(Info->gameInterface->graphics->getBackgroundMusicOnOff())
		al_play_sample(Info->gameInterface->graphics->getBackgroundSample(), 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void Viewer::on_YouStart(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - OPPONENT TURN");
	Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));
	Info->gameInterface->graphics->setAttackWarningShown(false);
	Info->gameInterface->graphics->setPurchaseWarningShown(false);
	if (Info->gameInterface->graphics->getBackgroundMusicOnOff())
		al_play_sample(Info->gameInterface->graphics->getBackgroundSample(), 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void Viewer::on_RyouStart(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - YOUR TURN");
	Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));
	Info->gameInterface->graphics->setAttackWarningShown(false);
	Info->gameInterface->graphics->setPurchaseWarningShown(false);
	if (Info->gameInterface->graphics->getBackgroundMusicOnOff())
		al_play_sample(Info->gameInterface->graphics->getBackgroundSample(), 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void Viewer::on_RIStart(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - OPPONENT TURN");
	Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));
	Info->gameInterface->graphics->setAttackWarningShown(false);
	Info->gameInterface->graphics->setPurchaseWarningShown(false);
	if (Info->gameInterface->graphics->getBackgroundMusicOnOff())
		al_play_sample(Info->gameInterface->graphics->getBackgroundSample(), 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void Viewer::on_Tile(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));

}

void Viewer::on_Pass(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->setAttackWarningShown(false);
	Info->gameInterface->graphics->setPurchaseWarningShown(false);
	if (Info->gameInterface->getIamPlaying())
		Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - YOUR TURN");
	else
		Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - OPPONENT TURN");
}

void Viewer::on_RPass(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->setAttackWarningShown(false);
	Info->gameInterface->graphics->setPurchaseWarningShown(false);
	if (Info->gameInterface->getIamPlaying())
		Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - YOUR TURN");
	else
		Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - OPPONENT TURN");
}

void Viewer::on_Move(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));
}

void Viewer::on_RMove(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));
}

void Viewer::on_Purchase(genericEvent * ev, usefulInfo * Info)
{
	//Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));

}

void Viewer::on_RPurchase(genericEvent * ev, usefulInfo * Info)
{
	//Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));

}

void Viewer::on_Attack(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));
}

void Viewer::on_RAttack(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));
}

void Viewer::on_YouWon(genericEvent * ev, usefulInfo * Info)
{

}

void Viewer::on_RYouWon(genericEvent * ev, usefulInfo * Info)
{
}

void Viewer::on_PlayAgain(genericEvent * ev, usefulInfo * Info)
{
}

void Viewer::on_RplayAgain(genericEvent * ev, usefulInfo * Info)
{
}

void Viewer::on_GameOver(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->playGameOverSound();
}

void Viewer::on_RgameOver(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->playGameOverSound();
}

void Viewer::on_Error_(genericEvent * ev, usefulInfo * Info)
{
	al_clear_to_color(al_color_name("black"));
	//al_show_native_message_box(Info->gameInterface->graphics->getDisplay(),
	//	"ERROR", "CONNECTION LOST", "The connection with the other player was lost.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

void Viewer::on_Rerror_(genericEvent * ev, usefulInfo * Info)
{
	al_clear_to_color(al_color_name("black"));
	//al_show_native_message_box(Info->gameInterface->graphics->getDisplay(),
	//	"ERROR", "CONNECTION LOST", "The connection with the other player was lost.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

void Viewer::on_Quit(genericEvent * ev, usefulInfo * Info)
{
}

void Viewer::on_Rquit(genericEvent * ev, usefulInfo * Info)
{
}

void Viewer::on_OneMinTimeout(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->playOneMinSound();
	
	if (Info->gameInterface->getIamPlaying())
		Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - YOUR TURN");
	else
		Info->gameInterface->graphics->setDisplayName("SKIRMISH WARS - OPPONENT TURN");
}

void Viewer::on_TwoHalfMinTimeout(genericEvent * ev, usefulInfo * Info)
{
	al_clear_to_color(al_color_name("black"));
	//al_show_native_message_box(Info->gameInterface->graphics->getDisplay(),
//		"ERROR", "CONNECTION LOST", "The connection with the other player was lost.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

void Viewer::on_TenSecLeft(genericEvent * ev, usefulInfo * Info)
{	
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));

	//Info->gameInterface->graphics->playTenSecSound();
}

void Viewer::on_ThirtySecLeft(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));

	//Info->gameInterface->graphics->playThirtySecSound();
	
}

void Viewer::on_OneSecTimeout(genericEvent * ev, usefulInfo * Info)
{
	Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam(), (60 - (Info->timeoutSrc->getTimeoutCount1())));

}