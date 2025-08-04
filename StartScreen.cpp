#ifndef START_SCREEN_CPP
#define START_SCREEN_CPP

#include "StartScreen.hpp"


#define STARTX 0
#define STARTY 0
#define STARTLENGHT 512
#define STARTHEIGHT 512
StartScreen::StartScreen(){
	//make sure to load assets in game.cpp
	objects.push_back(new SDLGameObject(new LoaderParams(0,0,1920,1080,"titlepage")));
	objects.push_back(new SDLGameObejct(new LoaderParams(x,y,512,512,"startbtn")));
	//we are going to need two start buttons, one should be for
	//playing without a CPU and the other for with, for now
	//just use the one until the AI is up and running.
	
	status = 0;
	//0 = waiting
	//
}


int StartScreen::submit(int x, int y){
	//checks if the x and y (cursor input) is on either button
	if(x >= STARTX && x <= STARTX+STARTLENGTH){
		if(x>= STARTY && x <= STARTY+STARTHEIGHT){
			return 1;
		}
	}
	return 0;
	//0 return means no option was selected and should not leave the start page
}










#endif
