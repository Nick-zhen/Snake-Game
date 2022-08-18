#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>
#include <iostream>

GamePlay::GamePlay(std::shared_ptr<Context>& context) 
    : m_context(context), 
    m_snakeDirection({32.f, 0}), 
    m_elapsedTime(sf::Time::Zero),
    m_score(0)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay() 
{
}

void GamePlay::Init() 
{
    m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
    m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png");
    m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png", true);
    m_context->m_assets->AddTexture(SNAKE, "assets/textures/snake.png");
    // m_context->m_assets->AddMusic(PlayGameMusic, "assets/musics/PalyGame.ogg");
    // m_context->m_assets->AddMusic(GameOverMusic, "assets/musics/PalyGame.ogg");

    // set backgroud music
    if (!backgroud_music.openFromFile("assets/musics/PlayGame.ogg")) {
        std::cout << "Audio ERROR!" << std::endl;
    }

    // set grass textuere
    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    // set wall texture
    for (auto& wall: m_walls) {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }
    m_walls[0].setTextureRect({0, 0, int(m_context->m_window->getSize().x),32});
    m_walls[1].setTextureRect({0, 0, int(m_context->m_window->getSize().x),32});
    m_walls[1].setPosition(0, int(m_context->m_window->getSize().y) - 32);

    m_walls[2].setTextureRect({0, 0, 32,int(m_context->m_window->getSize().y)});
    m_walls[3].setTextureRect({0, 0, 32,int(m_context->m_window->getSize().y)});
    m_walls[3].setPosition(int(m_context->m_window->getSize().x) - 32, 0);

    // set food
    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setOrigin(m_food.getLocalBounds().width / 2,
                     m_food.getLocalBounds().height / 2);
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

    // set snake    
    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));

    // set score title
    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score: " + std::to_string(m_score));
}

void GamePlay::ProcessInput() 
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->m_window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code) {
            case sf::Keyboard::Up:
                newDirection = {0.f, -32.f};
                break;
            case sf::Keyboard::Down:
                newDirection = {0.f, 32.f};
                break;
            case sf::Keyboard::Left:
                newDirection = {-32.f, 0.f};
                break;
            case sf::Keyboard::Right:
                newDirection = {32.f, 0.f};
                break;
            case sf::Keyboard::Space:
                // Pause
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                break;
            default:
                break;
            }
            if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) || 
                std::abs(m_snakeDirection.y) != std::abs(newDirection.y)) {
                    m_snakeDirection = newDirection;
                }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime) 
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime.asSeconds() > 0.1) {

        for (auto& wall: m_walls) {
            if (m_snake.isOn(wall)) {
                // Go to Game over
                backgroud_music.stop();

                m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
                break;
            }
        }

        if (m_snake.isOn(m_food)) {
            m_snake.Grow(m_snakeDirection);
            
            int x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 32, 600);
            int y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 32, 700);
            m_food.setPosition(x, y);

            m_score++;
            m_scoreText.setString("Score: " + std::to_string(m_score));

        } else {
            m_snake.Move(m_snakeDirection);
        }

        m_elapsedTime = sf::Time::Zero;
    }
}

void GamePlay::Draw() 
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);
    for (auto& wall: m_walls) {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);

    m_context->m_window->display();
}

void GamePlay::Pause() 
{
    backgroud_music.pause();
}

void GamePlay::Start() 
{
    backgroud_music.play();
}