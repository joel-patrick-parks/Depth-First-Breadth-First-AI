#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <time.h>
using namespace std;

// The game board
vector<vector<int>> gameBoard;
vector<vector<int>> randomWalkBoard;
vector<vector<int>> clonedBoard;
vector<vector<vector<int>>> gameBoardStates;
vector<vector<vector<int>>> nonNormalBoardStates;
vector<string> movesToSolution;
vector<vector<vector<int>>> statesToSolution;
vector<vector<vector<vector<int>>>> parentToChild;
vector<vector<string>> parentToChildMoves;
vector<vector<vector<int>>> BSTStatesToSolution;
vector<string> BSTMovesToSolution;
int nodes = 0;
int length = 0;
//float time;

class PieceMove{
public:
	// Class constructor
	PieceMove(vector<vector<int>> pieceBoard);

	// Returns the board
	vector<vector<int>> getPieceBoard();

	// Sets the board
	void setPieceBoard(vector<vector<int>> board);

	// Generates moves a piece can make
	vector<string> movePieceGeneration(int piece);

	// Generates all moves that the pieces can make
	vector<string> moveAllGeneration();

	// Applies a random available move to the board
	string applyMove(vector<string> availableMoves);

	// Clones the move made and returns a new state
	vector<vector<int>> applyMoveCloning(int piece, char direction);
private:
	vector<vector<int>> pieceMoveBoard;
};

PieceMove::PieceMove(vector<vector<int>> pieceBoard){
	pieceMoveBoard = pieceBoard;
}

vector<vector<int>> PieceMove::getPieceBoard(){
	return pieceMoveBoard;
}

void PieceMove::setPieceBoard(vector<vector<int>> board){
	pieceMoveBoard = board;
}

vector<string> PieceMove::movePieceGeneration(int piece){
	int masterBrickWidth = 1;
	int masterBrickHeight = 1;
	bool masterBrickSize = false;
	bool masterBrickCheck = false;
	string possibleMove;
	vector<string> possibleMoveSet;

	// Gets the width and height of the brick
	for(int i = 0; i < pieceMoveBoard.size(); i++){
		for(int j = 0; j < pieceMoveBoard[i].size(); j++){
			if(pieceMoveBoard[i][j] == piece){
				if(pieceMoveBoard[i+1][j] == piece || pieceMoveBoard[i-1][j] == piece){
					masterBrickHeight = 2;
					masterBrickSize = true;
				}
				if(pieceMoveBoard[i][j+1] == piece){
					masterBrickWidth = 2;
					masterBrickSize = true;
				}
			}
			if(masterBrickSize){break;}
		}
		if(masterBrickSize){break;}
	}

	// Determines if/where the brick can move
	for(int i = 0; i < pieceMoveBoard.size(); i++){
		for(int j = 0; j < pieceMoveBoard[i].size(); j++){
			if(pieceMoveBoard[i][j] == piece){
				masterBrickCheck = true;
				// Checks for moves if the brick height and width is 1
				if(masterBrickHeight = 1 && masterBrickWidth == 1){
					if(pieceMoveBoard[i][j-1] == 0){
						//cout << "(" << piece << ", left)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'l';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i][j+1] == 0){
						//cout << "(" << piece << ", right)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'r';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i-1][j] == 0){
						//cout << "(" << piece << ", up)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'u';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i+1][j] == 0){
						//cout << "(" << piece << ", down)" << endl;

						possibleMove = to_string(piece);
						possibleMove += 'd';
						possibleMoveSet.push_back(possibleMove);
					}
				}
				// Checks for moves if the brick height is 1 and width is 2
				else if(masterBrickHeight = 1 && masterBrickWidth == 2){
					if(pieceMoveBoard[i][j-1] == 0){
						//cout << "(" << piece << ", left)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'l';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i][j+2] == 0){
						//cout << "(" << piece << ", right)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'r';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i+1][j] == 0 && pieceMoveBoard[i+1][j+1] == 0){
						//cout << "(" << piece << ", up)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'd';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i-1][j] == 0 && pieceMoveBoard[i-1][j+1] == 0){
						//cout << "(" << piece << ", down)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'u';
						possibleMoveSet.push_back(possibleMove);
					}
				}
				// Checks for moves if the brick height is 2 and width is 1
				else if(masterBrickHeight = 1 && masterBrickWidth == 2){
					if(pieceMoveBoard[i][j-1] == 0 && pieceMoveBoard[i-1][j-1] == 0){
						//cout << "(" << piece << ", left)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'l';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i][j+2] == 0 && pieceMoveBoard[i-1][j+2] == 0){
						//cout << "(" << piece << ", right)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'r';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i-1][j] == 0){
						//cout << "(" << piece << ", up)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'u';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i+1][j] == 0){
						//cout << "(" << piece << ", down)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'd';
						possibleMoveSet.push_back(possibleMove);
					}
				}
				// Checks for moves if the brick height is 2 and width is 2
				else if(masterBrickHeight = 2 && masterBrickWidth == 2){
					if(pieceMoveBoard[i][j-1] == 0 && pieceMoveBoard[i-1][j-1] == 0){
						//cout << "(" << piece << ", left)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'l';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i][j+2] == 0 && pieceMoveBoard[i-1][j+2] == 0){
						//cout << "(" << piece << ", right)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'r';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i+1][j] == 0 && pieceMoveBoard[i+1][j+1] == 0){
						//cout << "(" << piece << ", up)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'u';
						possibleMoveSet.push_back(possibleMove);
					}
					if(pieceMoveBoard[i-1][j] == 0 && pieceMoveBoard[i-1][j+1] == 0){
						//cout << "(" << piece << ", down)" << endl;
						possibleMove = to_string(piece);
						possibleMove += 'd';
						possibleMoveSet.push_back(possibleMove);
					}
				}
			}
			if(masterBrickCheck){break;}
		}
		if(masterBrickCheck){break;}
	}
	return possibleMoveSet;
}

vector<string> PieceMove::moveAllGeneration(){
	int highestPiece = 2;
	vector<string> pieceMoves;
	vector<string> listOfMoves;

	// Gets the highest value piece on the board
	for(int i = 0; i < pieceMoveBoard.size(); i++){
		for(int j = 0; j < pieceMoveBoard[i].size(); j++){
			if(pieceMoveBoard[i][j] > highestPiece){
				highestPiece = pieceMoveBoard[i][j];
			}
		}
	}
	
	// Generates the moves that pieces can make
	for(int piece = 2; piece <= highestPiece; piece++){
		pieceMoves = movePieceGeneration(piece);
		for(int i = 0; i < pieceMoves.size(); i++){
			listOfMoves.push_back(pieceMoves[i]);
		}
	}
	return listOfMoves;
}

string PieceMove::applyMove(vector<string> availableMoves){
	int availableMovesSize = availableMoves.size();
	bool hasMadeMove = false;
	bool finishingMove = false;
	// Picks a random move from the list of available moves to make
	double x = rand()/static_cast<double>(RAND_MAX+1);
	int randomMove = 0 + static_cast<int>(x*(availableMovesSize-0));
	string selectedMove = availableMoves[randomMove];
	// Gets the piece and the direction to move from the selected move
	int pieceToMove = selectedMove[0] - '0';
	char directionToMove = selectedMove[1];

	for(int i = 0; i < pieceMoveBoard.size(); i++){
		for(int j = 0; j < pieceMoveBoard[i].size(); j++){
			// Checks if the master brick is 1x2 and if there is a winning move to make
			if(pieceMoveBoard[i][j] == 2 && pieceMoveBoard[i][j+1] == 2){
				//Checks if the winning move is up
				if(pieceMoveBoard[i-1][j] == -1 && pieceMoveBoard[i-1][j+1] == -1){
					pieceMoveBoard[i][j] = 0;
					pieceMoveBoard[i][j+1] = 0;
					pieceMoveBoard[i-1][j] = 2;
					pieceMoveBoard[i-1][j+1] = 2;
					finishingMove = true;
					return "2u";
				}
				// Checks if the winning move is left
				else if(pieceMoveBoard[i][j-1] == -1){
					pieceMoveBoard[i][j+1] = 0;
					pieceMoveBoard[i][j-1] = 2;
					finishingMove = true;
					return "2l";
				}
			}
		}
	}

	//cout << "Move: " << pieceToMove << directionToMove << endl;

	vector<vector<int>> newClone = applyMoveCloning(pieceToMove, directionToMove);

	if(!finishingMove){
		for(int i = 0; i < pieceMoveBoard.size(); i++){
			for(int j = 0; j < pieceMoveBoard[i].size(); j++){
				if(pieceMoveBoard[i][j] == pieceToMove){
					// Determines the direction that the piece is going to move
					if(directionToMove == 'u'){
						// Checks how big the piece is to find what board cells need to be modified
						// Checks if the piece is 2x2
						if(pieceMoveBoard[i+1][j] == pieceToMove && pieceMoveBoard[i][j+1] == pieceToMove){
							pieceMoveBoard[i+1][j] = 0;
							pieceMoveBoard[i+1][j+1] = 0;
							pieceMoveBoard[i-1][j] = pieceToMove;
							pieceMoveBoard[i-1][j+1] = pieceToMove;
							hasMadeMove = true;
						}
						// Checks if the piece is 2x1
						else if(pieceMoveBoard[i+1][j] == pieceToMove){
							pieceMoveBoard[i+1][j] = 0;
							pieceMoveBoard[i-1][j] = pieceToMove;
							hasMadeMove = true;
						}
						// Checks if the piece is 1x2
						else if(pieceMoveBoard[i][j+1] == pieceToMove){
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i][j+1] = 0;
							pieceMoveBoard[i-1][j] = pieceToMove;
							pieceMoveBoard[i-1][j+1] = pieceToMove;
							hasMadeMove = true;
						}
						// If it reaches here the piece is 1x1
						else{
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i-1][j] = pieceToMove;
							hasMadeMove = true;
						}
					}else if(directionToMove == 'd'){
						// Checks how big the piece is to find what board cells need to be modified
						// Checks if the piece is 2x2
						if(pieceMoveBoard[i+1][j] == pieceToMove && pieceMoveBoard[i][j+1] == pieceToMove){
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i][j+1] = 0;
							pieceMoveBoard[i+2][j] = pieceToMove;
							pieceMoveBoard[i+2][j+1] = pieceToMove;
							hasMadeMove = true;
						}
						// Checks if the piece is 2x1
						else if(pieceMoveBoard[i+1][j] == pieceToMove){
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i+2][j] = pieceToMove;
							hasMadeMove = true;
						}
						// Checks if the piece is 1x2
						else if(pieceMoveBoard[i][j+1] == pieceToMove){
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i][j+1] = 0;
							pieceMoveBoard[i+1][j] = pieceToMove;
							pieceMoveBoard[i+1][j+1] = pieceToMove;
							hasMadeMove = true;
						}
						// If it reaches here the piece is 1x1
						else{
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i+1][j] = pieceToMove;
							hasMadeMove = true;
						}
					}else if(directionToMove == 'l'){
						// Checks how big the piece is to find what board cells need to be modified
						// Checks if the piece is 2x2
						if(pieceMoveBoard[i+1][j] == pieceToMove && pieceMoveBoard[i][j+1] == pieceToMove){
							pieceMoveBoard[i][j+1] = 0;
							pieceMoveBoard[i+1][j+1] = 0;
							pieceMoveBoard[i][j-1] = pieceToMove;
							pieceMoveBoard[i+1][j-1] = pieceToMove;
							hasMadeMove = true;
						}
						// Checks if the piece is 2x1
						else if(pieceMoveBoard[i+1][j] == pieceToMove){
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i+1][j] = 0;
							pieceMoveBoard[i][j-1] = pieceToMove;
							pieceMoveBoard[i+1][j-1] = pieceToMove;
							hasMadeMove = true;
						}
						// Checks if the piece is 1x2
						else if(pieceMoveBoard[i][j+1] == pieceToMove){
							pieceMoveBoard[i][j+1] = 0;
							pieceMoveBoard[i][j-1] = pieceToMove;
							hasMadeMove = true;
						}
						// If it reaches here the piece is 1x1
						else{
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i][j-1] = pieceToMove;
							hasMadeMove = true;
						}
					}else if(directionToMove == 'r'){
						// Checks how big the piece is to find what board cells need to be modified
						// Checks if the piece is 2x2
						if(pieceMoveBoard[i+1][j] == pieceToMove && pieceMoveBoard[i][j+1] == pieceToMove){
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i+1][j] = 0;
							pieceMoveBoard[i][j+2] = pieceToMove;
							pieceMoveBoard[i+1][j+2] = pieceToMove;
							hasMadeMove = true;
						}
						// Checks if the piece is 2x1
						else if(pieceMoveBoard[i+1][j] == pieceToMove){
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i+1][j] = 0;
							pieceMoveBoard[i][j+1] = pieceToMove;
							pieceMoveBoard[i+1][j+1] = pieceToMove;
							hasMadeMove = true;
						}
						// Checks if the piece is 1x2
						else if(pieceMoveBoard[i][j+1] == pieceToMove){
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i][j+2] = pieceToMove;
							hasMadeMove = true;
						}
						// If it reaches here the piece is 1x1
						else{
							pieceMoveBoard[i][j] = 0;
							pieceMoveBoard[i][j+1] = pieceToMove;
							hasMadeMove = true;
						}
					}
				}
				if(hasMadeMove){break;}
			}
			if(hasMadeMove){break;}
		}
	}
	return selectedMove;
	//return pieceMoveBoard;
}

vector<vector<int>> PieceMove::applyMoveCloning(int pieceToMove, char directionToMove){
	vector<vector<int>> pieceMoveBoardClone = pieceMoveBoard;
	bool hasMadeMove = false;

	for(int i = 0; i < pieceMoveBoardClone.size(); i++){
		for(int j = 0; j < pieceMoveBoardClone[i].size(); j++){
			if(pieceMoveBoardClone[i][j] == pieceToMove){
				// Determines the direction that the piece is going to move
				if(directionToMove == 'u'){
					// Checks how big the piece is to find what board cells need to be modified
					// Checks if the piece is 2x2
					if(pieceMoveBoardClone[i+1][j] == pieceToMove && pieceMoveBoardClone[i][j+1] == pieceToMove){
						pieceMoveBoardClone[i+1][j] = 0;
						pieceMoveBoardClone[i+1][j+1] = 0;
						pieceMoveBoardClone[i-1][j] = pieceToMove;
						pieceMoveBoardClone[i-1][j+1] = pieceToMove;
						hasMadeMove = true;
					}
					// Checks if the piece is 2x1
					else if(pieceMoveBoardClone[i+1][j] == pieceToMove){
						pieceMoveBoardClone[i+1][j] = 0;
						pieceMoveBoardClone[i-1][j] = pieceToMove;
						hasMadeMove = true;
					}
					// Checks if the piece is 1x2
					else if(pieceMoveBoardClone[i][j+1] == pieceToMove){
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i][j+1] = 0;
						pieceMoveBoardClone[i-1][j] = pieceToMove;
						pieceMoveBoardClone[i-1][j+1] = pieceToMove;
						hasMadeMove = true;
					}
					// If it reaches here the piece is 1x1
					else{
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i-1][j] = pieceToMove;
						hasMadeMove = true;
					}
				}else if(directionToMove == 'd'){
					// Checks how big the piece is to find what board cells need to be modified
					// Checks if the piece is 2x2
					if(pieceMoveBoardClone[i+1][j] == pieceToMove && pieceMoveBoardClone[i][j+1] == pieceToMove){
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i][j+1] = 0;
						pieceMoveBoardClone[i+2][j] = pieceToMove;
						pieceMoveBoardClone[i+2][j+1] = pieceToMove;
						hasMadeMove = true;
					}
					// Checks if the piece is 2x1
					else if(pieceMoveBoardClone[i+1][j] == pieceToMove){
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i+2][j] = pieceToMove;
						hasMadeMove = true;
					}
					// Checks if the piece is 1x2
					else if(pieceMoveBoardClone[i][j+1] == pieceToMove){
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i][j+1] = 0;
						pieceMoveBoardClone[i+1][j] = pieceToMove;
						pieceMoveBoardClone[i+1][j+1] = pieceToMove;
						hasMadeMove = true;
					}
					// If it reaches here the piece is 1x1
					else{
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i+1][j] = pieceToMove;
						hasMadeMove = true;
					}
				}else if(directionToMove == 'l'){
					// Checks how big the piece is to find what board cells need to be modified
					// Checks if the piece is 2x2
					if(pieceMoveBoardClone[i+1][j] == pieceToMove && pieceMoveBoardClone[i][j+1] == pieceToMove){
						pieceMoveBoardClone[i][j+1] = 0;
						pieceMoveBoardClone[i+1][j+1] = 0;
						pieceMoveBoardClone[i][j-1] = pieceToMove;
						pieceMoveBoardClone[i+1][j-1] = pieceToMove;
						hasMadeMove = true;
					}
					// Checks if the piece is 2x1
					else if(pieceMoveBoardClone[i+1][j] == pieceToMove){
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i+1][j] = 0;
						pieceMoveBoardClone[i][j-1] = pieceToMove;
						pieceMoveBoardClone[i+1][j-1] = pieceToMove;
						hasMadeMove = true;
					}
					// Checks if the piece is 1x2
					else if(pieceMoveBoardClone[i][j+1] == pieceToMove){
						pieceMoveBoardClone[i][j+1] = 0;
						pieceMoveBoardClone[i][j-1] = pieceToMove;
						hasMadeMove = true;
					}
					// If it reaches here the piece is 1x1
					else{
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i][j-1] = pieceToMove;
						hasMadeMove = true;
					}
				}else if(directionToMove == 'r'){
					// Checks how big the piece is to find what board cells need to be modified
					// Checks if the piece is 2x2
					if(pieceMoveBoardClone[i+1][j] == pieceToMove && pieceMoveBoardClone[i][j+1] == pieceToMove){
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i+1][j] = 0;
						pieceMoveBoardClone[i][j+2] = pieceToMove;
						pieceMoveBoardClone[i+1][j+2] = pieceToMove;
						hasMadeMove = true;
					}
					// Checks if the piece is 2x1
					else if(pieceMoveBoardClone[i+1][j] == pieceToMove){
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i+1][j] = 0;
						pieceMoveBoardClone[i][j+1] = pieceToMove;
						pieceMoveBoardClone[i+1][j+1] = pieceToMove;
						hasMadeMove = true;
					}
					// Checks if the piece is 1x2
					else if(pieceMoveBoardClone[i][j+1] == pieceToMove){
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i][j+2] = pieceToMove;
						hasMadeMove = true;
					}
					// If it reaches here the piece is 1x1
					else{
						pieceMoveBoardClone[i][j] = 0;
						pieceMoveBoardClone[i][j+1] = pieceToMove;
						hasMadeMove = true;
					}
				}
			}
			if(hasMadeMove){break;}
		}
		if(hasMadeMove){break;}
	}
	return pieceMoveBoardClone;
}

// Opens the file containing the board, builds and returns the board (DONE)
vector<vector<int>> createBoard(vector<vector<int>> board, string fileName){
	int lineNumber = 0;
	int width = 0;
	int boardSlot = 0;
	string line;
	string parsedLine;
	string nextDigit;
	ifstream boardFile;
	boardFile.open(fileName);

	// Checks if the board is open
	if(boardFile.is_open()){
		while(!boardFile.eof()){
			getline(boardFile,line);
			// Sets the height of the board and gets the width of the board
			if(lineNumber == 0){
				board.resize(line.at(2) - '0');
				width = line.at(0) - '0';
			}else{/*NEED TO GO FROM COMMA TO COMMA TO GET THE NUMBERS BECAUSE SOME ARE TWO DIGET AND SOME ARE ONE DIGIT*/
				// Sets the width of the current row of the board
				board[lineNumber-1].resize(width);
				stringstream commaCatcher(line);
				// Builds the current row from the parsed line
				while(getline(commaCatcher, parsedLine, ',')){
					board[lineNumber-1][boardSlot] = stoi(parsedLine);
					boardSlot++;
				}
				boardSlot = 0;
			}
			lineNumber++;
		}
	}
	// Close the file and return the board
	boardFile.close();
	return board;
}

// Displays the state of the board (DONE)
void displayState(vector<vector<int>> board){
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board[i].size(); j++){
			cout << "|" << board[i][j] << "|";
		}
		cout << endl;
	}
}

// Clones the state of the board (DONE)
vector<vector<int>> cloneState(vector<vector<int>> board){
	vector<vector<int>> clonedBoard = board;

	return clonedBoard;
}

// Checks if the master brick is on top of the goal (DONE)
bool puzzleComplete(vector<vector<int>> board){
	bool isComplete = true;
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board[i].size(); j++){
			// If a -1 exists, the master brick has not reached its goal
			if(board[i][j] == -1){
				isComplete = false;
			}
			// Break out of for loop
			if(!isComplete){break;}
		}
		// Break out of for loop
		if(!isComplete){break;}
	}
	return isComplete;
}

// Checks if two states are equivalent (DONE)
bool stateCompare(vector<vector<int>> board, vector<vector<int>> boardClone){
	bool identicalStates = true;

	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board[i].size(); j++){
			if(board[i][j] != boardClone[i][j]){
				identicalStates = false;
			}
			if(!identicalStates){break;}
		}
		if(!identicalStates){break;}
	}

	return identicalStates;
}

// Swaps the bricks on the board (DONE)
vector<vector<int>> swapIdx(int idx1, int idx2, vector<vector<int>> board){ 
	//cout << idx1 << "|" << idx2 << endl;
	for(int i = 0; i < board.size(); i++){ 
		for(int j = 0; j < board[i].size(); j++) {
			if(board[i][j] == idx1){
				board[i][j] = idx2;
			}else if(board[i][j] == idx2){ 
				board[i][j] = idx1;
			}
		}
	}
	return board;
}

// Normalizes the state of the board (DONE)
vector<vector<int>> normalizeState(vector<vector<int>> board){
	int nextIdx = 3;
	for(int i = 0; i < board.size(); i++){ 
		for(int j = 0; j < board[i].size(); j++){
			if(board[i][j] == nextIdx){ 
				nextIdx++;
			}else if(board[i][j] > nextIdx){
				board = swapIdx(nextIdx, board[i][j], board);
				nextIdx++;
			}
		}
	}
	return board;
}

// Takes steps equal to the integer given or the puzzle is complete (DONE)
void randomWalks(PieceMove pieceMove, int numberOfSteps){
	int stepsTaken = 0;
	displayState(randomWalkBoard);
	randomWalkBoard = normalizeState(randomWalkBoard);
	// Moves the pieces and then normalizes the board
	while(stepsTaken < numberOfSteps){
		pieceMove.applyMove(pieceMove.moveAllGeneration());
		randomWalkBoard = pieceMove.getPieceBoard();
		randomWalkBoard = normalizeState(randomWalkBoard);
		displayState(randomWalkBoard);
		stepsTaken++;
	}
	// Checks if the puzzle was solved
	if(puzzleComplete(randomWalkBoard)){
		cout << "Puzzle Complete" << endl;
	}
}

// Breadth first puzzle search
void breadthFirstSearch(PieceMove pieceMove, int movesMade, bool firstRun){
	vector<string> possibleMoves;
	vector<string> currentMove;
	string chosenMove;
	currentMove.resize(1);
	int counter = 0;
	int numberOfMoves = 0;
	int movesToBeMade = 0;
	int currentPosition;
	bool stateExists = false;

	if(firstRun){
		pieceMove.setPieceBoard(gameBoard);
		possibleMoves = pieceMove.moveAllGeneration();
		while(counter < possibleMoves.size()){
			currentMove[0] = possibleMoves[counter];
			chosenMove = pieceMove.applyMove(currentMove);
			clonedBoard = cloneState(pieceMove.getPieceBoard());
			// Normalizes the board after making the move
			pieceMove.setPieceBoard(normalizeState(pieceMove.getPieceBoard()));
			// Checks to see if the state alreadt exists
			// If so, do not make the move
			// If not, make the move and store the new state
			for(int i = 0; i < gameBoardStates.size(); i++){
				if(stateCompare(gameBoardStates[i], pieceMove.getPieceBoard())){
					stateExists = true;
				}
				if(stateExists){break;}
			}
			if(stateExists){
				pieceMove.setPieceBoard(gameBoard);
			}else{
				nodes++;
				numberOfMoves++;
				nonNormalBoardStates.push_back(cloneState(clonedBoard));
				parentToChild[0].push_back(cloneState(clonedBoard));
				parentToChildMoves[0].push_back(chosenMove);
				gameBoardStates.push_back(cloneState(pieceMove.getPieceBoard()));
				pieceMove.setPieceBoard(gameBoard);
			}
			counter++;
		}
		firstRun = false;
		parentToChild.resize(parentToChild.size()+1);
		parentToChildMoves.resize(parentToChildMoves.size()+1);
		breadthFirstSearch(pieceMove, numberOfMoves, firstRun);
	}else{
		currentPosition = gameBoardStates.size() - movesMade;
		while(movesToBeMade < movesMade){
			gameBoard = cloneState(nonNormalBoardStates[currentPosition]);
			//displayState(gameBoard);
			pieceMove.setPieceBoard(gameBoard);
			possibleMoves = pieceMove.moveAllGeneration();
			parentToChild[parentToChild.size()-1].push_back(cloneState(gameBoard));
			parentToChildMoves[parentToChildMoves.size()-1].push_back("X");
			while(counter < possibleMoves.size()){
				currentMove[0] = possibleMoves[counter];
				chosenMove = pieceMove.applyMove(currentMove);
				clonedBoard = cloneState(pieceMove.getPieceBoard());
				// Normalizes the board after making the move
				pieceMove.setPieceBoard(normalizeState(pieceMove.getPieceBoard()));
				// Checks to see if the state alreadt exists
				// If so, do not make the move
				// If not, make the move and store the new state
				for(int i = 0; i < gameBoardStates.size(); i++){
					if(stateCompare(gameBoardStates[i], pieceMove.getPieceBoard())){
						stateExists = true;
					}
					if(stateExists){break;}
				}
				if(stateExists){
					pieceMove.setPieceBoard(gameBoard);
				}else{
					nodes++;
					numberOfMoves++;
					parentToChild[parentToChild.size()-1].push_back(cloneState(clonedBoard));
					parentToChildMoves[parentToChildMoves.size()-1].push_back(chosenMove);
					nonNormalBoardStates.push_back(cloneState(clonedBoard));
					gameBoardStates.push_back(cloneState(pieceMove.getPieceBoard()));
					if(puzzleComplete(pieceMove.getPieceBoard())){
						gameBoard = cloneState(clonedBoard);
						return;
					}
					pieceMove.setPieceBoard(gameBoard);
				}
				stateExists = false;
				counter++;
			}
			counter = 0;
			currentPosition++;
			movesToBeMade++;
		}
		parentToChild.resize(parentToChild.size()+1);
		parentToChildMoves.resize(parentToChildMoves.size()+1);
		breadthFirstSearch(pieceMove, numberOfMoves, firstRun);
	}
}

// Depth first puzzle search (DONE)
void depthFirstSearch(PieceMove pieceMove){
	// Creates a stable board to return to if the branch does not turn up the solution
	vector<vector<int>> stableBoard = cloneState(gameBoard);
	vector<string> possibleMoves = pieceMove.moveAllGeneration();
	vector<string> currentMove;
	string chosenMove;
	int counter = 0;
	bool stateExists = false;
	currentMove.resize(1);

	while(counter < possibleMoves.size()){
		pieceMove.setPieceBoard(gameBoard);
		currentMove[0] = possibleMoves[counter];
		chosenMove = pieceMove.applyMove(currentMove);
		clonedBoard = cloneState(pieceMove.getPieceBoard());
		// Normalizes the board after making the move
		pieceMove.setPieceBoard(normalizeState(pieceMove.getPieceBoard()));
		// Checks to see if the state alreadt exists
		// If so, do not make the move
		// If not, make the move and store the new state
		for(int i = 0; i < gameBoardStates.size(); i++){
			if(stateCompare(gameBoardStates[i], pieceMove.getPieceBoard())){
				stateExists = true;
			}
			if(stateExists){break;}
		}
		if(stateExists){
			pieceMove.setPieceBoard(gameBoard);
		}else{
			// Adds the move made to the movesToSolution vector
			nodes++;
			movesToSolution.push_back(chosenMove);
			gameBoard = cloneState(clonedBoard);
			gameBoardStates.push_back(cloneState(pieceMove.getPieceBoard()));
			statesToSolution.push_back(cloneState(clonedBoard));
			pieceMove.setPieceBoard(clonedBoard);
			//displayState(statesToSolution[statesToSolution.size()-1]);
			// Checks if the solution has been found so that another branch doesn't get traversed
			if(puzzleComplete(gameBoard)){return;}
			depthFirstSearch(pieceMove);
			// After the solution is found, break out of the method
			if(puzzleComplete(gameBoard)){return;}
			// If the branch reaches the end without finding the solution, remove the unsuccessful moves from the movesToSolution vector
			movesToSolution.pop_back();
			statesToSolution.pop_back();
		}
		counter++;
		stateExists = false;
		// Returns the the stable board to move to the next branch
		gameBoard = cloneState(stableBoard);
	}
}

// Iterative deepening puzzle search (RAN OUT OF TIME)
void iterativeDeepeningSearch(PieceMove pieceMove, vector<vector<vector<int>>> gameBoardStates){

}

// Finds the path taken for the solution (DONE)
void breadthFirstSearchSteps(){
	BSTStatesToSolution.push_back(parentToChild[parentToChild.size()-1][parentToChild[parentToChild.size()-1].size()-1]);
	BSTMovesToSolution.push_back(parentToChildMoves[parentToChildMoves.size()-1][parentToChildMoves[parentToChildMoves.size()-1].size()-1]);

	for(int i = parentToChild.size()-1; i >= 0; i--){
		for(int j = parentToChild[i].size()-1; j >= 1; j--){
			if(stateCompare(parentToChild[i][j], BSTStatesToSolution[BSTStatesToSolution.size()-1])){
				BSTStatesToSolution.push_back(parentToChild[i][0]);
				BSTMovesToSolution.push_back(parentToChildMoves[i][j]);
			}
		}
	}

	for(int i = BSTStatesToSolution.size() - 1; i >= 0; i--){
		cout << BSTMovesToSolution[i] << endl;
	}
	displayState(BSTStatesToSolution[0]);
	length = BSTStatesToSolution.size();
}

int main(){
	// WORKING
	// RandomWalks method call
	cout << "Random Walk: " << endl;
	string randomWalkFile = "SBP-level0.txt";
	randomWalkBoard = createBoard(randomWalkBoard, randomWalkFile);
	randomWalkBoard = normalizeState(randomWalkBoard);
	PieceMove randomPieceMove(randomWalkBoard);
	randomWalks(randomPieceMove, 3);


	string boardFile = "SBP-level1.txt";
	vector<vector<int>> gameBoardClone;
	parentToChild.resize(1);
	parentToChildMoves.resize(1);

	gameBoard = createBoard(gameBoard, boardFile);
	gameBoard = normalizeState(gameBoard);
	gameBoardClone = cloneState(gameBoard);
	gameBoardStates.push_back(gameBoard);
	parentToChild[0].push_back(gameBoard);
	parentToChildMoves[0].push_back("X");
	nonNormalBoardStates.push_back(gameBoard);
	PieceMove pieceMove(gameBoard);

	// WORKING
	// BFS method call
	cout << "Breadth-First Search Solution: " << endl;
	const clock_t bfs_time = clock();
	breadthFirstSearch(pieceMove, 0, true);
	breadthFirstSearchSteps();
	cout << "Nodes: " << nodes << " Time: " << float(clock() - bfs_time)/CLOCKS_PER_SEC << " Length: " << length << endl;

	nodes = 0;
	length = 0;

	gameBoard.clear();
	gameBoardStates.clear();
	gameBoard = createBoard(gameBoard, boardFile);
	gameBoard = normalizeState(gameBoard);
	gameBoardStates.push_back(gameBoard);
	
	// WORKING
	// DFS method call
	cout << "Depth-First Search Solution:" << endl;
	const clock_t dfs_time = clock();
	depthFirstSearch(gameBoard);
	// Displays the moves made that led to the solution of the board
	for(int i = 0; i < movesToSolution.size(); i++){
		cout << movesToSolution[i] << endl;
	}
	displayState(statesToSolution[statesToSolution.size()-1]);
	length = movesToSolution.size();
	cout << "Nodes: " << nodes << " Time: " << float(clock() - dfs_time)/CLOCKS_PER_SEC << " Length: " << length << endl;

	system("pause");
	return 0;
}