#include <iostream>

extern "C" {
#include <SDL2/SDL.h>
}

#include "gfx_core.h"
#include "pico_core.h"
#include "pico_data.h"

#include "game.h"

int main(int, char**) {
	GFX_Init(512, 512);
	GFX_CreateBackBuffer(128, 128);
	pico_control::init(128, 128);
	pico_data::load_test_data();

	bool init = false;

	uint32_t ticks = SDL_GetTicks();

	while (true) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		} else {
			using namespace pico_api;

			pixel_t* pixels;
			int pitch;
			GFX_LockBackBuffer(&pixels, &pitch);
			pico_control::set_buffer(pixels, pitch);

			if (!init) {
				pico_init();
				init = true;
			}

			pico_update();
			pico_draw();
			GFX_UnlockBackBuffer();
			GFX_Flip();
		}
	}
	GFX_End();
}
