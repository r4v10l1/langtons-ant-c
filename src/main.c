/*
 *	https://github.com/r4v10l1
 *	Langtons ant simulation made in pure C with SDL2.
 *	Based on https://github.com/r4v10l1/LangtonsAnt
 */

#include <stdio.h>
#include "SDL.h"

#include "read_config.h"

#define WINDOW_W 1200		// Window width in pixels
#define WINDOW_H 750		// Window height in pixels

#define FPS 60				// Will wait 1000ms/FPS between frames
#define DELAY 50			// Will set this as delay instead of the fps if this value is not 0 and the space is pressed

#define DEBUG_PRINT 0

int main(int argc, char* argv[]) {
	// Start SDL
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to start: %s\n", SDL_GetError());
		return 1;
	}
	if (DEBUG_PRINT == 1) printf("SLD started!\n");
	
	// Create window
	SDL_Window* sdl_window = SDL_CreateWindow("SDL2 test",  // Window name
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0); 
	if (!sdl_window) {
		printf("Error creating a window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	if (DEBUG_PRINT == 1) printf("Window created!\n");

	// Create renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* sdl_renderer = SDL_CreateRenderer(sdl_window, -1, render_flags);
	if (!sdl_renderer) {
		printf("Error creating a renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(sdl_window);
		SDL_Quit();
		return 1;
	}
	if (DEBUG_PRINT == 1) printf("Renderer created!\n\n");
	
	if (read_config() == 1) {
		printf("Error opening config.cfg\nExiting...\n");
		return 1;
	}

	printf("Press space to start the simulation.\n");

	/* ------------------------------------------------------------------------------- */

	// Main loop
	int running = 1, space_pressed = 0; 

	SDL_Event sdl_event;	// Create an event for the keys and shit
	while (running == 1) {
		// Events
		while (SDL_PollEvent(&sdl_event)) {
			switch (sdl_event.type) {
				case SDL_QUIT:  // Window is closed
					running = 0;
					break;
				case SDL_KEYDOWN:
					// Check the pressed key
					switch (sdl_event.key.keysym.scancode) {
						case SDL_SCANCODE_ESCAPE:
							running = 0;
							if (DEBUG_PRINT == 1) {
								printf("Esc key pressed!\n");
							}
							break;
						case SDL_SCANCODE_SPACE:
							space_pressed = 1;
							break;
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					// Check the released key
					switch (sdl_event.key.keysym.scancode) {
						case SDL_SCANCODE_SPACE:
							space_pressed = 0;
							if (DEBUG_PRINT == 1) {
								printf("Space key released!\n");
							}
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}

		// Clear window
		SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
		SDL_RenderClear(sdl_renderer);

		// Do something every frame the space is pressed
		if (space_pressed) {
			// Do shit
		}
		
		// Send to renderer
		SDL_RenderPresent(sdl_renderer);
		if (space_pressed && DELAY) {
			SDL_Delay(DELAY);
		} else {
			SDL_Delay(1000/FPS);
		}
	}

	// End of the program
	printf("Reached end of the program!\n");
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();

	return 0;
}