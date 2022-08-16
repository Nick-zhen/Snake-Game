#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<Context>& context) 
    : m_context(context), 
    m_snakeDirection({32.f, 0}), 
    m_elapsedTime(sf::Time::Zero)
{
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
}

void GamePlay::ProcessInput() 
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->m_window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Up:
                m_snakeDirection = {0.f, -32.f};
                break;
            case sf::Keyboard::Down:
                m_snakeDirection = {0.f, 32.f};
                break;
            case sf::Keyboard::Left:
                m_snakeDirection = {-32.f, 0.f};
                break;
            case sf::Keyboard::Right:
                m_snakeDirection = {32.f, 0.f};
                break;
            default:
                break;
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime) 
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime.asSeconds() > 0.1) {
        m_snake.Move(m_snakeDirection);
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

    m_context->m_window->display();
}

void GamePlay::Pause() 
{

}

void GamePlay::Start() 
{
    
}