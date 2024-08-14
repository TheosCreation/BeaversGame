#include "Music.h"

/*
	Creates a Music Object

	@author Jamuel Bocacao
	@param string: Music File Path
	@param float: Volume of Sound (Between 0 and 100)
*/
Music::Music(string _strMusicPath, float _fVolume)
{
	// Check if Music loaded
	if (m_music.openFromFile(_strMusicPath))
	{
		m_music.setVolume(_fVolume);
		m_music.setLoop(true);
	}
	else
	{
		printf("Failed to load Music: \"%s\"", _strMusicPath.c_str());
	}
}

/*
	Handles Deleting
*/
Music::~Music()
{
	m_music.stop();
}

/*
	Sets Volume of Music

	@author Jamuel Bocacao
	@param float: New Volume of Music
*/
void Music::SetVolume(float _fVolume)
{
	m_music.setVolume(_fVolume);
}

/*
	Plays Music

	@author Jamuel Bocacao
	@param sf::Time: Start time of Music
*/
void Music::Play(sf::Time _startTime)
{
	m_music.play();
	m_music.setPlayingOffset(_startTime);
}

/*
	Pauses Music

	@author Jamuel Bocacao
*/
void Music::Pause()
{
	m_music.pause();
}

/*
	Stops Music

	@author Jamuel Bocacao
*/
void Music::Stop()
{
	m_music.stop();
}
