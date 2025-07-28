//#include <SDL2/SDL.h>
//#include <SDL2/SDL_Image.h>
#include "game.h"
#include "Timer.h"
//#include "TextureManager.h"

const int FPS = 144;
const int DELAY_TIME = 1000.0f /FPS;

const char * title = "THE GAME";
#define XPOS 0
#define YPOS 0
#define WIDTH 1920
#define HEIGHT 1080
#define fullscreen true

int main (void) 
{
	Uint32 framestart, frametime;
	
	bool initsuccess = TheGame::Instance()->init(title, XPOS, YPOS, WIDTH, HEIGHT, fullscreen);

	if(initsuccess) std::cout<<"Init success!"<<std::endl;
	else std::cout<<"Init failed!"<<std::endl;


	Timer<144> fps_cap_timer;

	while(TheGame::Instance()->running())
	{
		
		//looks dumb because Im checking events so much
		//but helps with input lag for now
		//until I figure out a better system
		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		//TheGame::Instance()->handleEvents();
		TheGame::Instance()->render();
		//TheGame::Instance()->handleEvents();
		//fps_cap_timer.sleep();		// this solution is far better than book proposed
	}
	TheGame::Instance()->clean();

	return 0;
}


