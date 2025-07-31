#ifndef TICTACTOE_CPP
#define TICTACTOE_CPP

#include "TicTacToeBoard.hpp"


#define NOWIN 0
#define PLAYER1WIN 1
#define PLAYER2WIN 2
#define CATSGAME 3
#define RESETAWAIT 4
#define RESETTING 5


TicTacToeBoard::TicTacToeBoard(const LoaderParams *params) : SDLGameObject (params) {
	
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 3;j++){
			gamestate[i][j]=0;					//zero out the gamestate
												//we we will use 1 for x 2 for circle
		}
	}
	winstate = 0;
	
	Highlighter = new SDLGameObject(new LoaderParams(1921, 1081, 210,160, "highlight"));
	tictacs.push_back(Highlighter);
	//init highlight, leave it off window for now
}

void TicTacToeBoard::alignHighlight(){
	if(highlighted == 0){
		Highlighter->m_position.setX(1921);
		Highlighter->m_position.setY(1081);
		// move it off the screen
	}
	else{
		int x = getHighlightedX();
		int y = getHighlightedY();
		Highlighter->m_position.setX(translateX(x)-20);
		Highlighter->m_position.setY(translateY(y)-6);
	}
}


int TicTacToeBoard::translateY(int y){
	return (m_position.getY() + (y * 160) + 5);
		//starts by getting top left of window
		//then adds y * 160 (for each slot is 160 px wide)
}

int TicTacToeBoard::translateX(int x){
	return (m_position.getX() + (x * 214) + 20);	
	//real hackjob here but I think this will look fine
}

void TicTacToeBoard::draw(){
	SDLGameObject::draw();
	//main grid is drawn, now we need to draw pieces though....
	for(int i = 0; i < tictacs.size();i++){
		tictacs[i]->draw();
	}
}

void TicTacToeBoard::update(){
	if(winstate == RESETTING){
		std::cout << "winstate is RESETTING\n";
		resetBoard();		//essentially hand update over to this function.
		return;
	}
	if(winstate == RESETAWAIT){
		std::cout << "awaiting reset of the game\n";
		game_end_time = ((unsigned long)(SDL_GetTicks()));
		std::cout << "game end time update(): " << game_end_time << "\n";
		winstate = RESETTING;
		resetBoard();
		return;
		//since resetBoard also resets winstate, this works
	}
	if(winstate!=0){						
		if(winstate == CATSGAME){
			std::cout << "Catsgame";
			game_end_time = ((unsigned long)(SDL_GetTicks()));
			tictacs.push_back(new SDLGameObject(new LoaderParams(0,0,1920,1080,"catsgame")));
			winstate = RESETAWAIT;		
			return;
		}
		else{
			if(winstate == PLAYER1WIN){
				std::cout << "player 1 win\n";
				game_end_time = ((unsigned long)(SDL_GetTicks()));
				tictacs.push_back(new SDLGameObject(new LoaderParams(0,0,1920,1080,"player1")));
				winstate = RESETAWAIT;
				return;
			}
			if(winstate == PLAYER2WIN){
				std::cout << "player 2 win\n";
				game_end_time = ((unsigned long)(SDL_GetTicks()));
				tictacs.push_back(new SDLGameObject(new LoaderParams(0,0,1920,1080,"player2")));
				winstate = RESETAWAIT;
				return;
			}

			//std::cout << "Player " << winstate << " Won the game!";
		}
		std::cout << "0";
	}
	alignHighlight();	
	SDL_GetMouseState(&mouseX,&mouseY);	//get coords of mouse for highlighting square
	mouseToBox(mouseX,mouseY);

}

void TicTacToeBoard::clean(){
	//implement eventually maybe probably not
}

void TicTacToeBoard::mouseToBox(int x, int y){
	if(x > 640 && x < 1280){
			if( y > 300 && y < 780){
				
				y-=300;x-=640;
				//zero out x and y
				int tempx = 0;
				int tempy = 0;
				int foundx = 0;
				int foundy = 0;
				while(y > tempy){
					foundy++;
					tempy+=160;
				}
				while(x > tempx){
					foundx++;
					tempx+=214;
				}
				highlighted = ((foundy * 3) + foundx) -3;
				//converts the x and y to a box number since I dont want to 
				//pass around 2 numbers, probably just lazy
				return;
			}
	}
	highlighted = 0;
}

int TicTacToeBoard::getHighlightedY(){
	switch(highlighted){
		case 0: return 0;
		case 1:
		case 2:
		case 3: return 0;
		case 4:
		case 5:
		case 6: return 1;
		case 7:
		case 8:
		case 9: return 2;
		default: return 0;
		}
}

int TicTacToeBoard::getHighlightedX(){
	switch(highlighted){
		case 0:return 0;break;
		case 1:return 0;
		case 2:return 1;
		case 3:return 2;
		case 4:return 0;
		case 5:return 1;
		case 6:return 2;
		case 7:return 0;
		case 8:return 1;
		case 9:return 2;
		default: return 0;
	}
}
bool TicTacToeBoard::makeMove(){
	bool res;
	if(highlighted == 0){return false;} 	//also skips playerup++ effectively nulling this whole function :)
	if(playerup>2) { playerup = 1; }
		
	if(playerup==1){
		res = addX();
	}
	if(playerup==2){
		res = addCircle();
	}
	playerup++;
	checkWin();
	return res;
}

bool TicTacToeBoard::addCircle(){
	int x = getHighlightedX();
	int y = getHighlightedY();
	if(gamestate[x][y]==0){
		gamestate[x][y]=2;
		
		tictacs.push_back(new SDLGameObject(new LoaderParams(translateX(x), translateY(y), 150,150, "circle")));
		//add new game object
		std::cout << "added a circle\n";
		return true;
	}
	return false;
}

bool TicTacToeBoard::addX(){
	int x = getHighlightedX();
	int y = getHighlightedY();
	if(gamestate[x][y]==0){
		gamestate[x][y]=1;
		tictacs.push_back(new SDLGameObject(new LoaderParams(translateX(x),translateY(y),150,150,"x")));
		std::cout << "added an X\n";

		return true;
	}
	return false;
}


void badPlacement(){
	std::cout << "cant do that\n";
}	//obv needs implementation


void TicTacToeBoard::checkWin() {
	std::cout << "checking for a win\n";
	bool changed = false;
	if(winstate != 0){winstate = 4;}//so we dont overwrite that asap and ruin things
    for (int row = 0; row < 3; ++row) {
        if (gamestate[row][0] != 0 &&
            gamestate[row][0] == gamestate[row][1] &&
            gamestate[row][1] == gamestate[row][2]) {
            winstate = gamestate[row][0]; 
			changed = true;
        }
    }

    for (int col = 0; col < 3; ++col) {
        if (gamestate[0][col] != 0 &&
            gamestate[0][col] == gamestate[1][col] &&
            gamestate[1][col] == gamestate[2][col]) {
            winstate = gamestate[0][col];  
			changed = true;
        }
    }

    if (gamestate[0][0] != 0 &&
        gamestate[0][0] == gamestate[1][1] &&
        gamestate[1][1] == gamestate[2][2]) {
        winstate = gamestate[0][0];  
		changed = true;
    }

    if (gamestate[0][2] != 0 &&
        gamestate[0][2] == gamestate[1][1] &&
        gamestate[1][1] == gamestate[2][0]) {
        winstate = gamestate[0][2];  
		changed = true;
    }

    
	//check locked up board
	bool allFilled = true;
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 3;j++){
			if(gamestate[i][j]==0){
				allFilled = false;
			}
		}
	}
	if(allFilled == true && winstate == 0){						//added == 0 to make sure a win on the 9th move doesnt register as catsgame
		std::cout << "looks like a cats game to me pal \n";
		winstate = CATSGAME;
		changed = true;
		
		//code for reset board
	}
	
	

}

void TicTacToeBoard::resetBoard(){
	unsigned long current_gametime = ((unsigned long)(SDL_GetTicks()));
	std::cout << "resetboard() " << current_gametime << "\n";
	if(  (current_gametime-5000) > (game_end_time) ){
		std::cout<< "reset check still waiting\n";
		winstate = RESETTING;
		//wait for 10000 ticks before allowing reset
	}
	else if (winstate != RESETAWAIT) {		//make sure we dont get here if were stalling in between games
		std::cout << "we have made it into reset board\n";
		tictacs.clear();
		tictacs.push_back(Highlighter);
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				gamestate[i][j]=0;
			}
		}
		//objects have been cleared (memleak???)
		//game state cleared back to all zeros

		winstate = 0;
		//winstate reset
	}
}




#endif
