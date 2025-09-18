#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include "Button.hpp"

#ifdef _DEBUG
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#else
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-audio.lib")
#endif

#define FAST            0.05f
#define WIDTH           10
#define HEIGHT          20
#define BLOCK_SIZE      36
#define HEADER          40

enum class CategoryButton
{
    Close,
    RollUp
};

class TetrisGame 
{
public:
    TetrisGame();

public:
    void run();

private:
    void init();
    void createButtons();
    void processEvents();
    void update(float deltaTime);
    void render();
    void spawnPiece();
    bool isValidPosition(const std::array<sf::Vector2i, 4>& piece);
    void lockPiece();
    void clearLines();
    void handleInput(sf::Keyboard::Key key);
    void handleKeyRelease(sf::Keyboard::Key key);
    void drawGrid();
    void showMenu();
    void showGameOver();
    void processEventsButtons(const sf::Event& event);
    void renderButtons();
    void draggintWindow(const sf::Event& event);

private:
    const std::vector<std::array<sf::Vector2i, 4>> Figures = {
        // I
        { sf::Vector2i(1,0), sf::Vector2i(1,1), sf::Vector2i(1,2), sf::Vector2i(1,3) },

        // Z
        { sf::Vector2i(0,0), sf::Vector2i(1,0), sf::Vector2i(1,1), sf::Vector2i(2,1) },

        // S
        { sf::Vector2i(1,0), sf::Vector2i(2,0), sf::Vector2i(0,1), sf::Vector2i(1,1) },

        // T
        { sf::Vector2i(1,0), sf::Vector2i(0,1), sf::Vector2i(1,1), sf::Vector2i(2,1) },

        // L
        { sf::Vector2i(0,0), sf::Vector2i(0,1), sf::Vector2i(1,1), sf::Vector2i(2,1) },

        // J
        { sf::Vector2i(2,0), sf::Vector2i(0,1), sf::Vector2i(1,1), sf::Vector2i(2,1) },

        // O
        { sf::Vector2i(1,0), sf::Vector2i(2,0), sf::Vector2i(1,1), sf::Vector2i(2,1) }
    };

    sf::ContextSettings ctx;
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape block;
    std::array<sf::Color, 8> colors = {
        sf::Color(30, 30, 30),       // 0 = фон/пустота (тЄмно-серый)
        sf::Color(48, 213, 200),     // 1 = I Ч м€тный (бирюза)
        sf::Color(255, 100, 100),    // 2 = Z Ч алый
        sf::Color(100, 255, 100),    // 3 = S Ч лаймовый
        sf::Color(255, 230, 100),    // 4 = T Ч жЄлтый песочный
        sf::Color(255, 160, 50),     // 5 = L Ч насыщенный оранж
        sf::Color(80, 160, 255),     // 6 = J Ч лазурный
        sf::Color(180, 100, 255)     // 7 = O Ч фиолетово-розовый
    };
    sf::Clock clock;
    sf::Font font;
    sf::Text scoreLabel, scoreValue, levelLabel, levelValue;

    std::vector<Button> buttons;
    std::array<std::array<int, WIDTH>, HEIGHT> field{};
    std::array<sf::Vector2i, 4> currentPiece;
    std::array<sf::Vector2i, 4> previousPiece;
    int color = 0, nextColor = 1;
    float timer = 0.f;
    float delay = 0.f;
    float speed = 0.5f;
    bool gameOver = false;
    bool isDownPressed = false;
    int score = 0, level = 0;
    std::vector<std::string> options = { "Easy", "Normal", "Hardcore" };
    bool dragging = false;
    sf::Vector2i dragOffset;
};