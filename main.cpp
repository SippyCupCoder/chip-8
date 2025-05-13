#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

#include "chip8.hpp"

#define WIDTH 640
#define HEIGHT 320

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./CHIP8.exe \"PATH\\TO\\FILENAME\"" << std::endl;
        return 1;
    }
    chip8 CHIP8 = chip8(argv[1]);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    SDL_Window *window = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;
    bool running = true;
    while (running) {
        const Uint64 start = SDL_GetPerformanceCounter();

        if (SDL_PollEvent(&windowEvent)) {
            switch (windowEvent.type) {
                case SDL_QUIT:
                    running = false;
                    continue;
                    break;
                case SDL_KEYDOWN:
                    switch (windowEvent.key.keysym.sym) {
                        case SDLK_1: CHIP8.keypad[0x1] = true; break;
                        case SDLK_2: CHIP8.keypad[0x2] = true; break;
                        case SDLK_3: CHIP8.keypad[0x3] = true; break;
                        case SDLK_4: CHIP8.keypad[0xC] = true; break;

                        case SDLK_q: CHIP8.keypad[0x4] = true; break;
                        case SDLK_w: CHIP8.keypad[0x5] = true; break;
                        case SDLK_e: CHIP8.keypad[0x6] = true; break;
                        case SDLK_r: CHIP8.keypad[0xD] = true; break;

                        case SDLK_a: CHIP8.keypad[0x7] = true; break;
                        case SDLK_s: CHIP8.keypad[0x8] = true; break;
                        case SDLK_d: CHIP8.keypad[0x9] = true; break;
                        case SDLK_f: CHIP8.keypad[0xE] = true; break;

                        case SDLK_z: CHIP8.keypad[0xA] = true; break;
                        case SDLK_x: CHIP8.keypad[0x0] = true; break;
                        case SDLK_c: CHIP8.keypad[0xB] = true; break;
                        case SDLK_v: CHIP8.keypad[0xF] = true; break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (windowEvent.key.keysym.sym) {
                        case SDLK_1: CHIP8.keypad[0x1] = false; break;
                        case SDLK_2: CHIP8.keypad[0x2] = false; break;
                        case SDLK_3: CHIP8.keypad[0x3] = false; break;
                        case SDLK_4: CHIP8.keypad[0xC] = false; break;

                        case SDLK_q: CHIP8.keypad[0x4] = false; break;
                        case SDLK_w: CHIP8.keypad[0x5] = false; break;
                        case SDLK_e: CHIP8.keypad[0x6] = false; break;
                        case SDLK_r: CHIP8.keypad[0xD] = false; break;

                        case SDLK_a: CHIP8.keypad[0x7] = false; break;
                        case SDLK_s: CHIP8.keypad[0x8] = false; break;
                        case SDLK_d: CHIP8.keypad[0x9] = false; break;
                        case SDLK_f: CHIP8.keypad[0xE] = false; break;

                        case SDLK_z: CHIP8.keypad[0xA] = false; break;
                        case SDLK_x: CHIP8.keypad[0x0] = false; break;
                        case SDLK_c: CHIP8.keypad[0xB] = false; break;
                        case SDLK_v: CHIP8.keypad[0xF] = false; break;
                    }
                    break;
            }
        }

        CHIP8.run_cycle();

        SDL_RenderClear(renderer);
        SDL_Rect square = {.x = 0, .y = 0, .w = 10, .h = 10};
        for (uint8_t i = 0; i < 32; ++i) {
            for (uint8_t j = 0; j < 64; ++j) {
                square.x = j * 10;
                square.y = i * 10;
                if (CHIP8.display[i][j]) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
                }   
                SDL_RenderFillRect(renderer, &square);

                // Draw pixel outline
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
                SDL_RenderDrawRect(renderer, &square);
            }
        }
        SDL_RenderPresent(renderer);
        
        // Attempt to cap at 60 FPS
        const Uint64 end = SDL_GetPerformanceCounter();
        const double elapsedMS = (end - start) / SDL_GetPerformanceFrequency() * 1000;
        SDL_Delay(std::max(floor(16.666f - elapsedMS), 0.0));
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}