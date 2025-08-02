#ifndef COMPUTER_OPPONENT_HPP
#define COMPUTER_OPPONENT_HPP



class ComputerOpponent {
	ComputerOpponent(int diff), difficulty(diff){
		//potentially other stuff should be done here

	}
	
	int makeMove(int[3][3] gamestate);		//will implement algorithm to decide next move
	




	int playerNumber;		//either 1 or 2, depending on whether it is X or O
	int difficulty;

};
