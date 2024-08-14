#pragma once
#include <SFML/Audio.hpp>

using std::string;

class Sound
{
public:
	Sound(string _strSoundPath, float _fVolume);
	~Sound();

	void PlaySound(sf::Vector3f _location, sf::Time _offset);
	void SetVolume(float _fVolume);

	void Pause();
	void Stop();

	bool isValid();

private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
};

