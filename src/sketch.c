/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sketch.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 18:14:50 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 18:22:26 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/wolf.h"

t_sketch			*new_sketch(void *mlx_id)
{
	t_sketch		*sketch;

	if (!(sketch = (t_sketch*)ft_memalloc(sizeof(t_sketch))))
		return (0);
	sketch->board = new_cycle(new_grid(new_image(mlx_id, WIDTH, HEIGH)));
	sketch->marker = &sketch->board;
	sketch->size = 1;
	return (sketch);
}

void				sketch_destroy(t_sketch *sketch)
{
	cycle_delall(&sketch->board);
	*sketch->marker = 0;
	ft_memdel((void**)&sketch);
	return ;
}