#ifndef START_SCREEN_CPP
#define START_SCREEN_CPP

#include "StartScreen.hpp"
#include "TextureManager.h"		//so we can just load this classes assets here

#define STARTX 448
#define STARTY 100		//these buttons being 512x512 isnt going to fly for long 
#define STARTLENGTH 512
#define STARTHEIGHT 512

#define WAITING 0
#define SINGLEPLAYER 1
#define MULTIPLAYER 2


StartScreen::StartScreen(const LoaderParams * params) : SDLGameObject (params) {	//yep, we need to pass the renderer to the constructor :(
	
	//objects->push_back(new SDLGameObject(new LoaderParams(0,0,1920,1080,"titlepage")));
				//this should be passed to this when creating it, i think that makes most sense not here
		//this is still fine to init here I think.
	
	objects.push_back(new SDLGameObject(new LoaderParams(STARTX,STARTY,STARTLENGTH,STARTHEIGHT,"startbtn")));
	
	//we are going to need two start buttons, one should be for
	//playing without a CPU and the other for with, for now
	//just use the one until the AI is up and running.
	
	status = WAITING;
	//0 = waiting
	//
}

bool StartScreen::init(SDL_Renderer* renderer){
	//will need to be called before we can show the start screen
	//this is to avoid having substantially different constructors from other SDLGameObjects
	if(!(TheTextureManager::Instance()->load("assets/StartButtonTemp.png","startbtn",renderer))){
		std::cerr << "Error loading StartButtonTemp.png\n";
		return false;
		//give up if we fail even one
	}
	if(!(TheTextureManager::Instance()->load("assets/TitlePage.png","titlepage",renderer))){
		std::cerr << "Error laoding TitlePage.png\n";
		return false;
	}
	return 0;
}


int StartScreen::submit(int x, int y){
	//checks if the x and y (cursor input) is on either button
	if(x >= STARTX && x <= STARTX+STARTLENGTH){
		if(x>= STARTY && x <= STARTY+STARTHEIGHT){
			return MULTIPLAYER;
			std::cout << "Oh boy oh wow we made a good sumbission!!!\n";
		}
	}
	std::cout << "Misclick??\n";
	return 0;
	//0 return means no option was selected and should not leave the start page
}



void StartScreen::update(){
	//I think it makes sense that this would have its own input handler if this is to act
	//as its own little entity, since passing inputs or having if statements in game.cpp
	//for the start screens input would be slower and less readable
	int mouseX, mouseY;
	//reuse of these variable names here? is this allowed?
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_LEFT){
				SDL_GetMouseState(&mouseX,&mouseY);
				submit(mouseX,mouseY);
				//basically if we have mouseclick, submit that to 'submit'
				//and see if we get to do something.
			}
		}
	}	
}

void StartScreen::draw(){
	SDLGameObject::draw();		//inherit entirely
	for(int i = 0; i < objects.size();i++){
		objects[i]->draw();
		//also need to draw all children!!!
	}
}

void StartScreen::clean(){
	//just nothin for now
}






#endif
