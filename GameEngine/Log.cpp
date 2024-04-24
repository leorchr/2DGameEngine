#include "Log.h"
#include <SDL_error.h>
#include <SDL_log.h>
#include <string>

void Log::info(const string& message) {
	SDL_Log(message.c_str());
}

void Log::error(LogCategory category, const string& message) {
	SDL_LogError(static_cast<int>(category), "%s I SDL: %s", message.c_str(), SDL_GetError());
}