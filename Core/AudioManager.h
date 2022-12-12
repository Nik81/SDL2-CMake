#pragma once

#ifndef __AudioManager_H__
#define __AudioManager_H__

#include <string>
#include <SDL_mixer.h>
#include <map>

//========================================================================
class AudioManager
{
private:

	static AudioManager* _instance;

	AudioManager();
	~AudioManager();

	std::string m_ResourcesPath;
	std::string m_MusicPath;
	std::string m_SoundPath;

public:

	static AudioManager* GetInstance();

	void Release();

	// Sounds
	std::map<std::string, Mix_Chunk*> sounds;

	Mix_Chunk* LoadSound(const char* file);
	void AddSound(std::string id, const char* file);
	void RemSound(std::string id);
	void CleanSounds();	
	Mix_Chunk* GetSound(std::string id);

	void PlaySound(Mix_Chunk *sound, int loop = 0);
	bool IsPlayngSound(int channel = -1) { return Mix_Playing(channel); }

	void SetSoundVolume(int volume, int channel = -1) { Mix_Volume(channel, volume); };
	int GetSoundVolume(int channel = -1) { return Mix_Volume(channel, -1); };

	// Musics
	std::map<std::string, Mix_Music*> musics;

	Mix_Music* LoadMusic(const char* file);
	void AddMusic(std::string id, const char* file);
	void RemMusic(std::string id);
	void CleanMusics();
	Mix_Music* GetMusic(std::string id);
	
	void PlayMusic(Mix_Music *music, int loops = -1);
	void PauseMusic();
	void ResumeMusic();
	void StopMusic();

	bool IsPlayingMusic() { return Mix_PlayingMusic(); }
	bool IsPausedMusic() { return Mix_PausedMusic(); }
		
	void SetMusicVolume(int volume)	{ Mix_VolumeMusic(volume); };
	int GetMusicVolume() { return Mix_VolumeMusic(-1); };
	
	int GetMusicPosition(double position) { return Mix_SetMusicPosition(position); };

	//Mix_SetPanning(int channel, Uint8 left, Uint8 right)

	void Print();
};
#endif