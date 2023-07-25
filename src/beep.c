#include <stdio.h>

#include <SDL2/SDL.h>

int beep(char * choice) {
  const char * filename;
  if (strcmp(choice, "high") == 0) {
    filename = "../sounds/beep.wav";
  } else {
    filename = "../sounds/beep-low.wav";
  }
  SDL_Init(SDL_INIT_AUDIO);

  // Initialize SDL audio subsystem
  if (SDL_AudioInit(NULL) != 0) {
    printf("Failed to initialize SDL audio: %s\n", SDL_GetError());
    return 1;
  }

  SDL_AudioSpec spec;
  Uint8 * audioData;
  Uint32 audioLength;

  // Load the audio file
  if (SDL_LoadWAV(filename, & spec, & audioData, & audioLength) == NULL) {
    printf("Failed to load audio file: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Open the audio device
  SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, & spec, NULL, 0);
  if (deviceId == 0) {
    printf("Failed to open audio device: %s\n", SDL_GetError());
    SDL_FreeWAV(audioData);
    SDL_Quit();
    return 1;
  }

  // Play the audio
  SDL_QueueAudio(deviceId, audioData, audioLength);
  SDL_PauseAudioDevice(deviceId, 0);

  usleep(500000);
  // Clean up
  SDL_CloseAudioDevice(deviceId);
  SDL_FreeWAV(audioData);
  SDL_Quit();

  return 0;
}
