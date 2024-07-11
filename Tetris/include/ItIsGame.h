#ifndef ITISGAME_H
#define ITISGAME_H

#include "../include/Figures.h"
#include "../include/Platform.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <conio.h>
#include <atomic>

class ItIsGame {
public:
    static ItIsGame& GetGame() {
        static ItIsGame Game;
        return Game;
    }

    void run() {
        GameProcess();
    }

    ItIsGame(const ItIsGame&) = delete;
    ItIsGame& operator=(const ItIsGame&) = delete;

private:
    void GameProcess();
    void LogicGame();
    void SpawnRandomFigure();
    void MovementFigure();
    void ClearFigure();
    void RenderFigure();
    bool IsCollision(int newX, int newY);
    void PlaceFigure();
    void ClearLines();
    bool CheckGameOver();

    ItIsGame() : f_x(platform.width / 2 - 1), f_y(0), stopFlag(false) {};

    Figures& figures = Figures::GetFigures();
    Platform& platform = Platform::GetPlatform();

    std::random_device rd;
    bool newFigure = true;
    std::vector<std::string> figure;
    int tempF = 0;
    bool tempI = false;
    int f_x, f_y;
    std::atomic<bool> stopFlag;
};

#endif