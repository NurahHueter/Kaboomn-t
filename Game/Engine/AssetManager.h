#pragma once
#include <map>

namespace mmt_gd
{
	struct AssetManager
	{
		static
			AssetManager&
			instance()
		{
			static AssetManager s;
			return s;
		} // instance

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator = (const AssetManager&) = delete;

		std::map<std::string, std::shared_ptr<sf::Texture>> m_Textures{};							//Maps (dictionarys) erstellen
		std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_SoundBuffer{};
		std::map<std::string, std::shared_ptr<sf::Music>> m_Music{};
		std::map<std::string, std::shared_ptr<sf::Font>> m_Font{};
		void LoadTexture(std::string name, std::string filename);
		void LoadSoundBuffer(std::string name, std::string filename);
		void LoadMusic(std::string name, std::string filename);
		void LoadFont(std::string name, std::string filename);

		void UnloadTexture(std::string name);
		void UnloadSoundBuffer(std::string name);
		void UnloadMusic(std::string name);
		void UnloadFont(std::string name);

	private:
		AssetManager() {}
		~AssetManager() {}
	};
}