#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int playerBoard[5][5];
int computerBoard[5][5];
int computerBoardHidden[5][5];

void print_board(int board[5][5]) {
    int i, j;

    cout << "  A B C D E \n";

    for (i = 0; i < 5; i++) {
        cout << i + 1 << " ";
        for (j = 0; j < 5; j++) {
            if (board[i][j] == 0) cout << ". ";
            if (board[i][j] == 1) cout << "x ";
            if (board[i][j] == 2) cout << "@ ";
        }
        cout << endl;
    }
}

void clean_board(int board[5][5]) {
    int i, j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            board[i][j] = 0;
    }
}

int touch(int board[5][5], int j, int i, int y, int x) {
    for (int k = j - 1; k <= j + 1; k++)
        for (int l = i - 1; l <= i + 1; l++)
            if ((x == l) && (y == k) && board[k][l] == 2)
                return 1;

    return 0;
}

void place_ships(int board[5][5]) {
    int x, y;
    int orient, invalid;

    srand(time(NULL));

    for (int s = 0; s < 3; s++) {
        do {
            x = rand() % 5;
            y = rand() % 5;
            orient = rand() % 2;

            if (orient) {
                invalid = touch(board, y, x, y, x) || touch(board, y, x, y, x + 1);
            }
            else {
                invalid = touch(board, y, x, y + 1, x);
            }
        } while (invalid);

        board[y][x] = 2;

        if (orient) {
            board[y][x + 1] = 2;
        }
        else {
            board[y + 1][x] = 2;
        }
    }
}

int main() {
    int cx, cy;
    char gx;
    int gy;
    const int cA = 'A';

    clean_board(playerBoard);
    clean_board(computerBoard);
    clean_board(computerBoardHidden);

    place_ships(playerBoard);
    place_ships(computerBoard);

    do {
        print_board(playerBoard);
        cout << "Podaj kolumne [A-E] ";
        cin >> gx;
        cout << "Podaj wiersz [1-5] ";
        cin >> gy;
        cx = (int)gx - (int)cA;
        gy--;

        if (computerBoard[gy][cx] == 2) {
            cout << "Trafiony!" << endl;
            playerBoard[gy][cx] = 2;
            computerBoardHidden[gy][cx] = 2;
        }
        else {
            cout << "Pudło!" << endl;
            playerBoard[gy][cx] = 1;
            computerBoardHidden[gy][cx] = 1;
        }

        print_board(computerBoardHidden);

        cy = rand() % 5;
        cx = rand() % 5;

        if (playerBoard[cy][cx] == 2) {
            cout << "Komputer trafił!" << endl;
            playerBoard[cy][cx] = 1;
        }

    } while (true);

    return 0;
}
