#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;



int computerRandomPick; //random location which computer selects if first.
int computerPick; //used to decide computer vs player AI moves.
//player interaction
int playerChoice;
bool playerTurn;
int gameWin = 3;
//gameWin is integer because it will allow program to explicitly say who wins instead of bool which will allow you to only declare game state.

//board arrays
char blockOne = '1';
char blockTwo = '2';
char blockThree = '3';
char blockFour = '4';
char blockFive = '5';
char blockSix = '6';
char blockSeven = '7';
char blockEight = '8';
char blockNine = '9';
//random starting turn chooser
int turnFirst; //variable to decide whoever goes first

void checkWinComputer()
{
    if(blockOne == 'O' && blockFive == 'O' && blockNine == 'O' && playerTurn == false) //diagonal, 1 - 5 = 9
        gameWin = 2; //This will make computer win.
    if(blockThree == 'O' && blockFive == 'O' && blockSeven == 'O' && playerTurn == false) //diagonal, 3 - 5 = 7
        gameWin = 2;
    if(blockOne == 'O' && blockTwo == 'O' && blockThree == 'O' && playerTurn == false) //horizontal 1 - 2 = 3
        gameWin = 2;
    if(blockFour == 'O' && blockFive == 'O' && blockSix == 'O' && playerTurn == false) //horizontal 4 - 5 = 6
        gameWin = 2;
    if(blockSeven == 'O' && blockEight == 'O' && blockNine == 'O' && playerTurn == false) //horizontal 7 - 8 = 9
        gameWin = 2;
    if(blockOne == 'O' && blockFour == 'O' && blockSeven == 'O' && playerTurn == false) //vertical 1 - 4 = 7
        gameWin = 2;
    if(blockTwo == 'O' && blockFive == 'O' && blockEight == 'O' && playerTurn == false) //vertical 2 - 5 = 8
        gameWin = 2;
    if(blockThree == 'O' && blockSix == 'O' && blockNine == 'O' && playerTurn == false) //vertical 3 - 6 = 9
        gameWin = 2;
}
void checkWinPlayer()
{
    if(blockOne == 'X' && blockFive == 'X' && blockNine == 'X' && playerTurn == true) //diagonal, 1 - 5 = 9
        gameWin = 1; //This will make player win.
    if(blockThree == 'X' && blockFive == 'X' && blockSeven == 'X' && playerTurn == true) //diagonal, 3 - 5 = 7
        gameWin = 1;
    if(blockOne == 'X' && blockTwo == 'X' && blockThree == 'X' && playerTurn == true) //horizontal 1 - 2 = 3
        gameWin = 1;
    if(blockFour == 'X' && blockFive == 'X' && blockSix == 'X' && playerTurn == true) //horizontal 4 - 5 = 6
        gameWin = 1;
    if(blockSeven == 'X' && blockEight == 'X' && blockNine == 'X' && playerTurn == true) //horizontal 7 - 8 = 9
        gameWin = 1;
    if(blockOne == 'X' && blockFour == 'X' && blockSeven == 'X' && playerTurn == true) //vertical 1 - 4 = 7
        gameWin = 1;
    if(blockTwo == 'X' && blockFive == 'X' && blockEight == 'X' && playerTurn == true) //vertical 2 - 5 = 8
        gameWin = 1;
    if(blockThree == 'X' && blockSix == 'X' && blockNine == 'X' && playerTurn == true) //vertical 3 - 6 = 9
        gameWin = 1;
}
int computerAI() //work on computerAI part where the computer tries to win before countering.
{
    playerTurn == false;

    if(blockOne == 'O' && blockTwo == 'O' && playerTurn == false && blockThree == '3') //1 - 2 = 3 win
    {
        blockThree = 'O';
        playerTurn = true;
    }

    if(blockFour == 'O' && blockFive == 'O' && playerTurn == false && blockSix == '6') //4 - 5 = 6 win
    {
        blockSix = 'O';
        playerTurn = true;
    }

    if(blockSeven == 'O' && blockEight == 'O' && playerTurn == false && blockNine == '9') //7 - 8 = 9 win
    {
        blockNine = 'O';
        playerTurn = true;
    }

    if(blockOne == 'O' && blockFour == 'O' && playerTurn == false && blockSeven == '7') //1 - 4 = 7 win
    {
        blockSeven = 'O';
        playerTurn = true;
    }

    if(blockTwo == 'O' && blockFive == 'O' && playerTurn == false && blockEight == '8') //2 - 5 = 8 win
    {
        blockEight = 'O';
        playerTurn = true;
    }

    if(blockThree == 'O' && blockSix == 'O' && playerTurn == false && blockNine == '9') //3 - 6 = 9 win
    {
        blockNine = 'O';
        playerTurn = true;
    }

    if(blockOne == 'O' && blockFive == 'O' && playerTurn == false && blockNine == '9') //1 - 5 = 9 win
    {
        blockNine = 'O';
        playerTurn = true;
    }

    if(blockThree == 'O' && blockFive == 'O' && playerTurn == false && blockSeven == '7') //3 - 5 = 7 win
    {
        blockSeven = 'O';
        playerTurn == true;
    }

    if((playerChoice == 1 || playerChoice == 5 || playerChoice == 9) && playerTurn == false)
    {
        if((blockOne == 'X' && blockFive == 'X') && playerTurn == false && blockNine == '9') //1 - 5 = 9 diagonal
        {
            blockNine = 'O';
            playerTurn = true;
        }

        if((blockOne == 'X' && blockNine == 'X') && playerTurn == false && blockFive == '5') //1 - 9 = 5 diagonal
        {
            blockFive = 'O';
            playerTurn = true;
        }

        if((blockFive == 'X' && blockNine == 'X') && playerTurn == false && blockOne == '1') //5 - 9 = 1 diagonal
        {
            blockOne = 'O';
            playerTurn = true;
        }
    }

    if((playerChoice == 3 || playerChoice == 5 || playerChoice == 7) && playerTurn == false)
    {
        if((blockSeven == 'X' && blockFive == 'X') && playerTurn == false && blockThree == '3') //7 - 5 = 3 diagonal
        {
            blockThree = 'O';
            playerTurn = true;
        }

        if((blockSeven == 'X' && blockThree == 'X') && playerTurn == false && blockFive == '5') //7 - 3 = 5 diagonal
        {
            blockFive = 'O';
            playerTurn = true;
        }

        if((blockFive == 'X' && blockThree == 'X') && playerTurn == false && blockSeven == '7') //5 - 3 = 7 diagonal
        {
            blockSeven = 'O';
            playerTurn = true;
        }
    }

    if((playerChoice == 1 || playerChoice == 2 || playerChoice == 3) && playerTurn == false)
    {
        if((blockOne == 'X' && blockTwo == 'X') && playerTurn == false && blockThree == '3') // 1 - 2 = 3 horizontal
        {
            blockThree = 'O';
            playerTurn = true;
        }

        if((blockOne == 'X' && blockThree == 'X') && playerTurn == false && blockTwo == '2') //1 - 3 = 2 horizontal
        {
            blockTwo = 'O';
            playerTurn = true;
        }

        if((blockTwo == 'X' && blockThree == 'X') && playerTurn == false && blockOne == '1') //2 - 3 = 1 horizontal
        {
            blockOne = 'O';
            playerTurn = true;
        }
    }

    if((playerChoice == 4 || playerChoice == 5 || playerChoice == 6) && playerTurn == false)
    {
        if((blockFour == 'X' && blockFive == 'X') && playerTurn == false && blockSix == '6') //4 - 5 = 6 horizontal line 2
        {
            blockSix = 'O';
            playerTurn = true;
        }

        if((blockFour == 'X' && blockSix == 'X') && playerTurn == false && blockFive == '5') //4 - 6  = 5 horizontal line 2
        {
            blockFive = 'O';
            playerTurn = true;
        }

        if((blockFive == 'X' && blockSix == 'X') && playerTurn == false && blockFour == '4') //5 - 6 = 4 horizontal line 2
        {
            blockFour = 'O';
            playerTurn = true;
        }
    }

    if((playerChoice == 7 || playerChoice == 8 || playerChoice == 9) && playerTurn == false)
    {
        if((blockSeven == 'X' && blockEight == 'X') && playerTurn == false && blockNine == '9') //7 - 8 = 9 horizontal line 3
        {
            blockNine = 'O';
            playerTurn = true;
        }

        if((blockSeven == 'X' && blockNine == 'X') && playerTurn == false && blockEight == '8') //7 - 9 = 8 horizontal line 3
        {
            blockEight = 'O';
            playerTurn = true;
        }

        if((blockEight == 'X' && blockNine == 'X') && playerTurn == false && blockSeven == '7') //8 - 9 = 7 horizontal line 3
        {
            blockSeven = 'O';
            playerTurn = true;
        }
    }

    if((playerChoice == 1 || playerChoice == 4 || playerChoice == 7) && playerTurn == false)
    {
        if((blockOne == 'X' && blockFour == 'X') && playerTurn == false && blockSeven == '7') //1 - 4 = 7 vertical row 1
        {
            blockSeven = 'O';
            playerTurn = true;
        }

        if((blockOne == 'X' && blockSeven == 'X') && playerTurn == false && blockFour == '4') //1 - 7 = 4 vertical row 1
        {
            blockFour = 'O';
            playerTurn = true;
        }

        if((blockFour == 'X' && blockSeven == 'X') && playerTurn == false && blockOne == '1') //4 - 7 = 1 vertical row 1
        {
            blockOne = 'O';
            playerTurn = true;
        }

    }

    if((playerChoice == 2 || playerChoice == 5 || playerChoice == 8) && playerTurn == false)
    {
        if((blockTwo == 'X' && blockFive == 'X') && playerTurn == false && blockEight == '8') //2 - 5 = 8 vertical row 2
        {
            blockEight = 'O';
            playerTurn = true;
        }

        if((blockTwo == 'X' && blockEight == 'X') && playerTurn == false && blockFive == '5') //2 - 8 = 5 vertical row 2
        {
            blockFive = 'O';
            playerTurn = true;
        }

        if((blockFive == 'X' && blockEight == 'X') && playerTurn == false && blockTwo == '2') //5 - 8 = 2 vertical row 2
        {
            blockTwo = 'O';
            playerTurn = true;
        }
    }

    if((playerChoice == 3 || playerChoice == 6 || playerChoice == 9) && playerTurn == false)
    {
        if((blockThree == 'X' && blockSix == 'X') && playerTurn == false && blockNine == '9') //3 - 6 = 9 vertical row 3
        {
            blockNine = 'O';
            playerTurn = true;
        }

        if((blockThree == 'X' && blockNine == 'X') && playerTurn == false && blockSix == '6') //3 - 9 = 6 vertical row 3
        {
            blockSix = 'O';
            playerTurn = true;
        }

        if((blockSix == 'X' && blockNine == 'X') && playerTurn == false && blockThree == '3') //6 - 9 = 3 vertical row 3
        {
            blockThree = 'O';
            playerTurn = true;
        }
    }
    else
    {
        do
        {

            if(blockOne == '1' && playerTurn == false)
            {
                playerTurn = true;
                blockOne = 'O';
            }
            if(blockTwo == '2' && playerTurn == false)
            {
                playerTurn = true;
                blockTwo = 'O';
            }
            if(blockThree == '3' && playerTurn == false)
            {
                playerTurn = true;
                blockThree = 'O';
            }
            if(blockFour == '4' && playerTurn == false)
            {
                playerTurn = true;
                blockFour = 'O';
            }
            if(blockFive == '5' && playerTurn == false)
            {
                playerTurn = true;
                blockFive = 'O';
            }
            if(blockSix == '6' && playerTurn == false)
            {
                playerTurn = true;
                blockSix = 'O';
            }
            if(blockSeven == '7' && playerTurn == false)
            {
                playerTurn = true;
                blockSeven = 'O';
            }
            if(blockEight == '8' && playerTurn == false)
            {
                playerTurn = true;
                blockEight = 'O';
            }
            if(blockNine == '9' && playerTurn == false)
            {
                playerTurn = true;
                blockNine = 'O';
            }
        }
        while(playerTurn = false);
    }
    return 0;
}

int checkPlayerInput()
{
    if(playerChoice == 1 && blockOne == '1')
        blockOne = 'X';
    if(playerChoice == 2 && blockTwo == '2')
        blockTwo = 'X';
    if(playerChoice == 3 && blockThree == '3')
        blockThree = 'X';
    if(playerChoice == 4 && blockFour == '4')
        blockFour = 'X';
    if(playerChoice == 5 && blockFive == '5')
        blockFive = 'X';
    if(playerChoice == 6 && blockSix == '6')
        blockSix = 'X';
    if(playerChoice == 7 && blockSeven == '7')
        blockSeven = 'X';
    if(playerChoice == 8 && blockEight == '8')
        blockEight = 'X';
    if(playerChoice == 9 && blockNine == '9')
        blockNine = 'X';


    return 0;
}

int checkComputerInput()
{
    if(computerPick == 1 && blockOne == '1')
        blockOne = 'O';
    if(computerPick == 2 && blockTwo == '2')
        blockTwo = 'O';
    if(computerPick == 3 && blockThree == '3')
        blockThree = 'O';
    if(computerPick == 4 && blockFour == '4')
        blockFour = 'O';
    if(computerPick == 5 && blockFive == '5')
        blockFive = 'O';
    if(computerPick == 6 && blockSix == '6')
        blockSix = 'O';
    if(computerPick == 7 && blockSeven == '7')
        blockSeven = 'O';
    if(computerPick == 8 && blockEight == '8')
        blockEight = 'O';
    if(computerPick == 9 && blockNine == '9')
        blockNine = 'O';

    return 0;
}

void gameBoard()
{
    cout << "+-----+-----+-----+" << endl;
    cout << "|  " <<blockOne << "  |  " << blockTwo << "  |  " << blockThree << "  |" << endl;
    cout << "+-----+-----+-----+" << endl;
    cout << "|  " <<blockFour << "  |  " << blockFive << "  |  " << blockSix << "  |" << endl;
    cout << "+-----+-----+-----+" << endl;
    cout << "|  " <<blockSeven << "  |  " << blockEight << "  |  " << blockNine << "  |\n";
    cout << "+-----+-----+-----+" << endl;
}

void checkTie()
{
    if(blockOne != '1' && blockTwo != '2' && blockThree != '3' && blockFour != '4' && blockFive != '5' && blockSix != '6' && blockSeven != '7' && blockEight != '8' && blockNine != '9')
    {
        cout << "It's a tie!" << endl;
        gameWin = 0;
    }
//Check on this line since it doesnt work..

}



int main()
{
    //RNGs
    srand(time(0));
    int playAgain;

    int playerScore = 0;
    int computerScore = 0;
    int ties = 0;

    do
    {
        system("CLS");
        turnFirst = rand()% (2 - 1 + 1)+1;//generates starting person.
        computerRandomPick = rand()% (9 - 1 + 1)+1;//computer first pick - random
        gameWin = 3;
        blockOne = '1';
        blockTwo = '2';
        blockThree = '3';
        blockFour = '4';
        blockFive = '5';
        blockSix = '6';
        blockSeven = '7';
        blockEight = '8';
        blockNine = '9';

        //BEGIN OF PROGRAM
        cout << "Welcome to Tic Tac Toe!" <<endl<< endl;
        cout << "Player: " << playerScore << " Computer: "<< computerScore << " Ties: " << ties << endl;

        if(turnFirst == 1)//player first
        {
            cout << "Please choose a grid to place (X): "<<endl<<endl;
            gameBoard();//Gameboard for tic tac toe
            while (!(cin >> playerChoice)) //error traps letters and words
            {
                cout << endl;
                cout << "Numbers only." << endl;
                cin.clear();
                cin.ignore(10000,'\n');
            }
            checkPlayerInput();
            system("CLS");
            gameBoard();
            playerTurn = false; //switches to computer
        }

        if(turnFirst == 2)//Computer first
        {
            computerRandomPick;
            computerPick = computerRandomPick;
            checkComputerInput();
            cout << "The computer is choosing...\n" << endl;
            playerTurn = true;
            gameBoard();
        }


        do
        {
            if(playerTurn == true) //player loop
            {
                cout << "Please choose a grid to place (X): "<<endl<<endl;
                while (!(cin >> playerChoice)) //error traps letters and words
                {
                    cout << endl;
                    cout << "Numbers only." << endl;
                    cin.clear();
                    cin.ignore(10000,'\n');
                }
                checkPlayerInput();
                checkWinPlayer();
                checkTie();
                playerTurn = false;
            }

            if(playerTurn == false) //computer loop
            {
                computerAI();
                system("CLS");
                gameBoard();
                checkWinComputer();
                checkTie();
                playerTurn = true;
            }

        }
        while(gameWin > 2);

        if(gameWin == 0)
        {
            cout << "The game is a Tie!" << endl;
            ++ties;
        }


        if(gameWin == 1)
        {
            cout << "The player wins!" << endl;
            ++playerScore;
        }

        if(gameWin == 2)
        {
            cout << "The computer wins!" << endl;
            ++computerScore;
        }


        cout << "Player: " << playerScore << " "<< "Computer: " << computerScore << " Ties: "<< ties << endl;


        cout << "Play again?\n1. Yes\n2. No\n" << endl;

        while (!(cin >> playAgain)) //error traps letters and words
        {
            cout << endl;
            cout << "Play again?\n1. Yes\n2. No\n" << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }


    }
    while(playAgain == 1);

    return 0;
}