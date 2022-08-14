#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
Game::Game() : m_context(std::make_shared<Context>()) {
    m_context->m_window->create(sf::VideoMode(800, 800), "Snake Game!", sf::Style::Close);
    // Todo: add first state to m_states

}

Game::~Game() {

}

void Game::Run() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();
        // std::cout << timeSinceLastFrame.asSeconds() << std::endl;
        while (timeSinceLastFrame > TIME_PER_FRAME) {
            timeSinceLastFrame -= TIME_PER_FRAME;

            sf::Event event;
            while (m_context->m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_context->m_window->close();
            }

            m_context->m_window->clear();
            m_context->m_window->draw(shape);
            m_context->m_window->display();
        }
    }
}