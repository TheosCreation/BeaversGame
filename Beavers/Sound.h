#pragma once

#include <SFML/Audio.hpp>
#include <random>
using std::string;

class Sound
{
public:
	Sound(string _strSoundPath, float _fVolume);
	~Sound();

	void PlaySound(sf::Vector3f _location, sf::Time _offset);
	void LoopSound(sf::Vector3f _location, sf::Time _offset);
	void SetVolume(float _fVolume);
	void RandomizePitch(float min = 0, float max = 2);
	void Pause();
	void Stop();
	bool IsPlaying();

	bool isValid();

private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
};

