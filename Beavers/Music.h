#pragma once
#include <SFML/Audio.hpp>

using std::string;

class Music
{
public:
	Music(string _strMusicPath, float _fVolume);
	~Music();

	void SetVolume(float _fVolume);
	
	void Play(sf::Time _startTime);
	void Pause();
	void Stop();

private:
	sf::Music m_music;
};

