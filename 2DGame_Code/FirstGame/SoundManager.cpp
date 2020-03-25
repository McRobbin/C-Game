#include "SoundManager.h"
#include "SDL_mixer.h"
#include <iostream>

SoundManager* SoundManager::instance = 0;

void SoundManager::CreateInstance() {
	if (instance != 0) return;
	instance = new SoundManager();
}

void SoundManager::DestroyInstance() {
	if (instance == 0) return;

	Mix_HaltMusic();

	std::map<std::string, Mix_Chunk*>::iterator chunk_iter = instance->chunkMap.begin();
	while (chunk_iter != instance->chunkMap.end())
	{
		Mix_FreeChunk(chunk_iter->second);
		chunk_iter++;
	}

	std::map<std::string, Mix_Music*>::iterator music_iter = instance->musicMap.begin();
	while (music_iter != instance->musicMap.end())
	{
		Mix_FreeMusic(music_iter->second);
		music_iter++;
	}

	delete instance;
	instance = 0;
}
SoundManager* SoundManager::GetSingleton() {
	return instance;
}

bool SoundManager::LoadChunk(std::string sound_id, std::string file_name) {
	Mix_Chunk* temp_chunk = Mix_LoadWAV(file_name.c_str());
	if (temp_chunk == 0)
	{
		std::cout << file_name + "LoadChunkFailed" << std::endl;
		return false;
	}

	// everything went ok, add the texture to our list
	if (temp_chunk != 0)
	{
		chunkMap[sound_id] = temp_chunk;
		return true;
	}

	// reaching here means something went wrong
	return false;
}
bool SoundManager::LoadMusic(std::string sound_id, std::string file_name) {
	Mix_Music* temp_music = Mix_LoadMUS(file_name.c_str());
	if (temp_music == 0)
	{
		std::cout << file_name + "LoadMusicFailed" << std::endl;
		return false;
	}

	// everything went ok, add the texture to our list
	if (temp_music != 0)
	{
		musicMap[sound_id] = temp_music;
		return true;
	}

	// reaching here means something went wrong
	return false;
}
void SoundManager::PlayChunk(std::string sound_id) {
	Mix_PlayChannel(-1, chunkMap[sound_id], 0);
}
void SoundManager::PlayMusic(std::string sound_id) {
	Mix_PlayMusic(musicMap[sound_id], 0);
}