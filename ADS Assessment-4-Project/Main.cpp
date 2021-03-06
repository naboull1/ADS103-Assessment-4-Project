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

//Display menu and request input
int showHomeMenuPrompt()
{
    int choice = -1;

    cout << " 1: Play against a foe\n 2: Play against Cortana\n 3: Check Scores\n 4: Take the cowards way out\n\n";
    cout << "\t Enter your Choice > ";
    cin >> choice;
    return choice;
}






//store characters for input
char square[10] = { 'o','q','w','e','a','s','d','z','x','c' };

//function to reset background board
void resetArray()
{
    square[0] = 'o';
    square[1] = 'q';
    square[2] = 'w';
    square[3] = 'e';
    square[4] = 'a';
    square[5] = 's';
    square[6] = 'd';
    square[7] = 'z';
    square[8] = 'x';
    square[9] = 'c';
}

//Global functions
int isWinner();
void background();


//Master function handling the player control and board letter switching
int main()
{

    int menuChoice = NO_CHOICE;
    char player = 1, i, choice;
    int playerName = 1;
    char mark;
    //int maxTime = 300;
    //double time_spent = 0.0;

    while (menuChoice != QUIT)      // Add check: player isnt broke
    {
        menuChoice = showHomeMenuPrompt();  // Offer starting menu

        //player vs player section
        if (menuChoice == PLAYVSPLAY)
        {
            do
            {
                background();
                player = (player % 2) ? 1 : 2;
                playerName = (player % 2) ? 1 : 2;
                //start time 
                // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


                cout << "BTW your on the clock, tic tok, tic tok\n\n";
                cout << "\nif you want to surrender hit ESCAPE\n\n";
                cout << "if you want instant rematch hit R\n\n";
                cout << "Player " << playerName << ", enter the letter you want to place:  ";


                cin >> choice;

                //end time and output MS
                //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                //cout << "Milliseconds = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

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
                {
                    exit(3);
                    return 3;
                }
                else if (choice == 'r')
                {
                    resetArray();
                    system("cls");
                    main();
                }
                else
                {
                    cout << "Thats not gonna work, Try Again";
                    player--;
                    playerName--;
                    cin.ignore();
                    cin.get();
                }
                i = isWinner();

                player++;
                playerName++;
            }             while (i == -1);
            background();
            if (i == 1)
            {
                cout << "==>\aPlayer " << --playerName << " win ";
                ofstream outfile;

                outfile.open("ScoreCount.txt", ios_base::app);
                outfile << "\nplayer " << playerName << "  Gets 1 point";
                outfile.close();

                resetArray();
                cin.ignore();
                cin.get();
                system("cls");
                main();
            }
            else
                cout << "==>\aGame draw";
                resetArray();
                cin.ignore();
                cin.get();
                system("cls");
                main();
        }




        if (menuChoice == PLAYVSCOM)
        {
            cout << "\n\n\ncoming soon\n\n\n";
            //unable to implement :(
        }


        if (menuChoice == SCORES)
        {
            string firstLineVariable;

            ifstream readFile;
            readFile.open("ScoreCount.txt");
            
            cout << "List all SCORES:\n\n\n";

            ifstream myfile("ScoreCount.txt");
            if (myfile.is_open())
            {
                while (getline(myfile, firstLineVariable))
                {
                    cout << firstLineVariable << '\n';
                }
                myfile.close();
            }

            else 
            cout << "No Scores to show";
            cin.ignore();
            cin.get();
            system("cls");
        }


        if (menuChoice == QUIT)
        {
            exit(3);
            return 3;
        }
    }
}



//winner calculation section
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


//background display section
void background()
{
    system("cls");
    cout << "\n\n\tWELCOME TO EXTREME NOTS AND CROSSES\n\n";

    cout << "PLAYER 1 IS X  -  PLAYER 2 IS 0 " << endl << endl;
    cout << endl;

    cout << "                 |     |     " << endl;
    cout << "              " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;

    cout << "            _____|_____|_____" << endl;
    cout << "                 |     |     " << endl;

    cout << "              " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;

    cout << "            _____|_____|_____" << endl;
    cout << "                 |     |     " << endl;

    cout << "              " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;

    cout << "                 |     |     " << endl << endl;
}
            

