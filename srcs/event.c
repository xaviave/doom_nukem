/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cmerel <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:15:31 by cmerel       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 14:28:47 by cmerel      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void	keyboard()
{
	SDL_Event	ev;

	SDL_WaitEvent(&ev);
	if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.scancode == SDL_SCANCODE_A)
			printf("gauche\n");
		if (ev.key.keysym.scancode == SDL_SCANCODE_W)
			printf("avance\n");
		if (ev.key.keysym.scancode == SDL_SCANCODE_D)
			printf("droite\n");
		if (ev.key.keysym.scancode == SDL_SCANCODE_S)
			printf("recule\n");
	}
}
