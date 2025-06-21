#include "../include/Tetris.hpp"


TetrisGame::TetrisGame()
{
    init();
}

void TetrisGame::init()
{
    ctx.antialiasingLevel = 8;
    window.create(sf::VideoMode(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE + HEADER), "Tetris", sf::Style::None, ctx);

    createButtons();

    font.loadFromFile("Graphics\\Fonts\\Roboto.ttf");

    backgroundTexture.loadFromFile("Graphics\\Texture\\Background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(sf::Vector2f(0.f, 0.f));

    scoreLabel.setString("Score: ");
    scoreLabel.setFont(font);
    scoreLabel.setCharacterSize(18);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(12, 9);

    scoreValue.setString(std::to_string(score));
    scoreValue.setFont(font);
    scoreValue.setCharacterSize(18);
    scoreValue.setFillColor(sf::Color::Yellow);
    scoreValue.setPosition(scoreLabel.getPosition().x + scoreLabel.getLocalBounds().width, 9);

    levelLabel.setString("Level: ");
    levelLabel.setFont(font);
    levelLabel.setCharacterSize(18);
    levelLabel.setFillColor(sf::Color::White);
    levelLabel.setPosition(131, 9);

    levelValue.setString(options[level]);
    levelValue.setFont(font);
    levelValue.setCharacterSize(18);
    levelValue.setFillColor(sf::Color::Yellow);
    levelValue.setPosition(levelLabel.getPosition().x + levelLabel.getLocalBounds().width, 9);

    block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    block.setOutlineThickness(0);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawnPiece();
}

void TetrisGame::createButtons()
{
    buttons.emplace_back(
        static_cast<int>(CategoryButton::Close),
        sf::Vector2f(322.f, 3.f),
        "Graphics\\Buttons\\Close\\Close1.png",
        "Graphics\\Buttons\\Close\\Close2.png",
        "Graphics\\Buttons\\Close\\Close3.png",
        L"",
        font
    );

    /*buttons.emplace_back(
        static_cast<int>(CategoryButton::RollUp),
        sf::Vector2f(277.f, 3.f),
        "Graphics\\Buttons\\RollUp\\RollUp1.png",
        "Graphics\\Buttons\\RollUp\\RollUp2.png",
        "Graphics\\Buttons\\RollUp\\RollUp3.png",
        L"",
        font
    );*/
}

void TetrisGame::run()
{
    showMenu();

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        timer += deltaTime;
        processEvents();
        if (!gameOver) {
            update(deltaTime);
        }
        render();
    }
}

void TetrisGame::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        draggintWindow(event);
        processEventsButtons(event);

        if (event.type == sf::Event::KeyPressed) {
            handleInput(event.key.code);
        }

        if (event.type == sf::Event::KeyReleased) {
            handleKeyRelease(event.key.code);
        }
    }
}

void TetrisGame::update(float)
{
    if (timer > delay) {
        previousPiece = currentPiece;
        for (auto& p : currentPiece) p.y++;
        if (!isValidPosition(currentPiece)) {
            currentPiece = previousPiece;
            lockPiece();
            spawnPiece();
            if (!isValidPosition(currentPiece)) {
                gameOver = true;
                showGameOver();
            }
        }
        timer = 0;
    }
    clearLines();

    if (isDownPressed) {
        delay = FAST;
    }
    else {
        delay = speed;
    }
}

void TetrisGame::render()
{
    window.clear(colors[0]);
    window.draw(backgroundSprite);

    renderButtons();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int color = field[y][x];
            if (color == 0) continue;

            block.setFillColor(colors[color]);
            block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE + HEADER);
            window.draw(block);
        }
    }

    for (auto& p : currentPiece) {
        block.setFillColor(colors[color]);
        block.setPosition(p.x * BLOCK_SIZE, p.y * BLOCK_SIZE + HEADER);
        window.draw(block);
    }

    drawGrid();

    scoreValue.setString(std::to_string(score));
    levelValue.setString(options[level]);

    window.draw(scoreLabel);
    window.draw(scoreValue);
    window.draw(levelLabel);
    window.draw(levelValue);

    window.display();
}

void TetrisGame::spawnPiece()
{
    int n = std::rand() % Figures.size();
    currentPiece = Figures[n];
    color = nextColor;
    nextColor++;
    if (nextColor > 7) {
        nextColor = 1;
    }
    delay = speed;
}

bool TetrisGame::isValidPosition(const std::array<sf::Vector2i, 4>& piece) 
{
    for (const auto& p : piece) {
        if (p.x < 0 || p.x >= WIDTH || p.y >= HEIGHT) {
            return false;
        }
        if (p.y >= 0 && field[p.y][p.x]) {
            return false;
        }
    }
    return true;
}

void TetrisGame::lockPiece() 
{
    for (const auto& p : currentPiece) {
        if (p.y >= 0) {
            field[p.y][p.x] = color;
        }
    }
}

void TetrisGame::clearLines()
{
    int linesCleared = 0;

    for (int y = HEIGHT - 1; y >= 0; y--) {
        int count = 0;
        for (int x = 0; x < WIDTH; x++) {
            if (field[y][x]) count++;
        }

        if (count == WIDTH) {
            for (int row = y; row > 0; row--) {
                field[row] = field[row - 1];
            }
            field[0].fill(0);
            y++;
            linesCleared++;
        }
    }

    switch (linesCleared) {
        case 1: score += 100; break;
        case 2: score += 300; break;
        case 3: score += 500; break;
        case 4: score += 800; break;
    }
}

void TetrisGame::handleInput(sf::Keyboard::Key key)
{
    previousPiece = currentPiece;

    if (key == sf::Keyboard::Left || key == sf::Keyboard::A) {
        for (auto& p : currentPiece) {
            p.x--;
        }
    }
    else if (key == sf::Keyboard::Right || key == sf::Keyboard::D) {
        for (auto& p : currentPiece) {
            p.x++;
        }
    }
    else if (key == sf::Keyboard::Down || key == sf::Keyboard::S) {
        isDownPressed = true;
    }
    else if (key == sf::Keyboard::Up || key == sf::Keyboard::W) {
        sf::Vector2i center = currentPiece[1];
        for (auto& p : currentPiece) {
            int x = p.y - center.y;
            int y = p.x - center.x;
            p.x = center.x - x;
            p.y = center.y + y;
        }
    }
    else if (key == sf::Keyboard::Escape) {
        showMenu();
    }

    if (!isValidPosition(currentPiece)) {
        currentPiece = previousPiece;
    }
}

void TetrisGame::handleKeyRelease(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Down || key == sf::Keyboard::S) {
        isDownPressed = false;
    }
}

void TetrisGame::drawGrid()
{
    sf::VertexArray lines(sf::Lines);

    for (int x = 0; x <= WIDTH; x++) {
        float px = x * BLOCK_SIZE;
        lines.append(sf::Vertex(sf::Vector2f(px, HEADER), sf::Color(50, 50, 50)));
        lines.append(sf::Vertex(sf::Vector2f(px, HEIGHT * BLOCK_SIZE + HEADER), sf::Color(50, 50, 50)));
    }

    for (int y = 0; y <= HEIGHT; y++) {
        float py = y * BLOCK_SIZE + HEADER;
        lines.append(sf::Vertex(sf::Vector2f(0, py), sf::Color(50, 50, 50)));
        lines.append(sf::Vertex(sf::Vector2f(WIDTH * BLOCK_SIZE, py), sf::Color(50, 50, 50)));
    }

    window.draw(lines);
}

void TetrisGame::showMenu()
{
    int selected = 0;

    std::vector<sf::Text> texts;
    for (int i = 0; i < options.size(); ++i) {
        sf::Text text(options[i], font, 24);
        text.setPosition(117, 265 + i * 40);
        texts.push_back(text);
    }

    sf::Text titleTetris("Tetris", font, 48);
    titleTetris.setPosition(117, 130);
    titleTetris.setFillColor(sf::Color::White);

    sf::Text title("Choose the difficulty", font, 24);
    title.setPosition(62, 212);
    title.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            draggintWindow(event);
            processEventsButtons(event);

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return;
                }
                else  if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    selected = (selected + options.size() - 1) % options.size();
                }
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    selected = (selected + 1) % options.size();
                }
                else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return) {
                    switch (selected) {
                        case 0: speed = 0.5f; break;
                        case 1: speed = 0.3f; break;
                        case 2: speed = 0.1f; break;
                    }
                    delay = speed;
                    level = selected;
                    return;
                }
            }
        }

        window.clear(colors[0]);
        window.draw(backgroundSprite);
        drawGrid();

        renderButtons();
        window.draw(titleTetris);
        window.draw(title);

        for (int i = 0; i < texts.size(); ++i) {
            if (i == selected) {
                texts[i].setFillColor(sf::Color::Yellow);
                texts[i].setStyle(sf::Text::Bold);
            }
            else {
                texts[i].setFillColor(sf::Color(180, 180, 180));
                texts[i].setStyle(sf::Text::Regular);
            }
            window.draw(texts[i]);
        }

        window.display();
    }
}

void TetrisGame::showGameOver()
{
    sf::Text titleTetris("Game Over", font, 48);
    titleTetris.setPosition(52, 130);
    titleTetris.setFillColor(sf::Color::Blue);

    sf::Text titleScore("Score: " + std::to_string(score), font, 24);
    titleScore.setPosition(62, 212);
    titleScore.setFillColor(sf::Color::White);
    
    sf::Text titleLevel("Level: " + options[level], font, 24);
    titleLevel.setPosition(62, 265);
    titleLevel.setFillColor(sf::Color::White);

    std::string totalScoreText = "Total score: " + std::to_string(score * (level + 1));
    sf::Text totalScore(totalScoreText, font, 24);
    totalScore.setPosition(62, 318);
    totalScore.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            draggintWindow(event);
            processEventsButtons(event);

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return;
                }
            }
        }

        window.clear(colors[0]);
        window.draw(backgroundSprite);
        drawGrid();

        renderButtons();
        window.draw(titleTetris);
        window.draw(titleScore);
        window.draw(titleLevel);
        window.draw(totalScore);

        window.display();
    }
}

void TetrisGame::processEventsButtons(const sf::Event& event)
{
    for (auto& button : buttons) {
        button.handleEvent(event, window);
        if (button.clicking()) {
            if (button.getCategory() == static_cast<int>(CategoryButton::Close)) {
                window.close();
            }
            /*else if (button.getCategory() == static_cast<int>(CategoryButton::RollUp)) {
                ShowWindow(window.getSystemHandle(), SW_MINIMIZE);
            }*/
        }
    }
}

void TetrisGame::renderButtons()
{
    for (auto& button : buttons) {
        button.render(window);
    }
}

void TetrisGame::draggintWindow(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (event.mouseButton.y < HEADER) {
            dragging = true;
            dragOffset = sf::Mouse::getPosition() - window.getPosition();
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        dragging = false;
    }

    if (dragging) {
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        window.setPosition(mousePos - dragOffset);
    }
}