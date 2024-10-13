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
void Sound::RandomizePitch(float min, float max)
{
	if (min >= max) {
		throw std::invalid_argument("min should be less than max");
	}
	std::random_device rd;  // Obtain a random number from hardware
	std::default_random_engine eng(rd()); // Seed

	// Define the range
	std::uniform_real_distribution<float> distr(min, max);

	m_sound.setPitch(distr(eng));
}

void Sound::LoopSound(sf::Vector3f _location, sf::Time _offset)
{
	if(!m_sound.Playing){ 
		m_sound.setPosition(_location);
		m_sound.setLoop(true); // Enable looping
		m_sound.play();
		m_sound.setPlayingOffset(_offset);
	}
}

// Ensure Stop method stops the looping sound
/*
	Stops Sound Playing

	@author Jamuel Bocacao + Kazuo RDA
*/
void Sound::Stop()
{
	m_sound.stop();
	m_sound.setLoop(false); 
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
