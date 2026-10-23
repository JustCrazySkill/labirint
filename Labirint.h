#pragma once

#include <vector>
#include <string>
#include "Config.h"

class Labirint {
private:
    int width;
    int height;
    std::vector<std::vector<char>> grid;

    int startX, startY;
    int finishX, finishY;
    int playerX, playerY;

    void clearGrid();
    void generatePath();

public:
    Labirint(int w = Config::WIDTH, int h = Config::HEIGHT);

    void init(const std::string& seedStr);
    void draw() const;
    bool movePlayer(char direction);
    bool isFinished() const;
};

