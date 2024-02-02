#include <SDL.h>
#include <stdio.h>
#include <SDL_mixer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "thing.h"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct context
{
	SDL_Renderer *renderer;
	SDL_Rect dest;
	SDL_Rect purpleSquare;
	int r;
	int g;
	int b;
};

void handleEvents(context *ctx, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_LEFT)
		{
			ctx->purpleSquare.x -= 10;
		}
		else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RIGHT)
		{
			ctx->purpleSquare.x += 10;
		}
		else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_UP)
		{
			ctx->purpleSquare.y -= 10;
		}
		else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_DOWN)
		{
			ctx->purpleSquare.y += 10;
		}
	}
}

void mainloop(void *arg)
{
	struct context *ctx = static_cast<context *>(arg);
	SDL_Event e;
	handleEvents(ctx, &e);
	SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 255, 255);
	SDL_RenderClear(ctx->renderer);
	SDL_SetRenderDrawColor(ctx->renderer, ctx->r, ctx->g, ctx->b, 255);
	SDL_RenderFillRect(ctx->renderer, &ctx->purpleSquare);
	SDL_RenderPresent(ctx->renderer);
}

int main(int argc, char *args[])
{
	SDL_Window *window = NULL;
	struct context ctx;

	if (Mix_OpenAudio(44800, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	int flags = MIX_INIT_OGG;
	int initted = Mix_Init(flags);
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	ctx.purpleSquare.x = 320;
	ctx.purpleSquare.y = 240;
	ctx.purpleSquare.w = 32;
	ctx.purpleSquare.h = 32;
	ctx.r = 0;
	ctx.g = 0;
	ctx.b = 255;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &ctx.renderer);
	SDL_SetRenderDrawColor(ctx.renderer, 255, 0, 0, 255);
	Thing *thing = new Thing(34);
	thing->printNumber();
	Mix_Chunk *m_theme = Mix_LoadWAV("audio/theme.wav");
	int canPlay = Mix_PlayChannel(-1, m_theme, 1);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1);
#else
	SDL_Event e;
	bool quit = false;
	while (quit == false)
	{
		handleEvents(&ctx, &e);
		// while (SDL_PollEvent(&e))
		// {
		// 	if (e.type == SDL_QUIT)
		// 	{
		// 		quit = true;
		// 	}
		// 	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
		// 	{
		// 		Mix_Chunk *m_theme = Mix_LoadWAV("audio/theme.wav");
		// 		int canPlay = Mix_PlayChannel(0, m_theme, 1);
		// 		if (canPlay != -1)
		// 		{
		// 			ctx.b = 0;
		// 			ctx.g = 255;
		// 			ctx.r = 0;
		// 		}
		// 		else
		// 		{
		// 			ctx.b = 0;
		// 			ctx.g = 0;
		// 			ctx.r = 255;
		// 		}
		// 		ctx.purpleSquare.x -= 10;
		// 	}
		// 	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
		// 	{
		// 		ctx.purpleSquare.x += 10;
		// 	}
		// 	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
		// 	{
		// 		ctx.purpleSquare.y -= 10;
		// 	}
		// 	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
		// 	{
		// 		ctx.purpleSquare.y += 10;
		// 	}
		// }
		mainloop(&ctx);
	}
#endif
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
