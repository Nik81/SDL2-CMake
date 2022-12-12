/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "AudioManager.h"
#include "appDefines.h"

AudioManager*  AudioManager::_instance = 0;//NULL;

//------------------------------------------------------------------------
AudioManager::AudioManager() 
{
	m_ResourcesPath = APP_ASSETS_DIR;
	m_MusicPath = m_ResourcesPath + "/Audio/Music/";
	m_SoundPath = m_ResourcesPath + "/Audio/Clip/";
}
//------------------------------------------------------------------------
AudioManager::~AudioManager() {}

//------------------------------------------------------------------------
AudioManager* AudioManager::GetInstance()
{
	if (_instance == nullptr)
		_instance = new AudioManager();

	return _instance;
}
//------------------------------------------------------------------------
void AudioManager::Release()
{
	CleanSounds();
	CleanMusics();

	_instance = nullptr;
}

/// Sound
//------------------------------------------------------------------------
Mix_Chunk * AudioManager::LoadSound(const char* fileName)
{
	std::string soundFile = m_SoundPath + fileName;

	Mix_Chunk *sound = Mix_LoadWAV(soundFile.c_str());

	if (sound == nullptr)
	{
		//SDL_Log("SoundManager: Failed to load sound. %s", SDL_GetError());
		return NULL;
	}

	return sound;
}
//------------------------------------------------------------------------
void AudioManager::AddSound(std::string id, const char* path)
{
	std::string filePath = m_SoundPath;
	filePath += path;

	sounds.emplace(id, LoadSound(filePath.c_str()));

	//SDL_Log("AssetManager: Add Sound");
}
//------------------------------------------------------------------------
Mix_Chunk * AudioManager::GetSound(std::string id)
{
	return sounds[id];
}
//------------------------------------------------------------------------
void AudioManager::RemSound(std::string id)
{
	Mix_FreeChunk(sounds[id]);
	sounds.erase(id);

	//SDL_Log("AssetManager: Removed Sound");
}
//------------------------------------------------------------------------
void AudioManager::CleanSounds()
{
	int debug_count = 0;

	std::map<std::string, Mix_Chunk*>::iterator it;
	for (it = sounds.begin(); it != sounds.end(); it++)
	{
		debug_count++;
		Mix_FreeChunk(it->second);
	}

	sounds.clear();

	//SDL_Log("AssetManager: ClearSounds : Removed %d sounds", debug_count);
}

/// Music
//------------------------------------------------------------------------
Mix_Music * AudioManager::LoadMusic(const char* fileName)
{
	std::string musicFile = m_MusicPath + fileName;

	Mix_Music *music = Mix_LoadMUS(musicFile.c_str());

	if (music == nullptr)
	{
		//SDL_Log("SoundManager: Failed to load music. %s", SDL_GetError());
		return NULL;
	}

	return music;
}
//------------------------------------------------------------------------
void AudioManager::AddMusic(std::string id, const char* path)
{
	std::string filePath = m_MusicPath;
	filePath += path;

	musics.emplace(id, LoadMusic(filePath.c_str()));

	//SDL_Log("AssetManager: Add Music");
}
//------------------------------------------------------------------------
Mix_Music * AudioManager::GetMusic(std::string id)
{
	return musics[id];
}
//------------------------------------------------------------------------
void AudioManager::RemMusic(std::string id)
{
	Mix_FreeMusic(musics[id]);
	musics.erase(id);

	//SDL_Log("AssetManager: Removed Music");
}

//------------------------------------------------------------------------
void AudioManager::CleanMusics()
{
	int debug_count = 0;

	std::map<std::string, Mix_Music*>::iterator it;
	for (it = musics.begin(); it != musics.end(); it++)
	{
		debug_count++;
		Mix_FreeMusic(it->second);
	}

	musics.clear();

	//SDL_Log("AssetManager: ClearMusics : Removed %d Musics", debug_count);
}


//------------------------------------------------------------------------
void AudioManager::PlaySound(Mix_Chunk *sound, int loop)
{
	Mix_PlayChannel(-1, sound, loop);
}

//------------------------------------------------------------------------
void AudioManager::PlayMusic(Mix_Music *music, int loops)
{
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, loops);	
	}
	//If music is being played
	else
	{
		//If the music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume the music
			ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			PauseMusic();
		}
	}
}
//------------------------------------------------------------------------
void AudioManager::PauseMusic()
{
	Mix_PauseMusic();
}
//------------------------------------------------------------------------
void AudioManager::ResumeMusic()
{
	Mix_ResumeMusic();
}
//------------------------------------------------------------------------
void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}

//------------------------------------------------------------------------
void AudioManager::Print()
{
	printf("--------------------------------\n");
	printf("\AUDIO MANAGER\n");

	printf(" Sounds: %d\n", musics.size());

	// 	std::map<std::string, SDL_Texture*>::iterator it;
	// 	for (it = TextureMap.begin(); it != TextureMap.end(); it++)
	// 	{
	// 		printf(" %s\n", it->first);
	// 		printf(" %s\n", it->second);
	// 	}

	printf(" Musics: %d\n", sounds.size());
}