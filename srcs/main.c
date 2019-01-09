/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 10:14:48 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 16:52:41 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	init_parse(t_parse *parse)
{
	parse->vertex = NULL;
	parse->sector = NULL;
	parse->player.x = -1;
	parse->player.y = -1;
}

static void	init_level(t_level *level)
{
	level->vertex = NULL;
	level->sector = NULL;
	level->next = NULL;
}

static void	init_sdl(t_sdl *sdl, t_level *level)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
		render_error(10, sdl, level);
	if ((sdl->win = SDL_CreateWindow("map du futur", 100, 100, W, H,
		SDL_WINDOW_SHOWN)) == NULL)
		render_error(11, sdl, level);
	if ((sdl->rend = SDL_CreateRenderer(sdl->win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
		render_error(12, sdl, level);
	//sdl->tex = SDL_CreateTexture(sdl->rend, SDL_PIXELFORMAT_RGBA8888,
//		SDL_TEXTUREACCESS_STREAMING, 1280, 720);
	sdl->modif = 1;
	sdl->quit = 1;
	sdl->color.r = 0;
	sdl->color.g = 0;
	sdl->color.b = 0;
	sdl->color.a = 0;
    SDL_SetRenderDrawColor(sdl->rend, sdl->color.r, sdl->color.g, sdl->color.b,
        sdl->color.a);
}

/*
** check coord of the player if his coord aren't in the map
*/

int			main(int ac, char **av)
{
	t_parse		parse;
	t_level		level;
	t_sdl		sdl;

	init_parse(&parse);
	parse_map(ac, av, &parse);
	init_level(&level);
	parse_to_level(&parse, &level);
	init_sdl(&sdl, &level);
	render_map(&sdl, &level);
	free_level(&level);
	free_sdl(&sdl);
	return (0);
}
