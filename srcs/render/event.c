/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sdl->event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:15:31 by cmerel       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/19 11:43:16 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

/*
static void	final_aff(t_sdl *sdl, SDL_Texture *n)
{
	if (SDL_LockSurface(sdl->tex))
		return ;//error
	sdl->tex->pixels = n->pixels;
	SDL_UnlockSurface(sdl->tex);
	if (!(sdl->tex = SDL_CreateTextureFromSurface(sdl->rend, sdl->tex)))
		return ;//error
	SDL_RenderCopy(sdl->rend, sdl->tex, NULL, NULL);
	SDL_RenderPresent(sdl->rend);
	SDL_DestroyTexture(sdl->tex);
}
*/

void			aff_map(t_sdl *sdl)
{
	SDL_RenderClear(sdl->rend);
	int i, j = -1;

	while (++i < H)
	{
		j = -1;
		while (++j < W)
		{
			
		}
	}
	sdl->color.r = 0;
	sdl->color.g = 70;
	sdl->color.b = 100;
	sdl->color.a = 0;
	SDL_SetRenderDrawColor(sdl->rend, sdl->color.r, sdl->color.g, sdl->color.b,
        sdl->color.a);

	sdl->coord.x1 = 0;
	sdl->coord.y1 = 0;
	sdl->coord.x2 = 80;
	sdl->coord.y2 = 0;
	draw_line(sdl);

	sdl->coord.x1 = 80;
	sdl->coord.y1 = 0;
	sdl->coord.x2 = 80;
	sdl->coord.y2 = 80;
	draw_line(sdl);

	sdl->coord.x1 = 80;
	sdl->coord.y1 = 80;
	sdl->coord.x2 = 0;
	sdl->coord.y2 = 80;
	draw_line(sdl);

	sdl->coord.x1 = 0;
	sdl->coord.y1 = 80;
	sdl->coord.x2 = 0;
	sdl->coord.y2 = 0;
	draw_line(sdl);
        
    SDL_RenderPresent(sdl->rend);

	//SDL_Texture	*n;

	//while (sector)
	//algo interprete les secteurs / vertex
	//aff_sector

	//while (vertex)
	//aff_vertex

	//final_aff(sdl, n);
}

void			keyboard(t_sdl *sdl)
{
	SDL_WaitEvent(&sdl->ev);
	if (sdl->ev.key.keysym.sym == SDLK_f)
		sdl->modif = 0;
	if (sdl->ev.key.keysym.sym == SDLK_g)
		sdl->modif = 1;
	if (sdl->ev.type == SDL_QUIT || sdl->ev.key.keysym.sym == SDLK_ESCAPE)
	{
		sdl->modif = 0;
		sdl->quit = 0;
	}
	if (sdl->modif == 1)
		aff_map(sdl);
}
