#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <Windows.h> // only used for sleep f-n for exicutable file 

// make_move(board, column, player) updates the board following a move
//   by the given player in the given column; returns false if the move
//   was illegal because the column was full
// requires: 1 <= column < 7
//           player is either 'X' or 'O'
bool make_move(char board[6][7], int column, char player)
{
    if (column < 1 || column > 7)
    {
        return false;
    }
    
    for (int i = 5; i >= 0; i--)
    {
        if (board[i][column - 1] != 'X' && board[i][column - 1] != 'O')
        {
            board[i][column - 1] = player;
            return true; 
        }
    }

    return false;
}

// check_win(board) returns true if the given player has 4 connected
//   pieces on the board
bool check_win(char board[6][7], char player)
{
    // Horizontal Check
    for (int i = 0; i < 6; i++) // would be more efficient if it started at the bottom and went towards the top
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j+ 3] == player)
            {
                return true;
            }
        }
    }

    // Vertical Check
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player)
            {
                return true;
            }
        }
    }

    // Diagonal Check (forward)
    for (int i = 5; i > 2; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player)
            {
                return true;
            }
        }
    }

    // Diagonal Check (backwards)
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player)
            {
                return true;
            }
        }
    }

    return false;
}

// test_check_win() tests the make_move function using assert; if an error is
//   detected then the program stops
void test_check_win(void)
{
    //for test boards, X/Os can be floating in mid-air, doesn't matter
    //horizontal test initializations
    char test_a[6][7] = { {'X', 'X', 'X', 'X', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'}, 
                          {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'} };

    char test_b[6][7] = { {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'}, 
                          {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', 'O', 'O', 'O', 'O'} };
    
    //vertical test initalizations
    char test_c[6][7] = { {'*', '*', '*', '*', '*', '*', '*'},
                          {'X', '*', '*', '*', '*', '*', '*'}, 
                          {'X', '*', '*', '*', '*', '*', '*'},
                          {'X', '*', '*', '*', '*', '*', '*'},
                          {'X', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'} };

    char test_d[6][7] = { {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'}, 
                          {'*', '*', '*', '*', 'O', '*', '*'},
                          {'*', '*', '*', '*', 'O', '*', '*'},
                          {'*', '*', '*', '*', 'O', '*', '*'},
                          {'*', '*', '*', '*', 'O', '*', '*'} };

    //diagonal test initalizations
    char test_e[6][7] = { {'X', '*', '*', '*', '*', '*', '*'},
                          {'*', 'X', '*', '*', '*', '*', '*'}, 
                          {'*', '*', 'X', '*', '*', '*', '*'},
                          {'*', '*', '*', 'X', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'} };

    char test_f[6][7] = { {'*', '*', '*', '*', '*', '*', '*'},
                          {'*', '*', '*', '*', '*', '*', '*'}, 
                          {'*', '*', '*', '*', '*', '*', 'O'},
                          {'*', '*', '*', '*', '*', 'O', '*'},
                          {'*', '*', '*', '*', 'O', '*', '*'},
                          {'*', '*', '*', 'O', '*', '*', '*'} };

    //test without win
    char test_g[6][7] = { {'X', '*', '*', '*', '*', '*', '*'},
                          {'O', '*', '*', '*', 'O', '*', '*'}, 
                          {'X', '*', 'O', 'O', 'O', '*', '*'},
                          {'X', '*', 'X', 'X', 'X', '*', '*'},
                          {'X', 'O', 'X', 'O', 'O', 'X', '*'},
                          {'O', 'X', 'O', 'X', 'O', 'O', 'X'} };

    //actual asserts
    assert(check_win(test_a, 'X') == true);
    assert(check_win(test_b, 'O') == true);
    assert(check_win(test_c, 'X') == true);
    assert(check_win(test_d, 'O') == true);
    assert(check_win(test_e, 'X') == true);
    assert(check_win(test_f, 'O') == true);
    assert(check_win(test_g, 'X') == false);
    assert(check_win(test_g, 'O') == false);
}

// test_make_move() tests the check_win function using assert; if an error is
//   detected then the program stops
void test_make_move(void)
{
    char test_z[6][7] = { {'X', '*', '*', '*', '*', '*', '*'},
                          {'O', '*', '*', '*', 'O', '*', '*'}, 
                          {'X', '*', 'O', 'O', 'O', '*', '*'},
                          {'X', '*', 'X', 'X', 'X', '*', '*'},
                          {'X', 'O', 'X', 'O', 'O', 'X', '*'},
                          {'O', 'X', 'O', 'X', 'O', 'O', 'X'} };
    
    char check_z[6][7] = { {'X', '*', '*', '*', '*', '*', '*'},
                           {'O', '*', '*', '*', 'O', '*', '*'}, 
                           {'X', '*', 'O', 'O', 'O', '*', '*'},
                           {'X', '*', 'X', 'X', 'X', '*', '*'},
                           {'X', 'O', 'X', 'O', 'O', 'X', 'X'},
                           {'O', 'X', 'O', 'X', 'O', 'O', 'X'} };
    assert(make_move(test_z, 1, 'X') == false);
    assert(make_move(test_z, 7, 'X') == true);
    assert(test_z[4][6] == check_z[4][6]);
}

// Helper f-n to print board
void print_board(char board[6][7])
{
    printf(" 1 2 3 4 5 6 7 \n");
    printf("|-------------|\n");
    for (int i = 0; i < 6; i++)
    {
        printf("|");
        for (int j = 0; j < 7; j++)
        {
            if (j != 6)
            {
                printf("%c ", board[i][j]);
            }
            else if (j = 6)
            {
                printf("%c", board[i][j]);
            }
        }
        printf("|");
        printf("\n");

    }
    printf("|-------------|\n\n");
}

bool check_tie(char board[6][7])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == '*')
            {
                return false;
            }
        }
    }

    return true;
}



int main(void)
{
    char board[6][7] = { {'*', '*', '*', '*', '*', '*', '*'},
                         {'*', '*', '*', '*', '*', '*', '*'}, 
                         {'*', '*', '*', '*', '*', '*', '*'},
                         {'*', '*', '*', '*', '*', '*', '*'},
                         {'*', '*', '*', '*', '*', '*', '*'},
                         {'*', '*', '*', '*', '*', '*', '*'}, };
    int column;
    print_board(board);

    while (check_win(board, 'X') == false || check_win(board, 'O') == false)
    {
        printf("Player 'X' enter a column to play:\n");
        if (scanf(" %1d", &column) != 1 || make_move(board, column, 'X') == false)
        {
            printf("Invalid Move, Player 'X' try again:\n");
            scanf(" %1d", &column);
            make_move(board, column, 'X');
        }
        printf("\n");
        print_board(board);

        if (check_win(board, 'X') == true)
        {
            printf("Congratulations Player 'X' You Win!\n");
            break;
        }

        printf("Player 'O' enter a column to play:\n");
        if (scanf(" %1d", &column) != 1 || make_move(board, column, 'O') == false)
        {
            printf("Invalid Move, Player 'O' try again:\n");
            scanf(" %1d", &column);
            make_move(board, column, 'O');
        }
        printf("\n");
        print_board(board);

        if (check_win(board, 'O') == true)
        {
            printf("Congratulations Player 'O' You Win!\n");
            break;
        }

        if (check_tie(board) == true)
        {
            printf("Tie Game: No more possible moves\n");
            break;
        }
    }

    Sleep(10000);

    return 0;
}