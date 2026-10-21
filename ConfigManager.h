#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <fstream>
#include <string>
#include "Config.h"

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
        outFile << "Игра #" << totalGames << " | SEED: " << seedUsed << "\n";
        outFile.close();
    }
}

#endif
