/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 10:14:48 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 14:46:54 by cmerel      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

int			main(int ac, char **av)
{
	t_level			level;
	SDL_Window		*window = NULL;
	SDL_Renderer    *renderer = NULL;
	SDL_Color       color = {255, 255, 40, 255};


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	window = SDL_CreateWindow("test", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL)
		return (1);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		return (1);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);
	parse_map(ac, av, &level);
	keyboard();
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	if (window != NULL)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
