#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 10
#define BOMBS 15

int countAdjacentBombs(char board[SIZE][SIZE], int x, int y) // check around user input for bombs
{
    int n = 0; // # of tiles around user input which contain bombs
    if (board[x-1][y-1] == 'X' && (x-1 >= 0) && (y-1 >= 0))
    {
        n++;
    }
    if (board[x-1][y] == 'X' && (x-1 >= 0))
    {
        n++;
    }
    if (board[x-1][y+1] == 'X' && (x-1 >= 0) && (y+1 <= 9))
    {
        n++;
    }
    if (board[x][y-1] == 'X' && (y-1 >= 0))
    {
        n++;
    }
    if (board[x][y+1] == 'X' && (y+1 <= 9))
    {
        n++;
    }
    if (board[x+1][y-1] == 'X' && (x+1 <= 9) && (y-1 >= 0))
    {
        n++;
    }
    if (board[x+1][y] == 'X' && (x+1 <= 9))
    {
        n++;
    }
    if (board[x+1][y+1] == 'X' && (x+1 <= 9) && (y+1 <= 9))
    {
        n++;
    }
    return n; 
}

void placeBombs(char board[SIZE][SIZE]) // place random bombs
{
    srand(time(NULL)); // allows rand() to be different every iteration
    int bombsPlaced = 0;
    while (bombsPlaced < BOMBS)
    {
        int x = rand() % 10;
        int y = rand() % 10;

        if (board[x][y] != 'X')
        {
            board[x][y] = 'X'; // change '-' to 'X'
            bombsPlaced++;
        }
    }
}

void printBoard(char board[SIZE][SIZE]) //print current board
{
    printf(" ");
    for (int k = 0; k < SIZE; k++)
    {
        printf(" %d", k);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int main ()
{
    char board[SIZE][SIZE]; // initialize master board
    char playerBoard[SIZE][SIZE]; //initialize player's board
    for (int i = 0; i < SIZE; i++) // initialize first board
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = '-';
            playerBoard[i][j] = '-';
        }
    }
    placeBombs(board); // place hidden bombs

    // printBoard(board); // cheat board to check where hidden bombs are

    int gameOver = 0; // a boolean checking if the game is over
    int remainingCells = SIZE * SIZE - BOMBS; // # of cells user has left
    printf("Welcome to Minesweeper!\n");
    printf("Enter the coordinates (x y) to reveal a cell.\n");
    printBoard(playerBoard);
    while (remainingCells > 0 && !gameOver) // run game
    {
        int x = 0;
        int y = 0;
        int num = 0;
        int flag = 1;

        while (flag == 1) // loop until valid user input
        {
            printf("Enter coordinates (x y) with space between them: ");
            scanf("%d%d", &x, &y);
            if ((x >= 0 && x <= 9) && (y >= 0 && y <= 9) && (playerBoard[x][y] == '-')) // valid input
            {
                flag = 0;
            }
            else // invalid input
            {
                if ((x < 0 || x > 9) || (y < 0 || y > 9))
                {
                    flag = 1;
                    int size = SIZE - 1;
                    printf("Invalid input. Enter integer where 0 <= x,y <= %d. Try again.\n", size);
                    printBoard(playerBoard);
                }
                else if (playerBoard[x][y] != 'X' && playerBoard[x][y] != '-')
                {
                    flag = 1;
                    printf("Invalid input. Coordinates have previously been entered. Try again.\n");
                    printBoard(playerBoard);
                }               
            }
        }

        if (board[x][y] != 'X') // display # of bombs around user coordinates
        {
            num = countAdjacentBombs(board, x, y);
            char charValue = num + '0';
            playerBoard[x][y] = charValue;
            remainingCells--; 
            printBoard(playerBoard);
        }

        else // if bomb was hit, game over
        {
            printf("Game Over! You hit a bomb.\n");
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    if (board[i][j] == 'X')
                    {
                        playerBoard[i][j] = 'X';
                    }
                }
            }
            printBoard(playerBoard);
            gameOver = 1;
        }   
    }

    if (remainingCells == 0) // game win, no tiles left to guess
    {
        printf("You Win!\n");
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == 'X')
                {
                    playerBoard[i][j] = 'X';
                }
            }
        }
        printBoard(playerBoard);
    }
}