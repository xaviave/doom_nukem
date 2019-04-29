/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   misc.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 21:12:24 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 18:25:18 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/wolf.h"

void				debug_display(t_engine *e)
{
	if (!e->mlx->win->menu)
	{
		mlx_string_put(e->mlx->id, e->mlx->win->id, WIDTH - 75, 0, 0x0000FF22, "FPS: ");
		mlx_string_put(e->mlx->id, e->mlx->win->id, WIDTH - 25, 0, 0x0000FF22, ft_itoa(1.0 / e->mlx->frame));
		mlx_string_put(e->mlx->id, e->mlx->win->id, 0, 0, CLR_STR, "Mouse");
		mlx_string_put(e->mlx->id, e->mlx->win->id, 0, 20, CLR_STR, "X: ");
		mlx_string_put(e->mlx->id, e->mlx->win->id, 25, 20, CLR_VAR, ft_itoa(e->mouse->x));
		mlx_string_put(e->mlx->id, e->mlx->win->id, 75, 20, CLR_STR, "Y: ");
		mlx_string_put(e->mlx->id, e->mlx->win->id, 100, 20, CLR_VAR, ft_itoa(e->mouse->y));
		mlx_string_put(e->mlx->id, e->mlx->win->id, 0, HEIGH - 25, CLR_STR, "Layer: ");
		mlx_string_put(e->mlx->id, e->mlx->win->id, 75, HEIGH - 25, CLR_VAR, ft_itoa(cycle_index(&e->sketch->board, e->sketch->marker)));
	}
	return ;
}
