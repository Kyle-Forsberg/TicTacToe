#ifndef GAME_CPP
#define GAME_CPP

#include "game.h"
#include <cmath>


#define WINDOWHEIGHT 1080
#define WINDOWWIDTH 1920




Game * Game::s_pInstance = 0;

//these will be moved to their own classes momentarily


bool Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen){
	int flags = SDL_WINDOW_RESIZABLE;
	if(fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		std::cout << "SDL init success\n";
		m_pWindow = SDL_CreateWindow(title,xpos,ypos,width,height,flags);

		if(m_pWindow != 0){	//if zero it did not init right
			std::cout << "Window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if(m_pRenderer!=0){
				std::cout << "Renderer Creation Success\n";
				SDL_SetRenderDrawColor(m_pRenderer,255,255,255,0);
				if(!TheTextureManager::Instance()->load("assets/grid.png","grid",m_pRenderer)){ std::cerr << "issue loading the grid\n";}
				//use our custom class	
				//m_gameObjects.push_back(new SDLGameObject(new LoaderParams((WINDOWWIDTH/2)-(640/2), (WINDOWHEIGHT/2)-(480/2), 640, 480, "grid")));
				//we are using TicTacToeBoard object instead
				if(!TheTextureManager::Instance()->load("assets/circle.png","circle",m_pRenderer)){std::cerr << "issue loading the cirlce\n";}				
				ttt = new TicTacToeBoard(new LoaderParams((WINDOWWIDTH/2)-(640/2),(WINDOWHEIGHT/2)-(480/2),640,480,"grid"));
				if(!TheTextureManager::Instance()->load("assets/x.png","x",m_pRenderer)){std::cerr << "issue loading 'x'\n";}
				if(!TheTextureManager::Instance()->load("assets/highlight.png","highlight",m_pRenderer)){std::cerr << "error loading HL\n";}

				if(!TheTextureManager::Instance()->load("assets/Player1.png","player1",m_pRenderer)){std::cerr << "error loading P1\n";}
				if(!TheTextureManager::Instance()->load("assets/Player2.png","player2",m_pRenderer)){std::cerr << "error loading P2\n";}
				if(!TheTextureManager::Instance()->load("assets/catsgame.png","catsgame",m_pRenderer)){std::cerr << "error loading Catgame\n";}
				m_gameObjects.push_back(ttt);

				//we are keeping a reference to this board here, so we make it and give it a name
				//and then add it to the ole game objects vector
			}
			else{
				std::cout << "Renderer init failure\n";
				return false;
			}
		}
		else{
			std::cout << "Window Init Failure\n";
			return false;
		}
	}
	else{
		std::cout << "SDL init failure\n";
		return false;
	}
	std::cout << "total init success\n";
	m_bRunning = true;	//everything success, Lets start that main loop!
	
	//init new classes and add them to the vector of game objects
	

	return true;
}


void Game::render(){
	SDL_RenderClear(m_pRenderer);	//clear the renderer first
	
	for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size();i++){
		TheGame::Instance()->m_gameObjects[i]->draw();//removed renderer from draw() call
		//std::cout << "rendered an obj\n";
	}
	//this function is much simpler now, splendid.
	SDL_RenderPresent(m_pRenderer);	//draw to the screen
}

void Game::clean(){
	std::cout << "Cleaning the game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents(){
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT: m_bRunning = false;
				 break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				  	case SDLK_c:	ttt->addX();break;
					case SDLK_x:	ttt->addCircle();break;
					case SDLK_ESCAPE: m_bRunning = false;break;	
					defualt:break;
				}break;

			case SDL_MOUSEBUTTONDOWN: 
				std::cout << "Mouse button pressed\n";
				if(event.button.button == SDL_BUTTON_LEFT){ ttt->makeMove();}
				break;
			default: break;
		}
		
	}
}

void Game::update(){
		
	for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size();i++){
		m_gameObjects[i]->update();
	}
	//update all game objects in the list 
}







#endif
