#include "Labirint.h"
#include "ConfigManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Labirint::Labirint(int w, int h) : width(w), height(h) {
    grid.resize(width, vector<char>(height, Config::WALL));
}

void Labirint::clearGrid() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[x][y] = Config::WALL;
        }
    }
}

void Labirint::init(const std::string& seedStr) {
    clearGrid();


    unsigned int seedValue;
    if (seedStr == "r" || seedStr == "R") {
        seedValue = static_cast<unsigned int>(time(nullptr));
    } else {
        seedValue = 0;
        for (char c : seedStr) seedValue += static_cast<unsigned int>(c);
    }
    srand(seedValue);

    // Точка старта на левой границе
    startX = 0;
    startY = rand() % (height - 2) + 1;

    playerX = startX;
    playerY = startY;

    // Генерируем путь
    generatePath();

    grid[startX][startY] = Config::START;
    grid[finishX][finishY] = Config::FINISH;
}

void Labirint::generatePath() {
    int curX = startX;
    int curY = startY;

    grid[curX][curY] = Config::PATH;

    while (curX < width - 1) {
        int dir = rand() % 3; // 0 - Вправо, 1 - Вверх, 2 - Вниз

        if (dir == 0) {
            curX++;
        } else if (dir == 1 && curY > 1) {
            curY--;
        } else if (dir == 2 && curY < height - 2) {
            curY++;
        }

        grid[curX][curY] = Config::PATH;
    }

    finishX = curX;
    finishY = curY;
}

bool Labirint::movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;

    direction = tolower(direction);
    if (direction == 'w') newY--;
    else if (direction == 's') newY++;
    else if (direction == 'a') newX--;
    else if (direction == 'd') newX++;
    else return false;

    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
        if (grid[newX][newY] != Config::WALL) {
            playerX = newX;
            playerY = newY;
            return true;
        }
    }
    return false;
}

bool Labirint::isFinished() const {
    return (playerX == finishX && playerY == finishY);
}

void Labirint::draw() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == playerX && y == playerY) {
                cout << Config::PLAYER << ' ';
            } else {
                cout << grid[x][y] << ' ';
            }
        }
        cout << '\n';
    }
}

// ==========================================================
// ТОЧКА ВХОДА В ПРОГРАММУ (Главная функция main)
// ==========================================================
int main() {
    cout << "=== Labirint C++ ===\n";
    cout << "Games count: " << getGamesPlayed() << "\n\n";

    string seed;
    cout << "Seed(r - random): ";
    cin >> seed;

    Labirint lab;
    lab.init(seed);

    char input;
    while (!lab.isFinished()) {
        system("cls");

        std::cout << "controls - WASD\n\n";

        lab.draw();

        cout << "\n";
        cin >> input;

        lab.movePlayer(input);
    }

    cout << "\nSucces\n";
    saveGameSession(seed);

    return 0;
}
