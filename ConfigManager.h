#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Config.h"


inline int readSafeMenuChoice(int minVal, int maxVal) {
    int choice = 0;
    while (true) {
        std::cout << "Choose action (" << minVal << "-" << maxVal << "): ";
        if (std::cin >> choice && choice >= minVal && choice <= maxVal) {
            std::cin.ignore(10000, '\n');
            return choice;
        }
        std::cout << "[Error] Enter a valid number!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

inline int getGamesPlayed() {
    std::ifstream file(Config::STATS_FILE);
    int games = 0;
    if (file.is_open()) {
        file >> games;
        file.close();
    }
    return games;
}

inline void saveGameSession(const std::string& seedUsed) {
    int totalGames = getGamesPlayed() + 1;

    std::ifstream inFile(Config::STATS_FILE);
    std::string history = "";
    if (inFile.is_open()) {
        int dummy;
        inFile >> dummy;
        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                history += line + "\n";
            }
        }
        inFile.close();
    }

    std::ofstream outFile(Config::STATS_FILE);
    if (outFile.is_open()) {
        outFile << totalGames << "\n";
        outFile << history;
        outFile << "\u0413\u0440\u0430 #" << totalGames << " | SEED: " << seedUsed << "\n";
        outFile.close();
    }
}
