#include "../include/ItIsGame.h"

void ItIsGame::GameProcess() {
    std::thread movementThread(&ItIsGame::MovementFigure, this);
    movementThread.detach();

    while (!stopFlag) {
        if (newFigure) {
            SpawnRandomFigure();
            if (CheckGameOver()) {
                stopFlag = true;
                break;
            }
            newFigure = false;
        }

        LogicGame();

        system("cls");
        platform.PrintPlatform();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Game Over!" << std::endl;
}

void ItIsGame::SpawnRandomFigure() {
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, figures.figures.size() - 1);
    int random = dis(gen);
    tempF = random;
    tempI = 0;
    figure = figures.figures.at(random).at(0);
    f_x = platform.width / 2 - figure[0].size() / 2;
    f_y = 0;
}

void ItIsGame::LogicGame() {
    ClearFigure();
    if (!IsCollision(f_x, f_y + 1)) {
        f_y++;
    }
    else {
        PlaceFigure();
        ClearLines();
        newFigure = true;
    }
    RenderFigure();
}

void ItIsGame::ClearFigure() {
    for (int y = 0; y < figure.size(); y++) {
        for (int x = 0; x < figure[y].size(); x++) {
            if (figure[y][x] == '#' && f_y + y < platform.height && f_x + x < platform.width) {
                platform.platform[f_y + y][f_x + x] = ' ';
            }
        }
    }
}

void ItIsGame::RenderFigure() {
    for (int y = 0; y < figure.size(); y++) {
        for (int x = 0; x < figure[y].size(); x++) {
            if (figure[y][x] == '#' && f_y + y < platform.height && f_x + x < platform.width) {
                platform.platform[f_y + y][f_x + x] = '#';
            }
        }
    }
}

void ItIsGame::MovementFigure() {
    while (!stopFlag) {
        if (_kbhit()) {
            char key = _getch();
            ClearFigure();
            int newX = f_x;
            int newY = f_y;
            switch (key) {
            case 'w':
                tempI = !tempI;
                figure = figures.figures.at(tempF).at(tempI);
                break;
            case 's':
                newY++;
                break;
            case 'a':
                newX--;
                break;
            case 'd':
                newX++;
                break;
            default:
                break;
            }

            if (!IsCollision(newX, newY)) {
                f_x = newX;
                f_y = newY;
            }
            RenderFigure();
        }
    }
}

bool ItIsGame::IsCollision(int newX, int newY) {
    for (int y = 0; y < figure.size(); y++) {
        for (int x = 0; x < figure[y].size(); x++) {
            if (figure[y][x] == '#') {
                if (newX + x < 0 || newX + x >= platform.width || newY + y >= platform.height || platform.platform[newY + y][newX + x] != ' ') {
                    return true;
                }
            }
        }
    }
    return false;
}

void ItIsGame::PlaceFigure() {
    for (int y = 0; y < figure.size(); y++) {
        for (int x = 0; x < figure[y].size(); x++) {
            if (figure[y][x] == '#') {
                platform.platform[f_y + y][f_x + x] = '#';
            }
        }
    }
}

void ItIsGame::ClearLines() {
    for (int y = 0; y < platform.height; y++) {
        bool fullLine = true;
        for (int x = 0; x < platform.width; x++) {
            if (platform.platform[y][x] == ' ') {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int line = y; line > 0; line--) {
                platform.platform[line] = platform.platform[line - 1];
            }
            platform.platform[0] = std::string(platform.width, ' ');
        }
    }
}

bool ItIsGame::CheckGameOver() {
    for (int x = 0; x < platform.width; x++) {
        if (platform.platform[0][x] == '#') {
            return true;
        }
    }
    return false;
}