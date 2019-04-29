/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   grid.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 17:04:49 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 22:40:17 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/wolf.h"

t_grid			*new_grid(t_image *img)
{
	t_grid		*grid;

	if (!(grid = (t_grid*)ft_memalloc(sizeof(t_grid))))
		return (0);
	grid->img = img;
	grid->scale = G_SCALE;
	grid->cursor_coef = 1.0;
	return (grid);
}

void			grid_destroy(t_grid *grid)
{
	image_destroy(grid->img);
	ft_memdel((void**)&grid);
	return ;
}

void			grid_draw(t_grid *grid, int color)
{
	image_fill(grid->img, CLR_A);
	image_pixel_put(grid->img, 300, 300, color);
	return ;
}