
/* The following program is a game of Cylinditrical Mule Checkers.
Authors: Kenny Bui, Ethan Silver and Amir Eghbal
Professor: Ghassan Hamarneh*/
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

//Global Constants
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72;
const int NOPLAYER = 0;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;

//Functions
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);
bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLoc, int yLoc);
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLoc, int yLoc);
bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex);
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
int ConvertToNum(int xLocation, int yLocation, int numRowsInBoard);
void ConvertToXY(int number, int &xLocation, int &yLocation, int numRowsInBoard);

//Main Function
int main()
{
	//Main variables
	int numRowsInBoard = 0;
	int evenOdd = 0;
	int counter1 = 0;
	int counter = 0;
	int maxAttempts = 3;
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0 };
	int player = 0;
	int xIndicesMove[MAX_PIECES] = { 0 };
	int yIndicesMove[MAX_PIECES] = { 0 };
	int xIndicesJump[MAX_PIECES] = { 0 };
	int yIndicesJump[MAX_PIECES] = { 0 };
	int numCanJump = 0;
	int numCanMove = 0;
	char endGame;
	int theFromSquare = 0;
	int theToSquare = 0;
	int i = 0;
	int j = 0;
	int canJump[MAX_PIECES] = { 0 };
	int xLocation = 0;
	int yLocation = 0;
	int fromXLocation = 0;
	int fromYLocation = 0;
	int toXLocation = 0;
	int toYLocation = 0;
	bool jumpResult = false;
	bool ENDOFWORLD = false;
	bool isJumpResult = false;
	int tester = 0;
	bool test2 = false;
	bool test3 = false;


	player = 1; // White player starts
	//Board prompt and error checking. Max times to renter is 3
	for (counter1 = 0; counter1 < maxAttempts; counter1++)
	{
		cout << "Enter the number of squares along each edge of the board" << endl;
		cin >> numRowsInBoard;
		evenOdd = numRowsInBoard % 2;

		if (cin.fail())
		{
			cerr << "ERROR: Board size is not an integer" << endl;
			cerr << "8 <= number of squares <= 18" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		else if (numRowsInBoard > 18)
		{
			cerr << "ERROR: Board size too large" << endl;
			cerr << "8 <= number of squares <= 18" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		else if (numRowsInBoard < 8)
		{
			cerr << "ERROR: Board size too small" << endl;
			cerr << "8 <= number of squares <= 18" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		else if (evenOdd != 0)
		{
			cerr << "ERROR: Board size is odd" << endl;
			cerr << "8 <= number of squares <= 18" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		else if (8 <= numRowsInBoard && numRowsInBoard <= 18)
		{
			break;
		}
	}
	if (counter1 == 3)
	{
		cerr << "ERROR: Too many errors entering the size of the board." << endl;
		return 1;
	}
	InitializeBoard(myCMCheckersBoard, numRowsInBoard); //Board is being initialized
	DisplayBoard(myCMCheckersBoard, numRowsInBoard); //Displaying the board
	numCanJump = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump); //Numbers that can jump
	numCanMove = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove); //Numbers that can move
	//If no moves left game ends
	while (!ENDOFWORLD) //Game begins
	{
		player = 1;
		if (player == 1)
		{
			cout << "White takes a turn." << endl;
			while (player == 1)
			{
				cout << "Enter the square number of the checker you want to move" << endl;
				//White player errors for incorrect from checker
				if (!(cin >> theFromSquare))
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: You did not enter an integer" << endl;
					cerr << "Try again" << endl;
					continue;
				}
				if (theFromSquare > ((numRowsInBoard * numRowsInBoard) - 1) || theFromSquare < 0)
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: That square is not on the board." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				//Converting number inputed to X and Y coordinates
				ConvertToXY(theFromSquare, xLocation, yLocation, numRowsInBoard);
				fromXLocation = xLocation;
				fromYLocation = yLocation;
				//More errors for incorrect input
				if (myCMCheckersBoard[yLocation][xLocation] == REDSOLDIER || myCMCheckersBoard[yLocation][xLocation] == REDMULE || myCMCheckersBoard[yLocation][xLocation] == REDKING)
				{
					cerr << "ERROR: That square contains an opponent's checker." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				else if (myCMCheckersBoard[yLocation][xLocation] == 0)
				{
					cerr << "ERROR: That square is empty." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				//Error for if there is jump available and wrong move is picked
				if ((IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocation, yLocation) == false) && numCanJump > 0)
				{
					cout << "ERROR: You can jump with another checker, you may not move your chosen checker." << endl;
					cout << "You can jump using checkers on the following squares :";
					for (i = 0; i < numCanJump; i++)
					{
						canJump[i] = ConvertToNum(xIndicesJump[i], yIndicesJump[i], numRowsInBoard);
						cout << " " << canJump[i];
					}
					cout << "\nTry again" << endl;
					continue;
				}
				//Error for if from checker has no moves
				if ((IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocation, yLocation) == false) && (IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, xLocation, yLocation) == false))
				{
					cerr << "ERROR: There is no legal move for this checker." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				break;
			}
			//The to checker section
			while (player == 1)
			{
				xLocation = 0;
				yLocation = 0;
				cout << "Enter the square number of the square you want to move your checker to" << endl;

				//To checker errors
				if (!(cin >> theToSquare))
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: You did not enter an integer" << endl;
					cerr << "Try again" << endl;
					continue;
				}
				if (theToSquare > ((numRowsInBoard * numRowsInBoard) - 1) || theToSquare < 0)
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: It is not possible to move to a square that is not on the board." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				//Testing to see if it is the second jump 
				if (tester == 1)
				{
					ConvertToXY(theFromSquare, xLocation, yLocation, numRowsInBoard);
					fromXLocation = xLocation;
					fromYLocation = yLocation;
					tester = 0;
				}
				//Converting to-number to X and Y coordinates
				ConvertToXY(theToSquare, xLocation, yLocation, numRowsInBoard);
				toXLocation = xLocation;
				toYLocation = yLocation;
				//More errors
				if (myCMCheckersBoard[yLocation][xLocation] != NOPLAYER)
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: It is not possible to move to a square that is already occupied." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				//If checker can be jumped with this error tells them to pick another position
				if ((IsJump(myCMCheckersBoard, numRowsInBoard, player, fromXLocation, fromYLocation) == true) && (IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, fromXLocation, fromYLocation) == true))
				{
					if ((abs(fromYLocation - toYLocation)) == 1)
					{
						cerr << "ERROR: You can jump with this checker, you must jump not move 1 space." << endl;
						cerr << "Try again" << endl;
						continue;
					}
				}
				//Actual move happens
				test3 = (IsJump(myCMCheckersBoard, numRowsInBoard, player, fromXLocation, fromYLocation));
				MakeMove(myCMCheckersBoard, numRowsInBoard, player, theFromSquare, theToSquare, jumpResult);
				if (test3 == false)
				{
					tester = 0;
					break;
				}
				numCanJump = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump);
				numCanMove = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove);
				if (numCanJump == 0 && numCanMove == 0)
				{
					cout << "White is unable to move." << endl;
					cout << "GAME OVER, Red has won." << endl;
					cout << "Enter any character to close the game.";
					if (cin >> endGame)
					{
						return 0;
					}
				}
				if (jumpResult == false)
				{
					continue;
				}
				//Implementation for possible double jump
				isJumpResult = IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocation, yLocation);
				if (isJumpResult == true)
				{
					DisplayBoard(myCMCheckersBoard, numRowsInBoard);
					cout << "You can jump again, Please enter the next square you wish to move your checker to" << endl;
					theFromSquare = theToSquare;
					tester = 1;
					continue;
				}
				break;
			}
			//Board displayed again and win condition checked
			DisplayBoard(myCMCheckersBoard, numRowsInBoard);
			if (CheckWin(myCMCheckersBoard, numRowsInBoard) == true)
			{
				cout << "Enter any character to terminate the game then press the enter key" << endl;
				cout << "The program will terminate after the player presses the enter key." << endl;
				if (cin >> endGame)
				{
					return 0;
				}
			}
		}
		//Red player's turn
		player = 2;
		if (player == 2)
		{
			cout << "Red takes a turn." << endl;
			//From checker prompt and errors
			while (player == 2)
			{
				cout << "Enter the square number of the checker you want to move" << endl;

				if (!(cin >> theFromSquare))
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: You did not enter an integer" << endl;
					cerr << "Try again" << endl;
					continue;
				}
				if (theFromSquare > ((numRowsInBoard * numRowsInBoard) - 1) || theFromSquare < 0)
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: That square is not on the board." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				// Converting number to X and Y coordinates
				ConvertToXY(theFromSquare, xLocation, yLocation, numRowsInBoard);
				fromXLocation = xLocation;
				fromYLocation = yLocation;
				//More errors
				if (myCMCheckersBoard[yLocation][xLocation] == WHITESOLDIER || myCMCheckersBoard[yLocation][xLocation] == WHITEMULE || myCMCheckersBoard[yLocation][xLocation] == WHITEKING)
				{
					cerr << "ERROR: That square contains an opponent's checker." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				else if (myCMCheckersBoard[yLocation][xLocation] == 0)
				{
					cerr << "ERROR: That square is empty." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				//Error checking if jump is available and not chosen as a move
				if ((IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocation, yLocation) == false) && numCanJump > 0)
				{
					cout << "ERROR: You can jump with another checker, you may not move your chosen checker." << endl;
					cout << "You can jump using checkers on the following squares :";
					for (i = 0; i < numCanJump; i++)
					{
						canJump[i] = ConvertToNum(xIndicesJump[i], yIndicesJump[i], numRowsInBoard);
						cout << " " << canJump[i];
					}
					cout << "\nTry again" << endl;
					continue;
				}
				if ((IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocation, yLocation) == false) && (IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, xLocation, yLocation) == false))
				{
					cerr << "ERROR: There is no legal move for this checker." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				break;
			}
			//To checker prompt and errors
			while (player == 2)
			{
				xLocation = 0;
				yLocation = 0;
				cout << "Enter the square number of the square you want to move your checker to" << endl;

				if (!(cin >> theToSquare))
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: You did not enter an integer" << endl;
					cerr << "Try again" << endl;
					continue;
				}
				if (theToSquare > ((numRowsInBoard * numRowsInBoard) - 1) || theToSquare < 0)
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: It is not possible to move to a square that is not on the board." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				//Testing to see if it is the second jump 
				if (tester == 1)
				{
					ConvertToXY(theFromSquare, xLocation, yLocation, numRowsInBoard);
					fromXLocation = xLocation;
					fromYLocation = yLocation;
					tester = 0;
				}
				//converstion of number to X and Y Postions
				ConvertToXY(theToSquare, xLocation, yLocation, numRowsInBoard);
				toXLocation = xLocation;
				toYLocation = yLocation;
				if (myCMCheckersBoard[yLocation][xLocation] != NOPLAYER)
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cerr << "ERROR: It is not possible to move to a square that is already occupied." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				//If Jump available it should be made as supposed to single move
				if ((IsJump(myCMCheckersBoard, numRowsInBoard, player, fromXLocation, fromYLocation) == true) && (IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, fromXLocation, fromYLocation) == true))
				{
					if ((abs(fromYLocation - toYLocation)) == 1)
					{
						cerr << "ERROR: You can jump with this checker, you must jump not move 1 space." << endl;
						cerr << "Try again" << endl;
						continue;
					}
				}
				//Actual move happens
				test2 = (IsJump(myCMCheckersBoard, numRowsInBoard, player, fromXLocation, fromYLocation));
				MakeMove(myCMCheckersBoard, numRowsInBoard, player, theFromSquare, theToSquare, jumpResult);
				if (test2 == false)
				{
					break;
				}
				numCanJump = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump);
				numCanMove = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove);
				if (numCanJump == 0 && numCanMove == 0)
				{
					cout << "Red is unable to move." << endl;
					cout << "GAME OVER, White has won." << endl;
					cout << "Enter any character to close the game.";
					if (cin >> endGame)
					{
						return 0;
					}
				}
				if (jumpResult == false)
				{
					continue;
				}
				//Implementation for possible double jump
				isJumpResult = IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocation, yLocation);
				if (isJumpResult == true)
				{
					DisplayBoard(myCMCheckersBoard, numRowsInBoard);
					cout << "You can jump again, Please enter the next square you wish to move your checker to" << endl;
					theFromSquare = theToSquare;
					tester = 1;
					continue;
				}
				break;
			}
			DisplayBoard(myCMCheckersBoard, numRowsInBoard);
			if (CheckWin(myCMCheckersBoard, numRowsInBoard) == true)
			{
				cout << "Enter any character to terminate the game then press the enter key" << endl;
				cout << "The program will terminate after the player presses the enter key." << endl;
				if (cin >> endGame)
				{
					return 0;
				}
			}
		}

	}
	return 0;
}
//Intialization of the board. We had a better way to initialize(@easy) but we left it the same because it works
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int ind1 = 0;
	int ind2 = 0;

	if (numRowsInBoard == 8)
	{
		for (ind1 = 0; ind1 < numRowsInBoard; ind1++)
		{
			for (ind2 = 0; ind2 < (numRowsInBoard / 2); ind2++)
			{
				CMCheckersBoard[0][(2 * ind2)] = 0;
				CMCheckersBoard[0][(2 * ind2) + 1] = 2;
				CMCheckersBoard[1][(2 * ind2)] = 1;
				CMCheckersBoard[1][(2 * ind2) + 1] = 0;
				CMCheckersBoard[2][(2 * ind2)] = 0;
				CMCheckersBoard[2][(2 * ind2) + 1] = 1;
				CMCheckersBoard[3][ind2] = 0;
				CMCheckersBoard[4][ind2] = 0;
				CMCheckersBoard[5][(2 * ind2) + 1] = 0;
				CMCheckersBoard[5][(2 * ind2)] = 4;
				CMCheckersBoard[6][(2 * ind2) + 1] = 4;
				CMCheckersBoard[6][(2 * ind2)] = 0;
				CMCheckersBoard[7][(2 * ind2)] = 5;
				CMCheckersBoard[7][(2 * ind2) + 1] = 0;
			}
		}
	}
	if (numRowsInBoard == 10)
	{
		for (ind1 = 0; ind1 < numRowsInBoard; ind1++)
		{
			for (ind2 = 0; ind2 < (numRowsInBoard / 2); ind2++)
			{
				//0 Empty, 1 WS, 2 WM, 3 WK, 4 RS, 5 RM, 6 RK
				CMCheckersBoard[0][(2 * ind2)] = 0;
				CMCheckersBoard[0][(2 * ind2) + 1] = 2;
				CMCheckersBoard[1][(2 * ind2)] = 1;
				CMCheckersBoard[1][(2 * ind2) + 1] = 0;
				CMCheckersBoard[2][(2 * ind2)] = 0;
				CMCheckersBoard[2][(2 * ind2) + 1] = 1;
				CMCheckersBoard[3][(2 * ind2)] = 1;
				CMCheckersBoard[3][(2 * ind2) + 1] = 0;
				CMCheckersBoard[4][ind2] = 0;
				CMCheckersBoard[5][ind2] = 0;
				CMCheckersBoard[6][(2 * ind2) + 1] = 4;
				CMCheckersBoard[6][(2 * ind2)] = 0;
				CMCheckersBoard[7][(2 * ind2) + 1] = 0;
				CMCheckersBoard[7][(2 * ind2)] = 4;
				CMCheckersBoard[8][(2 * ind2) + 1] = 4;
				CMCheckersBoard[8][(2 * ind2)] = 0;
				CMCheckersBoard[9][(2 * ind2)] = 5;
				CMCheckersBoard[9][(2 * ind2) + 1] = 0;
			}
		}

	}
	if (numRowsInBoard == 12)
	{
		for (ind1 = 0; ind1 < numRowsInBoard; ind1++)
		{
			for (ind2 = 0; ind2 < (numRowsInBoard / 2); ind2++)
			{
				//0 Empty, 1 WS, 2 WM, 3 WK, 4 RS, 5 RM, 6 RK
				CMCheckersBoard[0][(2 * ind2)] = 0;
				CMCheckersBoard[0][(2 * ind2) + 1] = 2;
				CMCheckersBoard[1][(2 * ind2)] = 1;
				CMCheckersBoard[1][(2 * ind2) + 1] = 0;
				CMCheckersBoard[2][(2 * ind2)] = 0;
				CMCheckersBoard[2][(2 * ind2) + 1] = 1;
				CMCheckersBoard[3][(2 * ind2)] = 1;
				CMCheckersBoard[3][(2 * ind2) + 1] = 0;
				CMCheckersBoard[4][(2 * ind2)] = 0;
				CMCheckersBoard[4][(2 * ind2) + 1] = 1;
				CMCheckersBoard[5][ind2] = 0;
				CMCheckersBoard[6][ind2] = 0;
				CMCheckersBoard[7][(2 * ind2) + 1] = 0;
				CMCheckersBoard[7][(2 * ind2)] = 4;
				CMCheckersBoard[8][(2 * ind2) + 1] = 4;
				CMCheckersBoard[8][(2 * ind2)] = 0;
				CMCheckersBoard[9][(2 * ind2) + 1] = 0;
				CMCheckersBoard[9][(2 * ind2)] = 4;
				CMCheckersBoard[10][(2 * ind2) + 1] = 4;
				CMCheckersBoard[10][(2 * ind2)] = 0;
				CMCheckersBoard[11][(2 * ind2)] = 5;
				CMCheckersBoard[11][(2 * ind2) + 1] = 0;
			}
		}
	}
	if (numRowsInBoard == 14)
	{
		for (ind1 = 0; ind1 < numRowsInBoard; ind1++)
		{
			for (ind2 = 0; ind2 < (numRowsInBoard / 2); ind2++)
			{
				//0 Empty, 1 WS, 2 WM, 3 WK, 4 RS, 5 RM, 6 RK
				CMCheckersBoard[0][(2 * ind2)] = 0;
				CMCheckersBoard[0][(2 * ind2) + 1] = 2;
				CMCheckersBoard[1][(2 * ind2)] = 1;
				CMCheckersBoard[1][(2 * ind2) + 1] = 0;
				CMCheckersBoard[2][(2 * ind2)] = 0;
				CMCheckersBoard[2][(2 * ind2) + 1] = 1;
				CMCheckersBoard[3][(2 * ind2)] = 1;
				CMCheckersBoard[3][(2 * ind2) + 1] = 0;
				CMCheckersBoard[4][(2 * ind2)] = 0;
				CMCheckersBoard[4][(2 * ind2) + 1] = 1;
				CMCheckersBoard[5][(2 * ind2)] = 1;
				CMCheckersBoard[5][(2 * ind2) + 1] = 0;
				CMCheckersBoard[6][ind2] = 0;
				CMCheckersBoard[7][ind2] = 0;
				CMCheckersBoard[8][(2 * ind2) + 1] = 4;
				CMCheckersBoard[8][(2 * ind2)] = 0;
				CMCheckersBoard[9][(2 * ind2) + 1] = 0;
				CMCheckersBoard[9][(2 * ind2)] = 4;
				CMCheckersBoard[10][(2 * ind2) + 1] = 4;
				CMCheckersBoard[10][(2 * ind2)] = 0;
				CMCheckersBoard[11][(2 * ind2) + 1] = 0;
				CMCheckersBoard[11][(2 * ind2)] = 4;
				CMCheckersBoard[12][(2 * ind2) + 1] = 4;
				CMCheckersBoard[12][(2 * ind2)] = 0;
				CMCheckersBoard[13][(2 * ind2)] = 5;
				CMCheckersBoard[13][(2 * ind2) + 1] = 0;
			}
		}
	}
	if (numRowsInBoard == 16)
	{
		for (ind1 = 0; ind1 < numRowsInBoard; ind1++)
		{
			for (ind2 = 0; ind2 < (numRowsInBoard / 2); ind2++)
			{
				//0 Empty, 1 WS, 2 WM, 3 WK, 4 RS, 5 RM, 6 RK
				CMCheckersBoard[0][(2 * ind2)] = 0;
				CMCheckersBoard[0][(2 * ind2) + 1] = 2;
				CMCheckersBoard[1][(2 * ind2)] = 1;
				CMCheckersBoard[1][(2 * ind2) + 1] = 0;
				CMCheckersBoard[2][(2 * ind2)] = 0;
				CMCheckersBoard[2][(2 * ind2) + 1] = 1;
				CMCheckersBoard[3][(2 * ind2)] = 1;
				CMCheckersBoard[3][(2 * ind2) + 1] = 0;
				CMCheckersBoard[4][(2 * ind2)] = 0;
				CMCheckersBoard[4][(2 * ind2) + 1] = 1;
				CMCheckersBoard[5][(2 * ind2)] = 1;
				CMCheckersBoard[5][(2 * ind2) + 1] = 0;
				CMCheckersBoard[6][(2 * ind2)] = 0;
				CMCheckersBoard[6][(2 * ind2) + 1] = 1;
				CMCheckersBoard[7][ind2] = 0;
				CMCheckersBoard[8][ind2] = 0;
				CMCheckersBoard[9][(2 * ind2) + 1] = 0;
				CMCheckersBoard[9][(2 * ind2)] = 4;
				CMCheckersBoard[10][(2 * ind2) + 1] = 4;
				CMCheckersBoard[10][(2 * ind2)] = 0;
				CMCheckersBoard[11][(2 * ind2) + 1] = 0;
				CMCheckersBoard[11][(2 * ind2)] = 4;
				CMCheckersBoard[12][(2 * ind2) + 1] = 4;
				CMCheckersBoard[12][(2 * ind2)] = 0;
				CMCheckersBoard[13][(2 * ind2) + 1] = 0;
				CMCheckersBoard[13][(2 * ind2)] = 4;
				CMCheckersBoard[14][(2 * ind2) + 1] = 4;
				CMCheckersBoard[14][(2 * ind2)] = 0;
				CMCheckersBoard[15][(2 * ind2)] = 5;
				CMCheckersBoard[15][(2 * ind2) + 1] = 0;
			}
		}
	}
	if (numRowsInBoard == 18)
	{
		for (ind1 = 0; ind1 < numRowsInBoard; ind1++)
		{
			for (ind2 = 0; ind2 < (numRowsInBoard / 2); ind2++)
			{
				//0 Empty, 1 WS, 2 WM, 3 WK, 4 RS, 5 RM, 6 RK
				CMCheckersBoard[0][(2 * ind2)] = 0;
				CMCheckersBoard[0][(2 * ind2) + 1] = 2;
				CMCheckersBoard[1][(2 * ind2)] = 1;
				CMCheckersBoard[1][(2 * ind2) + 1] = 0;
				CMCheckersBoard[2][(2 * ind2)] = 0;
				CMCheckersBoard[2][(2 * ind2) + 1] = 1;
				CMCheckersBoard[3][(2 * ind2)] = 1;
				CMCheckersBoard[3][(2 * ind2) + 1] = 0;
				CMCheckersBoard[4][(2 * ind2)] = 0;
				CMCheckersBoard[4][(2 * ind2) + 1] = 1;
				CMCheckersBoard[5][(2 * ind2)] = 1;
				CMCheckersBoard[5][(2 * ind2) + 1] = 0;
				CMCheckersBoard[6][(2 * ind2)] = 0;
				CMCheckersBoard[6][(2 * ind2) + 1] = 1;
				CMCheckersBoard[7][(2 * ind2)] = 1;
				CMCheckersBoard[7][(2 * ind2) + 1] = 0;
				CMCheckersBoard[8][ind2] = 0;
				CMCheckersBoard[9][ind2] = 0;
				CMCheckersBoard[10][(2 * ind2) + 1] = 4;
				CMCheckersBoard[10][(2 * ind2)] = 0;
				CMCheckersBoard[11][(2 * ind2) + 1] = 0;
				CMCheckersBoard[11][(2 * ind2)] = 4;
				CMCheckersBoard[12][(2 * ind2) + 1] = 4;
				CMCheckersBoard[12][(2 * ind2)] = 0;
				CMCheckersBoard[13][(2 * ind2) + 1] = 0;
				CMCheckersBoard[13][(2 * ind2)] = 4;
				CMCheckersBoard[14][(2 * ind2) + 1] = 4;
				CMCheckersBoard[14][(2 * ind2)] = 0;
				CMCheckersBoard[15][(2 * ind2) + 1] = 0;
				CMCheckersBoard[15][(2 * ind2)] = 4;
				CMCheckersBoard[16][(2 * ind2) + 1] = 4;
				CMCheckersBoard[16][(2 * ind2)] = 0;
				CMCheckersBoard[17][(2 * ind2)] = 5;
				CMCheckersBoard[17][(2 * ind2) + 1] = 0;
			}
		}
	}
}

//Displaying the board
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	string DisplayChecker[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	int ind1 = 0;
	int ind2 = 0;
	int num = 0;
	string intToString;

	for (ind1 = 0; ind1 < numRowsInBoard; ind1++)
	{
		for (ind2 = 0; ind2 < numRowsInBoard; ind2++)
		{
			intToString = to_string(num);
			DisplayChecker[ind1][ind2] = intToString;
			num++;

			if (CMCheckersBoard[ind1][ind2] == 1)
			{
				DisplayChecker[ind1][ind2] = "WS";
			}
			if (CMCheckersBoard[ind1][ind2] == 2)
			{
				DisplayChecker[ind1][ind2] = "WM";
			}
			if (CMCheckersBoard[ind1][ind2] == 3)
			{
				DisplayChecker[ind1][ind2] = "WK";
			}
			if (CMCheckersBoard[ind1][ind2] == 4)
			{
				DisplayChecker[ind1][ind2] = "RS";
			}
			if (CMCheckersBoard[ind1][ind2] == 5)
			{
				DisplayChecker[ind1][ind2] = "RM";
			}
			if (CMCheckersBoard[ind1][ind2] == 6)
			{
				DisplayChecker[ind1][ind2] = "RK";
			}
			cout << fixed << setw(4) << DisplayChecker[ind1][ind2];
		}
		cout << endl;
	}
}
//This functions counts the number of checkers that have an available jump, by calling another function
//isJump
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int jumpCount = 0;
	int ind1 = 0;
	int x = 0;
	int y = 0;
	int xIndex = 0;
	int yIndex = 0;
	for (ind1 = 0; ind1 < MAX_PIECES; ind1++) //initialization of arrays
	{
		xLocArray[ind1] = -1;
		yLocArray[ind1] = -1;
	}
	if (player == 1)
	{
		for (yIndex = 0; yIndex < numRowsInBoard; yIndex++)
		{
			for (xIndex = 0; xIndex < numRowsInBoard; xIndex++)
			{
				if (CMCheckersBoard[yIndex][xIndex] == 1 || CMCheckersBoard[yIndex][xIndex] == 2 || CMCheckersBoard[yIndex][xIndex] == 3)
				{
					if ((IsJump(CMCheckersBoard, numRowsInBoard, player, xIndex, yIndex)) == true)
					{
						jumpCount++;
						xLocArray[x] = xIndex;
						x++;
						yLocArray[y] = yIndex;
						y++;
					}
				}
			}
		}
	}
	else if (player == 2)
	{
		for (yIndex = 0; yIndex < numRowsInBoard; yIndex++)
		{
			for (xIndex = 0; xIndex < numRowsInBoard; xIndex++)
			{
				if (CMCheckersBoard[yIndex][xIndex] == 4 || CMCheckersBoard[yIndex][xIndex] == 5 || CMCheckersBoard[yIndex][xIndex] == 6)
				{
					if ((IsJump(CMCheckersBoard, numRowsInBoard, player, xIndex, yIndex)) == true)
					{
						jumpCount++;
						xLocArray[x] = xIndex;
						x++;
						yLocArray[y] = yIndex;
						y++;
					}
				}
			}
		}
	}
	return jumpCount;
}

//This function counts the number of checkers that can move one square, by calling another function,
//isMoveSquare
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int moveCount = 0;
	int ind = 0;
	int yIndex = 0;
	int xIndex = 0;
	int x = 0;
	int y = 0;
	for (ind = 0; ind < MAX_PIECES; ind++)
	{
		xLocArray[ind] = -1;
		yLocArray[ind] = -1;
	}
	//
	if (player == 1)
	{
		for (yIndex = 0; yIndex < numRowsInBoard; yIndex++)
		{
			for (xIndex = 0; xIndex < numRowsInBoard; xIndex++)
			{
				if (CMCheckersBoard[yIndex][xIndex] == WHITESOLDIER || CMCheckersBoard[yIndex][xIndex] == WHITEMULE || CMCheckersBoard[yIndex][xIndex] == WHITEKING)
				{
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xIndex, yIndex) == 1)
					{
						moveCount++;
						xLocArray[x] = xIndex;
						x++;
						yLocArray[y] = yIndex;
						y++;
					}
				}
			}
		}
	}
	if (player == 2)
	{
		for (yIndex = 0; yIndex < numRowsInBoard; yIndex++)
		{
			for (xIndex = 0; xIndex < numRowsInBoard; xIndex++)
			{
				if (CMCheckersBoard[yIndex][xIndex] == REDSOLDIER || CMCheckersBoard[yIndex][xIndex] == REDMULE || CMCheckersBoard[yIndex][xIndex] == REDKING)
				{
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xIndex, yIndex) == 1)
					{
						moveCount++;
						xLocArray[x] = xIndex;
						x++;
						yLocArray[y] = yIndex;
						y++;
					}
				}
			}
		}
	}
	return moveCount;
}

//This function checks to see if a jump is available
//If it is available, then it return true to increment the number of jumps available
bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == 1)
	{
		//If the player is a whitepiece, it will check to see if the piece has any jumps available
		if ((yLoc != (numRowsInBoard - 2)) && (yLoc != (numRowsInBoard - 1)))
			if (CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITEKING)
			{
				if (xLoc == 0)
				{
					if (((CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING))
						&& (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDMULE) || (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDKING))
						&& (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0))
					{
						return true;
					}
				}
				else if (xLoc == 1)
				{
					if (((CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING))
						&& (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc + 1][0] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][0] == REDMULE) || (CMCheckersBoard[yLoc + 1][0] == REDKING))
						&& (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0))
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 2)
				{
					if (((CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING))
						&& (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDMULE) || (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDKING))
						&& (CMCheckersBoard[yLoc + 2][0] == 0))
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 1)
				{
					if (((CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING))
						&& (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc + 1][0] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][0] == REDMULE) || (CMCheckersBoard[yLoc + 1][0] == REDKING))
						&& (CMCheckersBoard[yLoc + 2][1] == 0))
					{
						return true;
					}
				}
				else if (((CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING))
					&& (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0))
				{
					return true;
				}
				else if (((CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING))
					&& (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0))
				{
					return true;
				}
			}
		//if ((yLoc != 0 && yLoc != 1)
		{
			if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
			{
				if (xLoc == 0)
				{
					if (((CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDMULE) || (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDKING))
						&& (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING))
						&& (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0))
					{
						return true;
					}
				}
				else if (xLoc == 1)
				{
					if (((CMCheckersBoard[yLoc - 1][0] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][0] == REDMULE) || (CMCheckersBoard[yLoc - 1][0] == REDKING))
						&& (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING))
						&& (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0))
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 2)
				{
					if (((CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDMULE) || (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDKING))
						&& (CMCheckersBoard[yLoc - 2][0] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING))
						&& (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0))
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 1)
				{
					if (((CMCheckersBoard[yLoc - 1][0] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][0] == REDMULE) || (CMCheckersBoard[yLoc - 1][0] == REDKING))
						&& (CMCheckersBoard[yLoc - 2][1] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING))
						&& (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0))
					{
						return true;
					}
				}
				else if (((CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING))
					&& (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0))
				{
					return true;
				}
				else if (((CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING))
					&& (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0))
				{
					return true;
				}
			}
		}
		return false;
	}

	//==================================================================================================================================================================================================================================================
	if (player == 2)
	{
		//If the player is a red piece, it will check to see if any of its checkers has an available jump
		if ((yLoc != (0)) && (yLoc != (1)))
			if (CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDKING)
			{
				if (xLoc == 0)
				{
					if (((CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0))
					{
						return true;
					}
				}
				else if (xLoc == 1)
				{
					if (((CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc - 1][0] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][0] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][0] == WHITEKING))
						&& (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0))
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 2)
				{
					if (((CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc - 2][0] == 0))
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 1)
				{
					if (((CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc - 1][0] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][0] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][0] == WHITEKING))
						&& (CMCheckersBoard[yLoc - 2][1] == 0))
					{
						return true;
					}
				}
				else if (((CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING))
					&& (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0))
				{
					return true;
				}
				else if (((CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE) || (CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING))
					&& (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0))
				{
					return true;
				}
			}
		if ((yLoc != numRowsInBoard - 1 && yLoc != numRowsInBoard - 2))
		{
			//Checks to see if the King can move backwards
			if (CMCheckersBoard[yLoc][xLoc] == REDKING) //King
			{
				if (xLoc == 0)
				{
					if (((CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0))
					{
						return true;
					}
				}
				else if (xLoc == 1)
				{
					if (((CMCheckersBoard[yLoc + 1][0] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][0] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][0] == WHITEKING))
						&& (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0))
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 2)
				{
					if (((CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc + 2][0] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0))
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 1)
				{
					if (((CMCheckersBoard[yLoc + 1][0] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][0] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][0] == WHITEKING))
						&& (CMCheckersBoard[yLoc + 2][1] == 0))
					{
						return true;
					}
					else if (((CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING))
						&& (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0))
					{
						return true;
					}
				}
				else if (((CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING))
					&& (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0))
				{
					return true;
				}
				else if (((CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE) || (CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING))
					&& (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0))
				{
					return true;
				}
			}
		}
		return false;
	}
}

//This function checks to see if the square selected has any moves available.
//If no movements for this square is available, it will return a value of false to the function that called it,
//In this case countMoves
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	//=========================================================================================================================================================================================================
	if (player == 1)
	{
		//Checks all possible spaces around it to see if it can make a legal move
		if (yLoc != (numRowsInBoard - 1))
		{
			if (CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITEKING)
			{
				if (xLoc == 0)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 0)
					{
						return true;
					}
				}
				else if (xLoc == 1)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][0] == 0)
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 2)
				{
					if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 1)
				{
					if (CMCheckersBoard[yLoc + 1][0] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
				{
					return true;
				}
			}
		}
		//Checks if the king can move backwards
		if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
		{
			if (xLoc == 0)
			{
				if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
				{
					return true;
				}
			}
			else if (xLoc == 1)
			{
				if (CMCheckersBoard[yLoc - 1][0] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
				{
					return true;
				}
			}
			else if (xLoc == numRowsInBoard - 2)
			{
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 0)
				{
					return true;
				}
			}
			else if (xLoc == numRowsInBoard - 1)
			{
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][0] == 0)
				{
					return true;
				}
			}
			else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
			{
				return true;
			}
		}
		return false;
	}
	//=============================================================================================================================================================================================================
	if (player == 2)
	{
		//Checks to see if any of the squares can make a move
		if (yLoc != (0))
		{
			if (CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDKING)
			{
				if (xLoc == 0)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 0)
					{
						return true;
					}
				}
				else if (xLoc == 1)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][0] == 0)
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 2)
				{
					if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
					{
						return true;
					}
				}
				else if (xLoc == numRowsInBoard - 1)
				{
					if (CMCheckersBoard[yLoc - 1][0] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
					{
						return true;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
				{
					return true;
				}
			}
		}
		//Checks to see if the king can move backwards
		if (CMCheckersBoard[yLoc][xLoc] == REDKING)
		{
			if (xLoc == 0)
			{
				if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
				{
					return true;
				}
			}
			else if (xLoc == 1)
			{
				if (CMCheckersBoard[yLoc + 1][0] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
				{
					return true;
				}
			}
			else if (xLoc == numRowsInBoard - 2)
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 0)
				{
					return true;
				}
			}
			else if (xLoc == numRowsInBoard - 1)
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[yLoc + 1][0] == 0)
				{
					return true;
				}
			}
			else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
			{
				return true;
			}
			else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
			{
				return true;
			}
		}
		return false;
	}
}

//This function actually moves the pieces you selected, under a set of conditions
//If the conditions are not met, then the function will return false and an error will prompt asking you to re-enter values.
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
{
	int xDistance = 0;
	int yDistance = 0;
	int fromXPosition = 0;
	int fromYPosition = 0;
	int toXPosition = 0;
	int toYPosition = 0;
	int temp = 0;
	char gameEnd;
	jumped = false;
	if (fromSquareNum / numRowsInBoard == 0)
	{
		fromXPosition = fromSquareNum;
	}
	else
	{
		fromXPosition = fromSquareNum % numRowsInBoard;
	}
	fromYPosition = fromSquareNum / numRowsInBoard;
	if (toSquareNum / numRowsInBoard == 0)
	{
		toXPosition = toSquareNum;
	}
	else
	{
		toXPosition = toSquareNum % numRowsInBoard;
	}
	toYPosition = toSquareNum / numRowsInBoard;
	xDistance = abs(toXPosition - fromXPosition);
	yDistance = abs(toYPosition - fromYPosition);
	if (fromYPosition == toYPosition)
	{
		cerr << "ERROR: Moving to that square is not legal, Try again." << endl;
		jumped = false;
		return false;
	}
	if (fromXPosition == toXPosition)
	{
		cerr << "ERROR: Moving to that square is not legal, Try again." << endl;
		jumped = false;
		return false;
	}


	//==================================================================================================================================================================================================================================
	if (player == 1)
	{
		//If the checker selected is a white piece, then we will move this piece
		if ((CMCheckersBoard[fromYPosition][fromXPosition] == WHITESOLDIER) || (CMCheckersBoard[fromYPosition][fromXPosition] == WHITEMULE) || (CMCheckersBoard[fromYPosition][fromXPosition] == WHITEKING))
		{
			//If the square selected to move to is greater than two squares away, then an error will prompt asking to re-enter a value
			if (xDistance > 2 && yDistance > 2)
			{
				cerr << "ERROR: Moving to that square is not legal, Try again." << endl;
				return false;
			}
			if ((CMCheckersBoard[fromYPosition][fromXPosition] == WHITESOLDIER) || (CMCheckersBoard[fromYPosition][fromXPosition] == WHITEMULE))
			{
				if (toSquareNum < fromSquareNum)
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			//If the square selected is going down the board, then the following occurs:
			if (toSquareNum > fromSquareNum)
			{
				//If the square selected to move is in the first, second, second to last, or last column, and there is a white piece in between, then an error will prompt
				//And the player will be asked to to re-enter a value
				//Otherwise, it will swap values
				if (fromXPosition == 1)
				{
					if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] != REDMULE) && (CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][0] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
							{
								CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
							{
								cout << "White has created a Mule King, Red wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(12);
								}
							}
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == numRowsInBoard - 2)
				{
					if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] != REDMULE) && (CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
							{
								CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
							{
								cout << "White has created a Mule King, Red wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(13);
								}
							}
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == 0)
				{
					if ((xDistance == numRowsInBoard - 1) && (yDistance == 1))
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
						{
							CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
							jumped = true;
							return true;
						}
						else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
						{
							cout << "White has created a Mule King, Red wins the game" << endl;
							cout << "Enter any character to terminate the game then press the enter key" << endl;
							if (cin >> gameEnd)
							{
								exit(14);
							}
						}
						jumped = true;
						return true;
					}
					else if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] != REDMULE) && (CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
							{
								CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
							{
								cout << "White has created a Mule King, Red wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(15);
								}
							}
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == numRowsInBoard - 1)
				{
					if ((xDistance == numRowsInBoard - 1) && (yDistance == 1))
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
						{
							CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
							jumped = true;
							return true;
						}
						else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
						{
							cout << "White has created a Mule King, Red wins the game" << endl;
							cout << "Enter any character to terminate the game then press the enter key" << endl;
							if (cin >> gameEnd)
							{
								exit(16);
							}
						}
						jumped = true;
						return true;
					}
					else if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition + 1][0] != REDSOLDIER) && (CMCheckersBoard[fromYPosition + 1][0] != REDMULE) && (CMCheckersBoard[fromYPosition + 1][0] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][0] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
							{
								CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
							{
								cout << "White has created a Mule King, Red wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(17);
								}
							}
							jumped = true;
							return true;
						}
					}
				}
			}
			//If the square selected is not in the first two or last two columns, and there is no white piece in between the two squares for moving two squares,
			//Then it will swap values
			if (xDistance == 1 && yDistance == 1)
			{
				temp = CMCheckersBoard[fromYPosition][fromXPosition];
				CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
				CMCheckersBoard[toYPosition][toXPosition] = temp;
				if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
				{
					CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
					jumped = true;
					return true;
				}
				else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
				{
					cout << "White has created a Mule King, Red wins the game" << endl;
					cout << "Enter any character to terminate the game then press the enter key" << endl;
					if (cin >> gameEnd)
					{
						exit(1);
					}
				}
				jumped = true;
				return true;
			}
			else if (xDistance == 2 && yDistance == 2)
			{
				if (toSquareNum > fromSquareNum)
				{
					if (toSquareNum < fromSquareNum + (2 * numRowsInBoard))
					{
						if ((CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] != REDMULE) && (CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
							{
								CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
							{
								cout << "White has created a Mule King, Red wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(1);
								}
							}
							jumped = true;
							return true;
						}
					}
					else if (toSquareNum > fromSquareNum + (2 * numRowsInBoard))
					{
						if ((CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] != REDMULE) && (CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == WHITESOLDIER) && (toYPosition == numRowsInBoard - 1))
							{
								CMCheckersBoard[toYPosition][toXPosition] = WHITEKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == WHITEMULE) && (toYPosition == numRowsInBoard - 1))
							{
								cout << "White has created a Mule King, Red wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(2);
								}
							}
							jumped = true;
							return true;
						}
					}
				}
			}
		}
		//This allows the king to move backwards
		if ((CMCheckersBoard[fromYPosition][fromXPosition] == WHITEKING))
		{
			{
				//If the square selected to jump to is greater than two squares, an error will reprompt, asking to re-enter a value
				if (xDistance > 2 && yDistance > 2)
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
				//If the square selected to jump is in the first, second, second to last, or last column, and there is a red piece in between, an error will prompt, asking to re-enter a value
				//Otherwise, it will swap the values
				if (fromXPosition == 1)
				{
					if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][0] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == numRowsInBoard - 2)
				{
					if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != REDMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][numRowsInBoard - 1] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == 0)
				{
					if ((xDistance == numRowsInBoard - 1) && (yDistance == 1))
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						jumped = true;
						return true;
					}
					else if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][numRowsInBoard - 1] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == numRowsInBoard - 1)
				{
					if ((xDistance == numRowsInBoard - 1) && (yDistance == 1))
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						jumped = true;
						return true;
					}
					else if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition - 1][0] != REDSOLDIER) && (CMCheckersBoard[fromYPosition - 1][0] != REDMULE) && (CMCheckersBoard[fromYPosition - 1][0] != REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][0] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
			}
			//However, if the square selected is not in the first two and last two columns, and there is a no white soldier in between the two squares for the move two spaces,
			//It will swap values
			if (xDistance == 1 && yDistance == 1)
			{
				temp = CMCheckersBoard[fromYPosition][fromXPosition];
				CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
				CMCheckersBoard[toYPosition][toXPosition] = temp;
				jumped = true;
				return true;
			}
			else if (xDistance == 2 && yDistance == 2)
			{
				if (toSquareNum < fromSquareNum - (2 * numRowsInBoard))
				{
					if ((CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != REDKING))
					{
						cerr << "Error;  illegal move" << endl;
						return false;
					}
					else
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] = NOPLAYER;
						jumped = true;
						return true;
					}
				}
				else if (toSquareNum > fromSquareNum - (2 * numRowsInBoard))
				{
					if ((CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != REDSOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != REDMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != REDKING))
					{
						cerr << "Error;  illegal move" << endl;
						return false;
					}
					else
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] = NOPLAYER;
						jumped = true;
						return true;
					}
				}
			}
		}
	}

	//=======================================================================================================================================================================================================================//
	if (player == 2)
	{
		//If the square selected was farther than 2 squares diagonally away, an error will prompt
		if ((CMCheckersBoard[fromYPosition][fromXPosition] == REDSOLDIER) || (CMCheckersBoard[fromYPosition][fromXPosition] == REDMULE) || (CMCheckersBoard[fromYPosition][fromXPosition] == REDKING))
		{
			if (xDistance > 2 && yDistance > 2)
			{
				cerr << "Error;  illegal move" << endl;
				return false;
			}
			if ((CMCheckersBoard[fromYPosition][fromXPosition] == REDSOLDIER) || (CMCheckersBoard[fromYPosition][fromXPosition] == REDMULE))
			{
				if (toSquareNum > fromSquareNum)
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			//If the toSquare selected was going in the forward direction, the following code will prompt
			//If the square selected to move was in the first, second, second to last, or last column, and the square in between is a red piece, an error will prompt
			//Otherwise it will swap squares
			if (toSquareNum < fromSquareNum)
			{
				if (fromXPosition == 1)
				{
					if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITESOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITEMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITEKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][0] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
							{
								CMCheckersBoard[toYPosition][toXPosition] = REDKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
							{
								cout << "Red has created a Mule King, White wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(3);
								}
							}
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == numRowsInBoard - 2)
				{
					if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != WHITESOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != WHITEMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != WHITEKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromXPosition][fromYPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][numRowsInBoard - 1] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
							{
								CMCheckersBoard[toYPosition][toXPosition] = REDKING;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
							{
								cout << "Red has created a Mule King, White wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(4);
								}
							}
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == 0)
				{
					if ((xDistance == numRowsInBoard - 1) && (yDistance == 1))
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
						{
							CMCheckersBoard[toYPosition][toXPosition] = REDKING;
							jumped = true;
							return true;
						}
						else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
						{
							cout << "Red has created a Mule King, White wins the game" << endl;
							cout << "Enter any character to terminate the game then press the enter key" << endl;
							if (cin >> gameEnd)
							{
								exit(5);
							}
						}
						jumped = true;
						return true;
					}
					else if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITESOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITEMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITEKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][numRowsInBoard - 1] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
							{
								CMCheckersBoard[toYPosition][toXPosition] = REDKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
							{
								cout << "Red has created a Mule King, White wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(6);
								}
							}
							jumped = true;
							return true;
						}
					}
				}
				else if (fromXPosition == numRowsInBoard - 1)
				{
					if ((xDistance == numRowsInBoard - 1) && (yDistance == 1))
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
						{
							CMCheckersBoard[toYPosition][toXPosition] = REDKING;
							jumped = true;
							return true;
						}
						else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
						{
							cout << "Red has created a Mule King, White wins the game" << endl;
							cout << "Enter any character to terminate the game then press the enter key" << endl;
							if (cin >> gameEnd)
							{
								exit(7);
							}
						}
						jumped = true;
						return true;
					}
					else if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if (toSquareNum < fromSquareNum)
						{
							if ((CMCheckersBoard[fromYPosition - 1][0] != WHITESOLDIER) && (CMCheckersBoard[fromYPosition - 1][0] != WHITEMULE) && (CMCheckersBoard[fromYPosition - 1][0] != WHITEKING))
							{
								cerr << "Error;  illegal move" << endl;
								return false;
							}
							else
							{
								temp = CMCheckersBoard[fromYPosition][fromXPosition];
								CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
								CMCheckersBoard[toYPosition][toXPosition] = temp;
								CMCheckersBoard[fromYPosition - 1][0] = NOPLAYER;
								jumped = true;
								if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
								{
									CMCheckersBoard[toYPosition][toXPosition] = REDKING;
									jumped = true;
									return true;
								}
								else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
								{
									cout << "Red has created a Mule King, White wins the game" << endl;
									cout << "Enter any character to terminate the game then press the enter key" << endl;
									if (cin >> gameEnd)
									{
										exit(8);
									}
								}
								jumped = true;
								return true;
							}
						}
					}
				}
			}
			//However, if the square is not in the first two and last two columns, and there is a player that can be jumped for moving two squares,
			//The values will swap
			if (xDistance == 1 && yDistance == 1)
			{
				temp = CMCheckersBoard[fromYPosition][fromXPosition];
				CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
				CMCheckersBoard[toYPosition][toXPosition] = temp;
				if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
				{
					CMCheckersBoard[toYPosition][toXPosition] = REDKING;
					jumped = true;
					return true;
				}
				else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
				{
					cout << "Red has created a Mule King, White wins the game" << endl;
					cout << "Enter any character to terminate the game then press the enter key" << endl;
					if (cin >> gameEnd)
					{
						exit(9);
					}
				}
				jumped = true;
				return true;
			}
			else if (xDistance == 2 && yDistance == 2)
			{
				if (toSquareNum < fromSquareNum)
				{
					if (toSquareNum < fromSquareNum - (2 * numRowsInBoard))
					{
						if ((CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITESOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITEMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] != WHITEKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][fromXPosition - 1] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
							{
								CMCheckersBoard[toYPosition][toXPosition] = REDKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
							{
								cout << "Red has created a Mule King, White wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(10);
								}
							}
							jumped = true;
							return true;
						}
					}
					else if (toSquareNum > fromSquareNum - (2 * numRowsInBoard))
					{
						if ((CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != WHITESOLDIER) && (CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != WHITEMULE) && (CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] != WHITEKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition - 1][fromXPosition + 1] = NOPLAYER;
							jumped = true;
							if ((CMCheckersBoard[toYPosition][toXPosition] == REDSOLDIER) && (toYPosition == 0))
							{
								CMCheckersBoard[toYPosition][toXPosition] = REDKING;
								jumped = true;
								return true;
							}
							else if ((CMCheckersBoard[toYPosition][toXPosition] == REDMULE) && (toYPosition == 0))
							{
								cout << "Red has created a Mule King, White wins the game" << endl;
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								if (cin >> gameEnd)
								{
									exit(11);
								}
							}
							return true;
						}
					}

				}
			}
		}
		//If the checker piece selected was a king, then this allows the king to move backwards
		if ((CMCheckersBoard[fromYPosition][fromXPosition] == REDKING))
		{
			{
				//If the player selected a square that is greater than 2 squares away, an error will prompt, asking to re-enter the value
				if (xDistance > 2 && yDistance > 2)
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
				//If the King is in the second column
				if (fromXPosition == 1)
				{
					//And it is trying to move across the board and there is another red piece in between, an error will prompt, asking to re-enter the value
					//Otherwise, it will swap the values
					if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] == REDSOLDIER) || (CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] == REDMULE) || (CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] == REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][0] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
				//If the king is in the second to last column
				else if (fromXPosition == numRowsInBoard - 2)
				{
					//And it is trying to move across the board and there is another red piece in between, an error will prompt, asking to re-enter the value
					//Otherwise, it will swap the values
					if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] == REDSOLDIER) || (CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] == REDMULE) || (CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] == REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
				//If the king is in the first column 
				else if (fromXPosition == 0)
				{
					//And it is trying to move across the board and there is another red piece in between, an error will prompt, asking to re-enter the value
					//Otherwise, it will swap the values
					if ((xDistance == numRowsInBoard - 1) && (yDistance == 1))
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						jumped = true;
						return true;
					}
					else if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] == REDSOLDIER) || (CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] == REDMULE) || (CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] == REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][numRowsInBoard - 1] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
				//If the King is in the last column
				else if (fromXPosition == numRowsInBoard - 1)
				{
					//And it is trying to move across the board and there is another red piece in between, an error will prompt, asking to re-enter the value
					//Otherwise, it will swap the values
					if ((xDistance == numRowsInBoard - 1) && (yDistance == 1))
					{
						temp = CMCheckersBoard[fromYPosition][fromXPosition];
						CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
						CMCheckersBoard[toYPosition][toXPosition] = temp;
						jumped = true;
						return true;
					}
					else if ((xDistance == numRowsInBoard - 2) && (yDistance == 2))
					{
						if ((CMCheckersBoard[fromYPosition + 1][0] == REDSOLDIER) || (CMCheckersBoard[fromYPosition + 1][0] == REDMULE) || (CMCheckersBoard[fromYPosition + 1][0] == REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][0] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
				//However, if it is just moving by one square and is not the two border edges, it will swap values
				if (xDistance == 1 && yDistance == 1)
				{
					temp = CMCheckersBoard[fromYPosition][fromXPosition];
					CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
					CMCheckersBoard[toYPosition][toXPosition] = temp;
					return true;
				}
				//However, if it is moving by two squares and is not the two border edges, it will swap values
				else if (xDistance == 2 && yDistance == 2)
				{
					if (toSquareNum < fromSquareNum + (2 * numRowsInBoard))
					{
						if ((CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] == REDSOLDIER) || (CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] == REDMULE) || (CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] == REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][fromXPosition - 1] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
					else if (toSquareNum > fromSquareNum - (2 * numRowsInBoard))
					{
						if ((CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] == REDSOLDIER) || (CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] == REDMULE) || (CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] == REDKING))
						{
							cerr << "Error;  illegal move" << endl;
							return false;
						}
						else
						{
							temp = CMCheckersBoard[fromYPosition][fromXPosition];
							CMCheckersBoard[fromYPosition][fromXPosition] = NOPLAYER;
							CMCheckersBoard[toYPosition][toXPosition] = temp;
							CMCheckersBoard[fromYPosition + 1][fromXPosition + 1] = NOPLAYER;
							jumped = true;
							return true;
						}
					}
				}
			}
		}
	}
}

//This function is used at the end of every turn to check for the following win conditions
//If the win conditions are met, this function will return true and the game will terminate
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int ind1 = 0;
	int ind2 = 0;
	int WHITESOLDIERcounter = 0;
	int WHITEMULEcounter = 0;
	int WHITEKINGcounter = 0;
	int REDSOLDIERcounter = 0;
	int REDMULEcounter = 0;
	int REDKINGcounter = 0;
	for (ind1 = 0; ind1 < numRowsInBoard; ind1++)
	{
		for (ind2 = 0; ind2 < numRowsInBoard; ind2++)
		{
			if (CMCheckersBoard[ind1][ind2] == WHITESOLDIER)
			{
				WHITESOLDIERcounter++;
			}
			else if (CMCheckersBoard[ind1][ind2] == WHITEMULE)
			{
				WHITEMULEcounter++;
			}
			else if (CMCheckersBoard[ind1][ind2] == WHITEKING)
			{
				WHITEKINGcounter++;
			}
			else if (CMCheckersBoard[ind1][ind2] == REDSOLDIER)
			{
				REDSOLDIERcounter++;
			}
			else if (CMCheckersBoard[ind1][ind2] == REDMULE)
			{
				REDMULEcounter++;
			}
			else if (CMCheckersBoard[ind1][ind2] == REDKING)
			{
				REDKINGcounter++;
			}
		}
	}
	if (REDMULEcounter == 0)
	{
		cout << "The Red Player has won the game by losing all of the Red Mules" << endl;
		return true;
	}
	else if (WHITEMULEcounter == 0)
	{
		cout << "The White Player has won the game by losing all of the White Mules" << endl;
		return true;
	}
	else if (REDSOLDIERcounter == 0 && REDKINGcounter == 0)
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings" << endl;
		return true;
	}
	else if (WHITESOLDIERcounter == 0 && WHITEKINGcounter == 0)
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

//This function is used to double check and make sure that all of the values that can jump or move are in their respectable arrays
bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex)
{
	int checkcount = 0;

	for (checkcount = 0; checkcount < MAX_ARRAY_SIZE; checkcount++)
	{
		if (inArray1[checkcount] == xIndex && inArray2[checkcount] == yIndex)
		{
			return true;
		}
		return false;

	}
}

//This function is used to to extract the coordinates of a square and returns it into the respectable number on the display board
int ConvertToNum(int xLocation, int yLocation, int numRowsInBoard)
{
	int number;
	number = (numRowsInBoard * yLocation) + xLocation;

	return number;
}

//This function is used to extract the number of a square from the display board and returns its coordinates
void ConvertToXY(int number, int &xLocation, int &yLocation, int numRowsInBoard)
{
	if (number / numRowsInBoard == 0)
	{
		xLocation = number;
	}
	else
	{
		xLocation = number % numRowsInBoard;
	}
	yLocation = number / numRowsInBoard;
}
