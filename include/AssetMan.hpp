#pragma once

#include <map>
#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine {

class AssetMan {
private:
    std::map<int, std::unique_ptr<sf::Texture>> m_textures;
    std::map<int, std::unique_ptr<sf::Font>> m_fonts;

public:
    AssetMan();
    ~AssetMan();

    void AddTexture();
    void AddFont();
    
    // Node: const before * means const for content of pointer. const after * means const for the address of content which is pointer's value(address)
    // const after function name means we cannot change the fildes in this class in this method(eg. getter)

    // always make the method as const if you don't modify the class
    const sf::Texture &GetTexture() const;
    const sf::Font &GetFont() const;
};
} // namespace Engine
