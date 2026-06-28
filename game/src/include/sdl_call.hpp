#pragma once

#include <log.hpp>

#include <SDL3/SDL.h>

#define SDL_CALL(expr)                             \
    do {                                           \
        if (!(expr)) {                             \
            LOGE("SDL Error: {}", SDL_GetError()); \
        }                                          \
    } while (0)
