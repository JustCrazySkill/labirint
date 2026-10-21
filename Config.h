#ifndef CONFIG_H
#define CONFIG_H

#include <string>

// Размеры и символы отображения лабиринта
namespace Config {
    const int WIDTH = 10;                     // Ширина сетки
    const int HEIGHT = 10;                    // Высота сетки

    const char WALL = '#';                    // Стена
    const char PATH = ' ';                    // Проход
    const char START = 'S';                   // Старт (слева)
    const char FINISH = 'F';                  // Финиш (справа)
    const char PLAYER = 'P';                  // Игрок

    const std::string STATS_FILE = "stats.txt"; // Имя файла статистики
}

#endif
