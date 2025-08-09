#ifndef STARTSCREEN_HPP
#define STARTSCREEN_HPP

#include <iostream>
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include <vector>
#include <SDL2/SDL.h>


class StartScreen : public SDLGameObject {
	public:
	StartScreen(const LoaderParams* params);
	//~StartScreen();

	virtual void draw();
	virtual void update();
	virtual void clean();


	bool init(SDL_Renderer*);
	

	bool gamestarted;
	int status;
	std::vector<SDLGameObject*> objects;
	
	int submit(int,int);		//returns the state in which the game is to be played
				//should also destroy this object;
};



#endif
