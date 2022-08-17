#include "GameOver.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>

GameOver::GameOver(std::shared_ptr<Context>& context) 
    : m_context(context), m_isRetryButtonSelected(true),
    m_isRetryButtonPressed(false), m_isExitButtonSelected(false),
    m_isExitButtonPressed(false)
{
}

GameOver::~GameOver() {
}

void GameOver::Init() {
    // set gameover music
    if (!gameOver_music.openFromFile("assets/musics/GameOver.ogg")) {
        std::cout << "Audio ERROR!" << std::endl;
    }

    // title
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("Game Over!");
    m_gameOverTitle.setCharacterSize(100);
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2,
                          m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2 - 20,
                            m_context->m_window->getSize().y / 2 - 300.f);

    // retry Button
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString("Retry");
    m_retryButton.setCharacterSize(50);
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2,
                           m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2- 20,
                            m_context->m_window->getSize().y / 2 - 25.f);
    

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(50);
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
                           m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2 - 20,
                            m_context->m_window->getSize().y / 2 + 25.f);
}

void GameOver::ProcessInput() {
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            m_context->m_window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            // event.key.code stores the key that was pressed
            switch (event.key.code) {
            case sf::Keyboard::Up: {
                if (!m_isRetryButtonSelected) {
                    m_isRetryButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down: {
                if (!m_isExitButtonSelected) {
                    m_isRetryButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return: {
                m_isRetryButtonPressed = false;
                m_isExitButtonPressed = false;
                if (m_isRetryButtonSelected) {
                    m_isRetryButtonPressed = true;
                } else {
                    m_isExitButtonPressed = true;
                }
                break;
            }
            default:
                break;
            }
        }  
    }
}

void GameOver::Update(sf::Time deltaTime) {
    if (m_isRetryButtonSelected) {
        m_retryButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setFillColor(sf::Color::White);
    } else {
        m_retryButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Yellow);
    }

    if (m_isRetryButtonPressed) {
        // Go to the Play State
        std::cout << "Let's retry!" << std::endl;
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    } else if (m_isExitButtonPressed) {
        m_context->m_window->close();
    }
}

void GameOver::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}

void GameOver::Start() 
{
    gameOver_music.play();
}