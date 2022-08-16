#include "Snake.hpp"

Snake::Snake() : m_body(std::list<sf::Sprite>(4)) {
    m_head =  --m_body.end();
    m_tail = m_body.begin();
}

Snake::~Snake() {
}

void Snake::Init(const sf::Texture& texture) {
    float x = 32.f;
    for (auto& piece : m_body) {
        piece.setTexture(texture);
        piece.setPosition({x, 32.f});
        x += 32.f;
    }
}

void Snake::Move(const sf::Vector2f& direction) {
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end()) {
        m_tail = m_body.begin();
    }
}

void Snake::isOn(const sf::Sprite& other) const {
    
}

void Snake::Grow(const sf::Vector2f& direction) {

}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto& piece : m_body) {
        target.draw(piece);
    }
}