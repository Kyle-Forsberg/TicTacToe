#include <iostream>
#include "SDLGameObject.cpp"
#include <vector>


class StartScreen : public SDLGameObject{
	StartScreen();
	~StartScreen();




	std::vector<SDLGameObject*> objects;
	
	int submit();		//returns the state in which the game is to be played
				//should also destroy this object;
	
}

