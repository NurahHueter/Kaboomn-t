#pragma once
#include "pch.h"
#include "AssetManager.h"
namespace mmt_gd
{

	void AssetManager::LoadTexture(std::string name, std::string filename) {

		std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

		if (texture->loadFromFile(filename)) {
			this->m_Textures[name] = texture;
		}
		else {
			std::cout << "Fehler beim Laden der Textur " << name << " aus der Datei " << filename << std::endl;
		}
	}

	void AssetManager::LoadSoundBuffer(std::string name, std::string filename) {

		std::shared_ptr<sf::SoundBuffer> sound = std::make_shared<sf::SoundBuffer>();

		if (sound->loadFromFile(filename)) {
			this->m_SoundBuffer[name] = sound;
		}
		else {
			std::cout << "Fehler beim Laden des Sounds " << name << " aus der Datei " << filename << std::endl;
		}
	}

	void AssetManager::LoadMusic(std::string name, std::string filename) {
		std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();

		if (music->openFromFile(filename)) {
			this->m_Music[name] = music;
		}
		else {
			std::cout << "Fehler beim Laden der Musik " << name << " aus der Datei " << filename << std::endl;
		}
	}

	void AssetManager::LoadFont(std::string name, std::string filename) {
		std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();

		if (font->loadFromFile(filename)) {
			this->m_Font[name] = font;
		}
		else {
			std::cout << "Fehler beim Laden der Font " << name << " aus der Datei " << filename << std::endl;
		}

	}

	void AssetManager::UnloadTexture(std::string name) {
		auto it = m_Textures.find(name);
		if (it != m_Textures.end()) {
			m_Textures.erase(it);
			std::cout << "unload Texture " << std::endl;
		}
	}

	void AssetManager::UnloadSoundBuffer(std::string name) {
		auto it = m_SoundBuffer.find(name);
		if (it != m_SoundBuffer.end()) {
			m_SoundBuffer.erase(it);
		}
	}

	void AssetManager::UnloadMusic(std::string name) {
		auto it = m_Music.find(name);
		if (it != m_Music.end()) {
			m_Music.erase(it);
		}
	}

	void AssetManager::UnloadFont(std::string name) {
		auto it = m_Font.find(name);
		if (it != m_Font.end()) {
			m_Font.erase(it);
		}
	}
}