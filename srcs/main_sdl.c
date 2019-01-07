/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_sdl.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 10:14:48 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/20 18:39:13 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

int			init_sdl(t_sdl *sdl)
{
	sdl->win = SDL_CreateWindow("test", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
	if (sdl->win == NULL)
		return (0);
	sdl->rend = SDL_CreateRenderer(sdl->win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (sdl->rend == NULL)
		return (0);
	sdl->tex_back = SDL_CreateTexture(sdl->rend, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, 1280, 720);
	sdl->tex_obj = SDL_CreateTexture(sdl->rend, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, 1280, 720);
	sdl->background.r = 0;
	sdl->background.g = 53;
	sdl->background.b = 142;
	sdl->background.a = 255;
	sdl->obj.r = 228;
	sdl->obj.g = 0;
	sdl->obj.b = 43;
	sdl->obj.a = 255;
	sdl->coord.x = 640;
	sdl->coord.y = 360;
	sdl->coord.x1 = 1000;
	sdl->coord.y1 = 600;
	sdl->quit = 0;
	sdl->x = 0;
	sdl->y = 0;
	sdl->modif = 0;
	sdl->radius = 10;
	ft_bzero(&sdl->position, 1);
	return (1);
}

int			main()
{
	t_sdl	sdl;

	if (SDL_Init(SDL_INIT_VIDEO) < 0 || !init_sdl(&sdl))
		return (0);
	while (!sdl.quit)
	{
		keyboard(&sdl);
	}
	if (sdl.tex_obj != NULL)
		SDL_DestroyTexture(sdl.tex_obj);
	if (sdl.tex_back != NULL)
		SDL_DestroyTexture(sdl.tex_back);
	if (sdl.rend != NULL)
		SDL_DestroyRenderer(sdl.rend);
	if (sdl.win != NULL)
		SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
