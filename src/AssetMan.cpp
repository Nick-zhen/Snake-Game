#include "AssetMan.hpp"

Engine::AssetMan::AssetMan() {

}

Engine::AssetMan::~AssetMan() {

}

void Engine::AssetMan::AddTexture(int id, const std::string& filePath, bool wantRepeated) {
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(filePath)) {
        texture->setRepeated(wantRepeated);
        m_textures[id] = std::move(texture);
    }
}

void Engine::AssetMan::AddFont(int id, const std::string& filePath) {
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath)) {
        m_fonts[id] = std::move(font);
    }
}

// void  Engine::AssetMan::AddMusic(int id, const std::string& filePath) {
//     auto music = std::make_unique<sf::Music>();

//     if (music->openFromFile(filePath)) {
//         m_musics[id] = std::move(music);
//     }
// }

// unique_ptr.get() return a pointer to the managed object which is reference, so we need to dereference it to get the object.
const sf::Texture& Engine::AssetMan::GetTexture(int id) const {
    return *(m_textures.at(id).get());
}

const sf::Font& Engine::AssetMan::GetFont(int id) const {
    return *(m_fonts.at(id).get());
}

// const sf::Music& Engine::AssetMan::GetMusic(int id) const {
//     return *(m_musics.at(id).get());
//  }