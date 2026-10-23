#include "Labirint.h"
#include "ConfigManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Labirint::Labirint(int w, int h) : width(w), height(h), lastSeed(0) {
    grid.resize(width, vector<char>(height, Config::WALL));
}

void Labirint::clearGrid() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[x][y] = Config::WALL;
        }
    }
}

bool Labirint::isNumber(const string& s) const {
    if (s.size() > 9) {
        return false;
    }
    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

void Labirint::init(const std::string& seedStr) {
    clearGrid();

    unsigned int seedValue;
    if (seedStr == "r" || seedStr == "R") {
        seedValue = time(0);
    } else if (isNumber(seedStr)) {
        seedValue = stoi(seedStr);
    } else {
        seedValue = 0;
        for (char c : seedStr) {
            seedValue += c;
        }
    }
    srand(seedValue);
    lastSeed = seedValue;

    startX = 0;
    startY = rand() % (height - 2) + 1;

    playerX = startX;
    playerY = startY;

    generatePath();

    grid[startX][startY] = Config::START;
    grid[finishX][finishY] = Config::FINISH;
}

void Labirint::generatePath() {
    int curX = startX;
    int curY = startY;

    grid[curX][curY] = Config::PATH;

    while (curX < width - 1) {
        int dir = rand() % 3;

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

unsigned int Labirint::getSeedValue() const {
    return lastSeed;
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
    cout.flush();
}

int main() {
    cout << "=== Labirint C++ ===\n";
    cout << "Games count: " << getGamesPlayed() << "\n\n";

    cout << "Field size:  1 - 10x10,  2 - 15x15,  3 - 20x20\n";
    int choice = readSafeMenuChoice(1, 3);
    int size = (choice == 1) ? 10 : (choice == 2) ? 15 : 20;

    string seed;
    cout << "Seed(r - random): ";
    cin >> seed;

    Labirint lab(size, size);
    lab.init(seed);

    string seedLog = seed;
    if (seed == "r" || seed == "R") {
        seedLog = seed + " (" + to_string(lab.getSeedValue()) + ")";
    }

    char input;
    while (!lab.isFinished()) {
        system("cls");

        cout << "controls - WASD\n\n";

        lab.draw();

        cout << "\n";
        cin >> input;
        if (!cin) break;

        lab.movePlayer(input);
    }

    if (lab.isFinished()) {
        cout << "\nSucces\n";
        saveGameSession(seedLog);
    }

    return 0;
}
