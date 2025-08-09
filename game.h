#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "TicTacToeBoard.hpp"
#include "StartScreen.hpp"

class Game {
  public:

    
    //just setting runnign to true for now
    bool init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen);

    void render();
    void update();
    void handleEvents();
    void clean();
   
	void addX(int,int);
	void addCircle(int,int);

    SDL_Renderer* getRenderer() const { return m_pRenderer;}

    //function to access the private running variable
    bool running() {return m_bRunning;}

    static Game* Instance(){
      if(s_pInstance == 0){
        s_pInstance = new Game();
        return s_pInstance;
      }
      return s_pInstance;
    }

  static Game* s_pInstance;

  private:
  Game(){}
  //typedef Game TheGame;


    SDL_Window * m_pWindow;
    SDL_Renderer * m_pRenderer;
    StartScreen * Start;
    bool m_bRunning;
    int m_currentFrame;

	TicTacToeBoard * ttt;

    TextureManager * m_TextureManager = TextureManager::Instance();


    std::vector<GameObject*> m_gameObjects;	//now we are talking
	

};


typedef Game TheGame;

#endif /*Defined the game __Game__ */
