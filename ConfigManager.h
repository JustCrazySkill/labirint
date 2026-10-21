#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Config.h"

// Функции для работы со статистикой и историей сидов

// Чтение количества сыгранных игр из файла
inline int getGamesPlayed() {
    std::ifstream file(Config::STATS_FILE);
    int games = 0;
    if (file.is_open()) {
        file >> games; // Считываем первое число из файла
        file.close();
    }
    return games;
}

// Сохранение нового сида и обновление счетчика игр
inline void saveGameSession(const std::string& seedUsed) {
    int totalGames = getGamesPlayed() + 1;

    // Перезаписываем файл: первое число — общее количество игр, далее — история
    // Сначала считаем существующую историю, чтобы сохранить её
    std::ifstream inFile(Config::STATS_FILE);
    std::string history = "";
    if (inFile.is_open()) {
        int dummy;
        inFile >> dummy; // Пропускаем старый счетчик
        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                history += line + "\n";
            }
        }
        inFile.close();
    }

    // Записываем обновленные данные в файл
    std::ofstream outFile(Config::STATS_FILE);
    if (outFile.is_open()) {
        outFile << totalGames << "\n";
        outFile << history;
        outFile << "Game N" << totalGames << " | SEED: " << seedUsed << "\n";
        outFile.close();
    }
}

#endif
