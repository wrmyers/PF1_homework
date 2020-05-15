#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>   // for bonus
using namespace std;

const int SIZE = 12; // size of the 2-d game board
const int EXIT_ROW = 6; // row index of the exit space
const int EXIT_COL = 11; // column index of the exit space
const string SAVE_FILE = "save.txt";  // only needed by bonus

//
// FUNCTION NAME: INTRO
// RETURNS: VOID
// PARAMETERS: NONE
// PRINTS THE GAME INSTRUCTIONS TO THE SCREEN.
//
void intro()
{
   cout <<"Welcome to PRISON BREAK\n";
   cout <<"Written by:  Weston Myers\n";
   cout << "Your goal is to reach the exit before the police catch you!\n";
   cout << "Your avatar (u) and the police (p) alternate moves\n";
   cout << "You are caught when you and the police are on the same board spot. \nIf you are ever beside the police officer when their move starts, you will be caught\n";
}

//
// FUNCTION NAME: saveGame bonus
// RETURNS: VOID
// PARAMETERS: POLICE'S POSITION (row and col), YOUR POSITION (row and col)
// SETS THE PLAYER'S POSITION AND THE POLICE'S POSITION TO
// VALUES STORED IN A SAVE FILE.
void saveGame(const int police_row,const int police_col,const int your_row,const int your_col)
{
    ofstream outfile;
    outfile.open("hw5_load.txt");
    outfile << police_row << " " << police_col << " " << your_row << " " << your_col;
    outfile.close();
}
//
// FUNCTION NAME: loadSavedGame bonus
// RETURNS: VOID
// PARAMETERS: POLICE'S POSITION (row and col), YOUR POSITION (row and col)
// SETS THE PLAYER'S POSITION AND THE POLICE'S POSITION TO
// VALUES STORED IN A SAVE FILE.
// IF THE FILE CANNOT BE OPENED, sets the police at 1, 1, and the user
// at 5, 5
void loadSavedGame(int &police_row,int &police_col,int &your_row,int &your_col)
{
    ifstream infile;
    infile.open("hw5_load.txt");
    if (infile.fail())
    {
        police_row=1;
        police_col=1;
        your_row=5;
        your_col=5;
    }
    infile >> police_row >> police_col >> your_row >> your_col ;

}

//FUNCTION NAME: CHECK_QUIT
//RETURNS: BOOLEAN
//PARAMETERS: NONE
bool check_quit (const int police_row,const int police_col,const int your_row,const int your_col)
{
    bool quit;
    cout << "Would you like to save? (Y/N)" << endl;
    char variable;
    cin >> variable;
    variable = toupper(variable);
    while (variable != 'Y' && variable != 'N')
    {
        cout << "Invalid input. Would you like to save? (Y/N)" << endl;
        cin >> variable;
        variable = toupper(variable);
    }
    if (variable == 'Y')
    {
        saveGame (police_row, police_col, your_row, your_col);
        quit = true;
    }
    else
        quit = false;

    return quit;
}
//
// FUNCTION NAME: startNewGame
// RETURNS: VOID
// PARAMETERS: THE PLAYING BOARD (const 2D array of characters)
//    POLICE'S POSITION (row and col), YOUR POSITION (row and col)
// SETS THE PLAYER'S POSITION AND THE POLICE'S POSITION TO RANDOM SPOTS
// ON THE BOARD AND ALL OTHER SPOTS TO A PLACEHOLDER.
// IF THE SPOT IS ALREADY OCCUPIED, TRY ANOTHER RANDOM LOCATION
//

void startNewGame (const char board[SIZE][SIZE], int &p_row, int &p_col, int &y_row, int &y_col)
{
   board[SIZE][SIZE] == '-';
   // set police location randomly
   p_row = rand() %12;
   p_col = rand() %12;
   board[p_row][p_col] == 'p';
   // set your location randomly
   y_row = rand() %12;
   y_col = rand() %12;
   board[y_row][y_col] == 'u';
   while (y_row == p_row && y_col == p_col)
   {
       board[p_row][p_col] == '-';
       p_row = rand() %12;
       p_col = rand() %12;
       board[p_row][p_col] == 'p';
   }
   while (y_row == EXIT_ROW && y_col == EXIT_COL)
   {
       board[y_row][y_col] == '-';
       y_row = rand() %12;
       y_col = rand() %12;
       board[y_row][y_col] == 'u';
   }
   while (p_row == EXIT_ROW && p_col == EXIT_COL)
   {
       board[p_row][p_col] == '-';
       p_row = rand() %12;
       p_col = rand() %12;
       board[p_row][p_col] == 'p';
   }
}

//
// FUNCTION NAME: POPULATE
// RETURNS: VOID
// PARAMETERS: GAME BOARD, PLAYER'S POSITION, POLICE'S POSITION
// SETS THE PLAYER'S POSITION AND THE POLICE'S POSITION TO RANDOM SPOTS ON THE BOARD AND ALL OTHER SPOTS TO A PLACEHOLDER.
//
void populate(char board[SIZE][SIZE], int &your_row, int &your_col, int &police_row, int &police_col)
{
char loadGame;

    // initialize the board to all '-'
    for(int row=0;row<SIZE;row++) {
        for(int col=0;col<SIZE;col++) {
            board[row][col] = '-';
        }
    }


    // do they want to load the game from a file
    cout << "Do you want to load a saved game?  Enter Y or N: ";
    cin >> loadGame;
    while (loadGame != 'y' && loadGame != 'Y' && loadGame != 'n' && loadGame != 'N')
    {
       cout << "Invalid input.  Do you want to load a saved game?  Enter Y or N: ";
       cin >> loadGame;
    }

    // for bonus only
    if (loadGame == 'Y' || loadGame == 'y')
       loadSavedGame (police_row, police_col, your_row, your_col);
    else

       startNewGame (board, police_row, police_col, your_row, your_col);

    // update the board with the 'e', 'p', and 'u'
    board[EXIT_ROW][EXIT_COL] = 'e';
    board[your_row][your_col] = 'u';
    board[police_row][police_col] = 'p';
}

//
// FUNCTION NAME: PRINT_BOARD
// RETURNS: VOID
// PARAMETERS: BOARD
// PRINTS EACH BOARD SPACE TO THE SCREEN.
//
void print_board(char board[SIZE][SIZE])
{
    cout << "               PRISON   BREAK      " << endl;
    cout << "      0  1  2  3  4  5  6  7  8  9 10 11\n";
    for(int row=0;row<SIZE;row++)
    {
        cout << setw(3) << row << " | ";
        for(int col=0;col<SIZE;col++)
        {
           cout << board[row][col] << "  ";
        }
        cout << "|";
        cout << endl;
   }
}

//
// FUNCTION NAME: VERIFY_DIRECTION
// RETURNS: VOID
// PARAMETERS: DIRECTION AS A CHARACTER (WASD)
// VERIFIES THAT THE USER-ENTERED VALUE IS W,A,S, OR D
// IF IT WAS NOT, LOOPS ASKING USER FOR VALID VALUE UNTIL
// VALID VALUE IS ENTERED; UPDATES PARAMETER WITH THE
// NEW VALID VALUE
//
void verify_direction(char &direction)
{

    if (direction != 'W' && direction != 'A' && direction != 'S' && direction != 'D')
    {
        cout << "Please enter a valid value." << endl;
            cin >> direction;

         while (direction != 'W' && direction != 'A' && direction != 'S' && direction != 'D');
        {
            cout << "Please enter a valid value." << endl;
            cin >> direction;
            direction = toupper(direction);
        }

    }
}
//
// FUNCTION NAME: MOVE_UP
// RETURNS: BOOLEAN - MOVE WAS COMPLETED OR IMPOSSIBLE
// PARAMETERS: BOARD, AVATAR'S POSITION (row and column), AVATAR CHARACTER TO MOVE (police or yourself)
// MOVES THE GIVEN AVATAR UP ON THE BOARD BY 1 SPACE IF POSSIBLE.
//
bool move_up(char board[SIZE][SIZE], int &row, int &col, const char avatar)
{
    bool success;
    int place;
    place = row -1;
    if (place < 0)
        success = false;
    else
    {
    success = true;
    board[place][col] = avatar;
    board[row][col] = '-';
    row = place;
    }


    return success;


}

//
// FUNCTION NAME: MOVE_DOWN
// RETURNS: BOOLEAN - MOVE WAS COMPLETED OR IMPOSSIBLE
// PARAMETERS: BOARD, AVATAR'S POSITION (row and column), AVATAR CHARACTER TO MOVE
// MOVES THE GIVEN AVATAR DOWN ON THE BOARD BY 1 SPACE.
//
bool move_down(char board[SIZE][SIZE], int &row, int &col, const char avatar)
{
    bool success;
    int place;
    place = row +1;
    if (place > 11)
        success = false;
    else
    {
    success = true;
    board[place][col] = avatar;
    board[row][col]= '-';
    row = place;
    }


    return success;
}
//
// FUNCTION NAME: MOVE_LEFT
// RETURNS: BOOLEAN - MOVE WAS COMPLETED OR IMPOSSIBLE
// PARAMETERS: BOARD, AVATAR'S POSITION (row and column), AVATAR CHARACTER TO MOVE
// MOVES THE GIVEN AVATAR LEFT ON THE BOARD BY 1 SPACE.
//
bool move_left(char board[SIZE][SIZE], int &row, int &col, const char avatar)
{
    bool success;
    int place;
    place = col -1;
    if (place < 0)
        success = false;
    else
    {
    success = true;

    board[row][place] = avatar;
    board[row][col] = '-';
    col = col -1;
    }


    return success;
}
//
// FUNCTION NAME: MOVE_RIGHT
// RETURNS: BOOLEAN - MOVE WAS COMPLETED OR IMPOSSIBLE
// PARAMETERS: BOARD, AVATAR'S POSITION (row and column), AVATAR CHARACTER TO MOVE
// MOVES THE GIVEN AVATAR RIGHT ON THE BOARD BY 1 SPACE.
//
bool move_right(char board[SIZE][SIZE], int &row, int &col, const char avatar)
{
    bool success;
    int place;
    place = col +1;
    if (place > 11)
        success = false;
    else
    {
    success = true;

    board[row][place] = avatar;
    board[row][col]= '-';
    col = col +1;

    }


    return success;
}
//
// FUNCTION NAME: MOVE_YOURSELF
// RETURNS: VOID
// PARAMETERS: BOARD, YOUR POSITION (row and column)
// Your row and column are updated as is the board
// ASKS USER WHICH DIRECTION TO MOVE AND CALLS THE CORRECT MOVE FUNCTION.
//
void move_yourself(char board[SIZE][SIZE], int &your_row, int &your_col)
{
bool success;
char direction = 'p';
bool quit;

   cout << "What direction would you like to move: W (up),A (left),S (down),D (right)?" << endl;
   cin >> direction;
   direction = toupper(direction);
   verify_direction(direction);  // If direction entered is invalid, prompts user until valid direction chosen

   //move in direction
   switch(direction) {
       case 'w':
       case 'W':

           success = move_up(board, your_row, your_col, 'u');
           if (!success)
              cout << "You've hit a wall! Choose a different direction." << endl;

           break;
       case 'a':
       case 'A':
       success = move_left(board, your_row, your_col, 'u');
           if (!success)
              cout << "You've hit a wall! Choose a different direction." << endl;

           break;
       case 's':
       case 'S':
       success = move_down(board, your_row, your_col, 'u');
           if (!success)
              cout << "You've hit a wall! Choose a different direction." << endl;
           break;
       case 'd':
       case 'D':
       success = move_right(board, your_row, your_col, 'u');
           if (!success)
              cout << "You've hit a wall! Choose a different direction." << endl;
           break;

       default:
           cout << "Impossible error" << endl;
   }
}

//
// FUNCTION NAME: MOVE_POLICE
// RETURNS: VOID
// PARAMETERS: BOARD, YOUR POSITION, POLICE POSITION
// MOVES THE POLICE 1 SPOT TOWARD YOUR POSITION.
//
void move_police(char board[SIZE][SIZE], const int your_row, const int your_col,
                 int &police_row, int &police_col)
{
    bool success;
    //move up
    int moveup = your_row - police_row;
    if (your_col == police_col && moveup<0)
    {
        success = move_up(board, police_row, police_col, 'p');
    }
    //move right
    int moveright = your_col - police_col;
    if (your_row == police_row && moveright>0)
    {
    success = move_right(board, police_row, police_col, 'p');
    }
    //move left
    int moveleft = your_col - police_col;
    if (your_row == police_row && moveleft<0)
    success = move_left(board, police_row, police_col, 'p');
    //move down
    int movedown = your_row - police_row;
    if (your_col == police_col && movedown>0)
    {
        success = move_down(board, police_row, police_col, 'p');

    }
    // move diagonal right up
    if (moveup < 0 && moveright>0)
    {
        success = move_right(board, police_row, police_col, 'p');
        success = move_up(board, police_row, police_col, 'p');
    }
    //move diagonal left up
    else if (moveup < 0 && moveleft < 0)
    {
       success = move_up(board, police_row, police_col, 'p');
        success = move_left(board, police_row, police_col, 'p');
    }
    //move diagonal down right
    else if (movedown >0 && moveright >0)
    {
        success = move_down(board, police_row, police_col, 'p');
        success = move_right(board, police_row, police_col, 'p');
    }
    //move diagonal down left
    else if (movedown > 0 && moveleft < 0)
    {
         success = move_down(board, police_row, police_col, 'p');
        success = move_left(board, police_row, police_col, 'p');

    }
}

//
// FUNCTION NAME: CHECK_ESCAPE
// RETURNS: BOOLEAN - ESCAPED OR NOT ESCAPED
// PARAMETERS: BOARD, YOUR POSITION
// RETURNS TRUE IF YOU HAVE ESCAPED.
//
bool check_escape(char board[SIZE][SIZE], const int your_row, const int your_col)
{
    bool escaped;
    if(your_row == 6 && your_col == 11)
    escaped = true;
    else
    escaped = false;

    return escaped;
}

//
// FUNCTION NAME: CHECK_CAPTURE
// RETURNS: BOOLEAN - CAPTURED OR NOT CAPTURED
// PARAMETERS: BOARD, YOUR POSITION
// RETURNS TRUE IF YOU HAVE BEEN CAPTURED.
//
bool check_capture(char board[SIZE][SIZE], const int your_row, const int your_col, const int police_row, const int police_col)
{
    bool captured;
    int row = your_row - police_row;
    int col = your_col - police_col;
    if(row == 0 && col == 0)
    captured = true;
    else
    captured = false;

    return captured;
}

//
// FUNCTION NAME: CHECK_QUIT  bonus
// RETURNS: BOOLEAN
// PARAMETERS: NONE
// RETURNS TRUE IF USER WANTS TO QUIT.
//

int main()
{
    bool escaped = false;
    bool captured = false;
    bool quit = false;  // only needed for bonus
    char variable;
    int your_row = 1;
    int your_col = 1;
    int police_row = 0;
    int police_col = 0;
    char board[SIZE][SIZE];

    // game setup:  seed the rng, populate the board, print intro
    system("clear");
    srand (time(NULL));
    intro();
    populate(board, your_row, your_col, police_row, police_col);


     // print the board
     print_board(board);



    // loop playing turns
    while(!escaped && !captured && !quit)
    {
        // move the avatar based on user input
        move_yourself(board, your_row, your_col);
        // print the updated board
        print_board(board);
        system("clear");

        // check for captured and/or escaped
        captured = check_capture(board, your_row, your_col, police_row, police_col);

        escaped= check_escape(board, your_row, your_col);
        // if you haven't escaped or been captured
        if (!escaped && !captured)
        {
           //move police toward the user
            move_police(board, your_row, your_col, police_row, police_col);
           // print the updated board
           print_board(board);

           // check for captured and/or escaped and/or quit

              captured = check_capture(board, your_row, your_col, police_row, police_col);
              escaped = check_escape(board, your_row, your_col);
              if (!escaped && !captured)
              quit = check_quit(police_row, police_col, your_row, your_col);  // if doing bonus


        }
    }

    // print the board and end of game messages based on
    print_board(board);
    // whether or not your escaped, are captured, or are quiting and saving
    if (escaped)
        cout << "You've escaped the police!";
    else if (captured)
    {
        cout << "The police have captured you!" << endl;
        cout << "---------- YOU LOSE ----------" << endl;
    }
    else
        cout << "Game succesfully saved" << endl;

    return 0;
}
