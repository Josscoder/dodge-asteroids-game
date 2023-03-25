#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 5;
const int COLUMNS = 5;

const char PATH = '-';
const char ASTEROID = '*';
const char SHIP = '>';

void printBoard(char board[ROWS][COLUMNS]);
void initBoard(char board[ROWS][COLUMNS]);
void placeAsteroids(char board[ROWS][COLUMNS], int count);
bool moveShip(char board[ROWS][COLUMNS], int& posX, int& posY);
bool checkCoordinates(int x, int y);
bool verifyImpact(char board[ROWS][COLUMNS], int x, int y);
bool checkVictoria(int posX, int posY);

int main() {
    char board[ROWS][COLUMNS];
    int posX, posY, quantityAsteroids;

    srand(time(nullptr));

    initBoard(board);

    cout << "Enter the number of asteroids: ";
    cin >> quantityAsteroids;

    placeAsteroids(board, quantityAsteroids);

    posX = 0;
    posY = 0;

    while (true) {
        printBoard(board);

        if (checkVictoria(posX, posY)) {
            cout << "Congratulations, you reached the goal!" << endl;
            break;
        }

        if (!moveShip(board, posX, posY)) {
            cout << "Crash into an asteroid! Game Over." << endl;
            break;
        }
    }

    return 0;
}

void printBoard(char board[ROWS][COLUMNS]) {
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void initBoard(char board[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (i == (ROWS - 1)) {
                board[i][j] = '=';
            } else if (i == 0 && j == 0) {
                board[i][j] = SHIP;
            } else {
                board[i][j] = PATH;
            }
        }
    }
}


void placeAsteroids(char board[ROWS][COLUMNS], int count) {
    int counter = 0;
    while (counter < count) {
        int x = rand() % ROWS;
        int y = rand() % COLUMNS;
        if (board[x][y] == PATH) {
            board[x][y] = ASTEROID;
            counter++;
        }
    }
}

bool moveShip(char board[ROWS][COLUMNS], int& posX, int& posY) {
    int moverX, moverY;
    cout << "Enter coordinate (" << posX << ", " << posY << "): ";
    cin >> moverX >> moverY;
    if (checkCoordinates(posX + moverX, posY + moverY)) {
        board[posX][posY] = ' ';
        posX += moverX;
        posY += moverY;
        if (verifyImpact(board, posX, posY)) {
            return false;
        }
        board[posX][posY] = SHIP;
        return true;
    }
    return false;
}

bool checkCoordinates(int x, int y) {
    if (x >= 0 && x < ROWS && y >= 0 && y < COLUMNS) {
        return true;
    }
    cout << "Invalid coordinates!" << endl;
    return false;
}

bool verifyImpact(char board[ROWS][COLUMNS], int x, int y) {
    return board[x][y] == ASTEROID;
}

bool checkVictoria(int posX, int posY) {
    return posX == (ROWS - 1) && posY == (COLUMNS - 1);
}
