#pragma once
#include "Sound.h"
#include "Music.h"
#include "Utils.h"

class AudioManager
{
public:
	static AudioManager& GetInstance();

	void PlaySound(string _strSoundPath, sf::Vector3f _position = sf::Vector3f(), sf::Time _offset = sf::seconds(0), float pitchMin = 1.0f, float pitchMax = 1.0f);
	void LoopSound(string _strSoundPath, sf::Vector3f _position = sf::Vector3f(), sf::Time _offset = sf::seconds(0));
	void PlayMusic(string _strMusicPath, sf::Time _startTime = sf::seconds(0));

	void SetSoundVolume(int _iVolume);
	int GetSoundVolume();

	void SetMusicVolume(int _iVolume);
	int GetMusicVolume();

	void StopSounds();
	void StopAll();

	void PauseMusic();
	void StopMusic();

	void UnloadAll();

private:
	AudioManager() = default;
	~AudioManager() = default;

	AudioManager(const AudioManager& _copy) = delete;
	AudioManager& operator = (const AudioManager& _copy) = delete;

private:
	static AudioManager m_instance;
	map<size_t, shared_ptr<Sound>> m_sounds;

	unique_ptr<Music> m_music;

	int m_iSoundVolume = 50;
	int m_iMusicVolume = 50;
};

inline AudioManager AudioManager::m_instance;
