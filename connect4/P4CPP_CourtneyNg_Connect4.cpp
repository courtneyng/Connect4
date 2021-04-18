/*
Courtney Ng
Period 4
Connect 4
*/

#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);

//global var
char board[6][7];

/*************** prototyping ***************/

//change board to underscores
void undscrs(char board[6][7], int row, int col);

//print board
void printBoard(int row, int col);

//place piece in column
void drop(char xo, int col, int row);

                      
//------------------------------------------------------------


//wins
//horizontal win
bool h_win(char b[6][7], int row, int col);
	
//vertical win	
bool v_win(char b[6][7], int row, int col);

// diagonal wins
bool d_win(char b[6][7], int row, int col);

//win check
bool won(char b[6][7], int row, int col){
	return h_win(b, row, col) || v_win(b, row, col) || d_win(b, row, col);	
	
}
/*******************************************/

/******************************************************** MAIN ********************************************************/
int main(){
	
	/******* var *******/
	int row, col, placement, ans;
	char xo;
	/******* end var *******/
	
	
	/******* intro/setup *******/
	SetConsoleTextAttribute(color, 12);
	//set instructions in a light red color
	
	
	/*** intro***/
	cout << "*******************************************************" << endl;
	cout << "                       Connect 4                       " << endl;
	cout << "                      how to win:                      " << endl;
	cout << "                 get 4 pieces in a row                 " << endl;
	cout << "       horizontally, vertically, or diagnonally        " << endl;
	cout << "*******************************************************" << endl << endl;
	/*** intro***/
	
	
	//change to a bright yellow
	SetConsoleTextAttribute(color, 14);
	
	
	
	/*** board ***/
	cout << " (1) customized board or (2) normal board (6 by 7): ";
	cin >> ans;
	//abs smallest board up to reg
	if(ans == 1){
		
		do{
			/*** setup ***/
			//customizable board
			cout << endl <<"          set board size within the limits" << endl << endl;
			
			cout << "          [min: 4 | max: 6] set row: ";
			cin >> row;
			
			cout << endl << "          [min: 4 | max: 7] set column: ";
			cin >> col;
			/*** setup ***/
			
		}while(col < 4 || row < 4 || col > 7 || row > 6 );
		
	}
	else{
		cout << "          the board will be set to the normal connect 4, 6 by 7" << endl << endl;
		row = 6; col = 7;
	}
	/*** board ***/
	
	
	undscrs(board, row, col);
	printBoard(row, col);
	
	/******* end intro/setup *******/
	
	/*************** game ***************/
	for(int k = 0; k < row*col && !won(board, row, col); k++){
		//SetConsoleTextAttribute(color, 7);
		
		/******* alternate turns *******/
		if(k % 2 == 0){ 
			xo = 'x';
			SetConsoleTextAttribute(color, 4); 
		} 
		
		/** x is red; o is yellow **/
		
		else{
			xo = 'o';
			SetConsoleTextAttribute(color, 14);
		}
		/******* alternate turns *******/
		
		cout << xo;
		
		cout << " is going " << endl;
		
		
		do{
		SetConsoleTextAttribute(color, 7);
		cout << "place into column: ";
		cin >> placement;
		//fix top corner color
		SetConsoleTextAttribute(color, 1);
		}while(placement > col || placement < 1);
		
		
		if(board[0][placement-1] != '_'){
			cout << "full, pick a different spot." << endl;
		}
			
		else{
			drop(xo, placement-1, row);
		}
			
		printBoard(row, col);
	}
	/*** win ***/
	if(won(board, row, col)){
		SetConsoleTextAttribute(color, 10);
		cout << xo;
		cout << " won the game";
		SetConsoleTextAttribute(color, 7);
	}

	else{
		SetConsoleTextAttribute(color, 10);
		cout << "deadlock.";
		SetConsoleTextAttribute(color, 7);
	}
	/*** win ***/
		
} /******************************************************** MAIN ********************************************************/

//change board to underscores
void undscrs(char board[6][7], int row, int col){
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col; c++){
			SetConsoleTextAttribute(color, 1);
			board[r][c] = '_';
		}
	}
}

//print board
void printBoard(int row, int col){
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col; c++){
			if(board[r][c] == 'x'){
				SetConsoleTextAttribute(color, 4);
			}
				
			else if(board[r][c] == 'o'){
				SetConsoleTextAttribute(color, 14); 
			}
				
			cout << board[r][c] << " ";
			SetConsoleTextAttribute(color, 1); 
		}
		cout << endl;
	}
	
	for(int r = 1; r <= col; r++){
		SetConsoleTextAttribute(color, 11);
		cout << r << " ";
	}
	cout << endl;
}


//place piece in column
void drop(char xo, int col, int row){
	bool placed = false;	
	for(int r = row; r >= 0 && !placed; r--){
		if(board[r][col] == '_'){
			board[r][col] = xo;
			placed = true;
		}
	}	
}
//horizontal win
bool h_win(char b[6][7], int row, int col){
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col-3; c++){
			if(b[r][c] != '_' && b[r][c] == b[r][c+1] && b[r][c+1] == b[r][c+2] && b[r][c+2] == b[r][c+3]){
				return true;
			}
		}
	}
	return false;
}
	
//vertical win	
bool v_win(char b[6][7], int row, int col){
	for(int c = 0; c < col; c++){
		for(int r = 0; r < col-3; r++){
			if(b[r][c] != '_' && b[r][c] == b[r+1][c] && b[r+1][c] == b[r+2][c] && b[r+2][c] == b[r+3][c])
				return true;
		}
	}
	return false;
}

// diagonal wins
bool d_win(char b[6][7], int row, int col){
	
	for(int r = 0; r < row-3; r++){
		for(int c = 0; c < col-3; c++){
			if(b[r][c] != '_' && b[r][c] == b[r+1][c+1] && b[r+1][c+1] == b[r+2][c+2] && b[r+2][c+2] == b[r+3][c+3])
				return true;
		}
	}
	
	for(int r = row; r >= row-3; r--){
		for(int c = 0; c < col-3; c++){
			if(b[r][c] != '_' && b[r][c] == b[r-1][c+1] && b[r-1][c+1] == b[r-2][c+2] && b[r-2][c+2] == b[r-3][c+3])
				return true;
		}
	}
	return false;
}


