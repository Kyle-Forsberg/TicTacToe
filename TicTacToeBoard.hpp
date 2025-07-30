#ifndef TICTACTOEBOARD_HPP
#define TICTACTOEBOARD_HPP

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include <vector>

class TicTacToeBoard : public SDLGameObject {

	public:
	TicTacToeBoard(const LoaderParams * params);
	virtual void draw();
	virtual void update();
	virtual void clean();

	std::vector<SDLGameObject*> tictacs;
	//this thing will have its own vector of objects
	//because it should manage them directly since they should atleast appear
	//to be a part of the board.
	
	bool addCircle();
	bool addX();
	bool makeMove();

	void badPlacement();
	int translateX(int x);
	int translateY(int y);	//these will take their spot in gamestate and make them into screen coords
	void mouseToBox(int,int);
	void resetBoard();


	int getHighlightedX();
	int getHighlightedY();
	void alignHighlight();

	int mouseX, mouseY;
	int highlighted;
	//this is going to be 0-9, 0 being none and then the rest 1-9.
	//for highlighting the squares so you know where youre gonna place it.
	int gamestate[3][3];	
		
	void checkWin();
	int winstate;
	int playerup = 1;
	bool reset_wait_over;
	unsigned long game_end_time;

	SDLGameObject * Highlighter;

};


#endif
