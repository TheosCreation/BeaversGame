#include "AudioManager.h"

/*
	Gets the Audio Manager's Instance

	@author Jamuel Bocacao
	@return AudioManager&: AudioManager Instance
*/
AudioManager& AudioManager::GetInstance()
{
	return m_instance;
}

/*
	Plays a Sound based on File Path, with optional position and starting time

	@author Jamuel Bocacao
	@param string: Sound File Path
	@param sf::Vector3f: Location to play Sound
	@param sf::Time: Start time of sound
*/
void AudioManager::PlaySound(string _strSoundPath, sf::Vector3f _position, sf::Time _offset)
{
	// Generate a Hash ID based on sound file path
	std::hash<string> hashGenerator;
	size_t soundID = hashGenerator(_strSoundPath);

	// Check if Sound has already been loaded
	if (!m_sounds.contains(soundID))
	{
		// If not load Sound file
		auto sound = make_shared<Sound>(_strSoundPath, float(m_iSoundVolume));
		if (sound->isValid())
		{
			// Store Sound using path as File ID
			m_sounds.emplace(soundID, sound);
			sound->PlaySound(_position, _offset);
			return;
		}
	}
	
	// Play existing sound
	m_sounds.at(soundID)->PlaySound(_position, _offset);
}

/*
	Plays Music based on on File Path

	@author Jamuel Bocacao
	@param string: Music File Path
	@param sf::Time: Start time of Music
*/
void AudioManager::PlayMusic(string _strMusicPath, sf::Time _startTime)
{
	m_music = make_unique<Music>(_strMusicPath, float(m_iMusicVolume));
	m_music->Play(_startTime);
}

/*
	Sets the Volume of all Sound Effects

	@author Jamuel Bocacao
	@param int: Sound Volume (Between 0 and 100)
*/
void AudioManager::SetSoundVolume(int _iVolume)
{
	for (auto sound : m_sounds)
	{
		sound.second->SetVolume(float(_iVolume));
	}
}

/*
	Gets the Volume of all Sound Effects

	@author Jamuel Bocacao
	@return int: Sound Volume
*/
int AudioManager::GetSoundVolume()
{
	return m_iSoundVolume;
}

/*
	Sets the Volume of all Music

	@author Jamuel Bocacao
	@param int: Sound Volume (Between 0 and 100)
*/
void AudioManager::SetMusicVolume(int _iVolume)
{
	m_iMusicVolume = _iVolume;
	m_music->SetVolume(_iVolume);
}

/*
	Gets the Music Volume

	@author Jamuel Bocacao
	@return int: Music Volume
*/
int AudioManager::GetMusicVolume()
{
	return m_iMusicVolume;
}

/*
	Stop all Sounds that are currently playing

	@author Jamuel Bocacao
*/
void AudioManager::StopSounds()
{
	for (auto sound : m_sounds)
	{
		sound.second->Stop();
	}
}

/*
	Stops all Sounds from Playing

	@author Jamuel Bocacao
*/
void AudioManager::StopAll()
{
	StopMusic();
	StopSounds();
}

/*
	Pauses Music

	@author Jamuel Bocacao
*/
void AudioManager::PauseMusic()
{
	m_music->Pause();
}

/*
	Stops Music

	@author Jamuel Bocacao
*/
void AudioManager::StopMusic()
{
	m_music->Stop();
}

/*
	Unloads all Sound

	@author Jamuel Bocacao
*/
void AudioManager::UnloadAll()
{
	m_sounds.clear();
	m_music.reset();
}
