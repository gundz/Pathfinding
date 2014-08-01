#include <easy_sdl.h>

#include <SDL.h>

#include <stdio.h>

void					test(t_esdl *esdl)
{
	static SDL_Rect		rect = {0, 0, 200, 200};
	static SDL_Texture 	*square = NULL;
	SDL_Surface			*surf;

	if (square == NULL)
	{
		surf = SDL_CreateRGBSurface(0, 200, 200, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
		draw_square(surf, rect, 0xFFFFFFFF);
		square = SDL_CreateTextureFromSurface(esdl->en.ren, surf);
	}
	if (rect.x >= RX)
		rect.x = 0;
	if (rect.y >= RY)
		rect.y = 0;
	rect.x++;
	rect.y++;
	SDL_RenderClear(esdl->en.ren);
	SDL_RenderCopy(esdl->en.ren, square, NULL, &rect);
	SDL_RenderPresent(esdl->en.ren);
}

int					main(int argc, char **argv)
{
	t_esdl			esdl;

	if (init_sdl(&esdl, "chibre", RX, RY) == -1)
		return (-1);
	while (!esdl.en.in.key[SDL_SCANCODE_ESCAPE])
	{
		update_events(&esdl.en.in);
		fps_counter(&esdl);
		test(&esdl);
	}
	(void)argc;
	(void)argv;
	return (0);
}
