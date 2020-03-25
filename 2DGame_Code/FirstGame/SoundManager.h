#pragma once
#include <string>
#include "SDL_mixer.h"
#include <map>

class SoundManager
{
private:
	SoundManager() {};
	static SoundManager* instance;
	std::map<std::string, Mix_Music*> musicMap;
	std::map<std::string, Mix_Chunk*> chunkMap;

public:
	static void CreateInstance();
	static void DestroyInstance();
	static SoundManager* GetSingleton();

	bool LoadChunk(std::string sound_id, std::string file_name);
	bool LoadMusic(std::string sound_id, std::string file_name);
	void PlayChunk(std::string sound_id);
	void PlayMusic(std::string sound_id);
	Mix_Music* GetMusic(std::string sound_id) { return musicMap[sound_id]; }
	Mix_Chunk* GetChunk(std::string sound_id) { return chunkMap[sound_id]; }
};

