/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_free_renderer.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/08 15:06:44 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/08 17:27:32 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	free_render(t_render *r)
{
	if (r->s)
		SDL_FreeSurface(r->s);
	if (r->win)
		SDL_DestroyWindow(r->win);
	if (r->rend)
		SDL_DestroyRenderer(r->rend);
	SDL_Quit();
}

void	render_error(int error, t_render *r, t_level *level)
{
	if (error == 10)
		ft_printf("Error 10 : SDL initialisation didn't work\n");
	else if (error == 11)
		ft_printf("Error 11 : Window couldn't be created\n");
	else if (error == 12)
		ft_printf("Error 12 : Renderer couldn't be created\n");
	free_render(r);
	free_level(level);
	exit(EXIT_FAILURE);
}

void	init_render(t_render *r, t_level *level)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
		render_error(10, r, level);
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &r->win, &r->rend))
		render_error(11, r, level);
	SDL_SetWindowTitle(r->win, "Doom Nukem");
	if (!(r->s = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0)))
		render_error(12, r, level);
}
