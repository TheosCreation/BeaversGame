#include "Sound.h"

/*
	Creates a Sound Object

	@author Jamuel Bocacao
	@param string: Sound File Path
	@param float: Volume of Sound (Between 0 and 100)
*/
Sound::Sound(string _strSoundPath, float _fVolume)
{
	// Check if Sounded loaded
	if (!m_buffer.loadFromFile(_strSoundPath))
	{
		printf("Could not load Audio File: %s", _strSoundPath.c_str());
	}
	else
	{
		m_sound.setBuffer(m_buffer);
		m_sound.setVolume(_fVolume);
	}
}

/*
	Handles Deleting Sound

	@author Jamuel Bocacao
*/
Sound::~Sound()
{
	Stop();
}

/*
	Plays a Sound at specific location and start time

	@author Jamuel Bocacao
	@param sf::Vector3f: Location of Sound in World (Default is (0,0))
	@param sf::Time: Starting point of sound (Deaffult is 0s)
*/
void Sound::PlaySound(sf::Vector3f _location, sf::Time _offset)
{
	m_sound.setPosition(_location);
	m_sound.play();
	m_sound.setPlayingOffset(_offset);
}

/*
	Sets Volume of Sound

	@author Jamuel Bocacao
	@param float: New Volume of Sound
*/
void Sound::SetVolume(float _fVolume)
{
	m_sound.setVolume(_fVolume);
}

/*
	Pauses the Sound Playing

	@author Jamuel Bocacao
*/
void Sound::Pause()
{
	m_sound.pause();
}

/*
	Stops Sound Playing

	@author Jamuel Bocacao
*/
void Sound::Stop()
{
	m_sound.stop();
}

/*
	Whether Sound is loaded

	@author Jamuel Bocacao
	@return bool: Sound has loaded properly
*/
bool Sound::isValid()
{
	return (m_sound.getBuffer() != NULL);
}
