#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

namespace Engine {

class AssetMan {
private:
    std::map<int, std::unique_ptr<sf::Texture>> m_textures;
    std::map<int, std::unique_ptr<sf::Font>> m_fonts;
    // std::map<int, std::unique_ptr<sf::Music>> m_musics;

public:
    AssetMan();
    ~AssetMan();

    void AddTexture(int id, const std::string& filePath, bool wantRepeated = false);
    void AddFont(int id, const std::string& filePath);
    // void AddMusic(int id, const std::string& filePath);
    
    // Node: const before * means const for content of pointer. const after * means const for the address of content which is pointer's value(address)
    
    // const sf::Texture& means const reference, we cannot change this object.

    // const after function name means we cannot change the fildes in this class in this method(eg. getter)
    // always make the method as const if you don't modify the class
    const sf::Texture &GetTexture(int id) const;
    const sf::Font &GetFont(int id) const;
    // const sf::Music &GetMusic(int id) const;
};
} // namespace Engine
