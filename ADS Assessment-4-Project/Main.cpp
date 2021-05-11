#include <iostream>
#include <windows.h>
#include <fstream>									//Library for File System control
#include <chrono>									//Library for Time Control
#include <cstdlib>
#include <ctime>
using namespace std;


// Constants for home menu
enum HomeMenuChoices
{
    PLAYVSPLAY = 1,
    PLAYVSCOM = 2,
    SCORES = 3,
    QUIT = 4,
    NO_CHOICE
};

// Input is player's choice. Output is true (valid) or false (invalid)
bool isValidChoice(int menuChoice)
{
    return (menuChoice > 0 && menuChoice < NO_CHOICE);
}

int showHomeMenuPrompt()
{
    int choice = -1;

    cout << " 1: Play against a foe\n 2: Play against Cortana\n 3: Check Scores\n 4: Take the cowards way out\n\n";
    cout << "\t Enter your Choice > ";
    return choice;
}


//store characters for input
char square[10] = { 'o','q','w','e','a','s','d','z','x','c' };

//Global functions 
int isWinner();
void background();



//Master function handling the player control and board letter switching
int main()
{

    int menuChoice = NO_CHOICE;
    char player = 1, i, choice;
    char mark;
    int maxTime = 300;
    double time_spent = 0.0;


    while (menuChoice != QUIT)      // Add check: player isnt broke
    {
        menuChoice = showHomeMenuPrompt();  // Offer starting menu

        if (menuChoice == PLAYVSPLAY)
        {
            do
            {
                background();
                player = (player % 2) ? 1 : 2;
                //start time 
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

                cout << "BTW your on the clock, tic tok, tic tok\n\n";
                cout << "\nif you want to surrender hit ESCAPE\n\n";
                cout << "if you wanna instant rematch hit R\n\n";
                cout << "Player " << player << ", enter the letter you want to place:  ";


                std::cin >> choice ;


                //end time and output MS
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                cout << "Milliseconds = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

                mark = (player == 1) ? 'X' : 'O';

                //////cant get time working\\\\\\\\\
                //if ((end.time_since_epoch() - begin.time_since_epoch()) == maxTime)
                //{
                //    cout << "BTW your on the clock, tic tok, tic tok\n\n";
                //}


                if (choice == 'q' && square[1] == 'q')
                    square[1] = mark;
                else if (choice == 'w' && square[2] == 'w')
                    square[2] = mark;
                else if (choice == 'e' && square[3] == 'e')
                    square[3] = mark;
                else if (choice == 'a' && square[4] == 'a')
                    square[4] = mark;
                else if (choice == 's' && square[5] == 's')
                    square[5] = mark;
                else if (choice == 'd' && square[6] == 'd')
                    square[6] = mark;
                else if (choice == 'z' && square[7] == 'z')
                    square[7] = mark;
                else if (choice == 'x' && square[8] == 'x')
                    square[8] = mark;
                else if (choice == 'c' && square[9] == 'c')
                    square[9] = mark;
                else if (choice == VK_ESCAPE)
                    return(0);
                else if (choice == 'r')
                {
                    system("cls");
                    main();
                }
                else
                {
                    cout << "Thats not gonna work, Try Again";
                    player--;
                    std::cin.ignore();
                    std::cin.get();
                }
                i = isWinner();

                player++;
            } 
            while (i == -1);
            background();
            if (i == 1)

                cout << "==>\aPlayer " << --player << " win ";
            else
                cout << "==>\aGame draw";

            std::cin.ignore();
            std::cin.get();
            return 0;
        }

    }


        if (menuChoice == PLAYVSCOM)
        {


        }


        if (menuChoice == SCORES)
        {


        }


        if (menuChoice == QUIT)
        {
            return 0;
        }
    }







    

/*********************************************
    FUNCTION TO RETURN GAME STATUS
    1 FOR GAME IS OVER WITH RESULT
    -1 FOR GAME IS IN PROGRESS
    O GAME IS OVER AND NO RESULT
**********************************************/

int isWinner()
{
    if (square[1] == square[2] && square[2] == square[3])

        return 1;
    else if (square[4] == square[5] && square[5] == square[6])

        return 1;
    else if (square[7] == square[8] && square[8] == square[9])

        return 1;
    else if (square[1] == square[4] && square[4] == square[7])

        return 1;
    else if (square[2] == square[5] && square[5] == square[8])

        return 1;
    else if (square[3] == square[6] && square[6] == square[9])

        return 1;
    else if (square[1] == square[5] && square[5] == square[9])

        return 1;
    else if (square[3] == square[5] && square[5] == square[7])

        return 1;
    else if (square[1] != 'q' && square[2] != 'w' && square[3] != 'e'
        && square[4] != 'a' && square[5] != 's' && square[6] != 'd'
        && square[7] != 'z' && square[8] != 'x' && square[9] != 'c')

        return 0;
    else
        return -1;
}


/*******************************************************************
     FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYERS MARK
********************************************************************/


void background()
{
    system("cls");
    cout << "\n\n\tTic Tac Toe\n\n";

    cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
    cout << endl;

    cout << "     |     |     " << endl;
    cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;

    cout << "     |     |     " << endl << endl;
}

/*******************************************************************
                END OF PROJECT
********************************************************************/
