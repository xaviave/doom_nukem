/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   framework.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 20:37:34 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 04:39:52 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/wolf.h"

void				window_destroy(t_window *win)
{
	image_destroy(win->bg);
	ft_memdel((void **)&win);
	return ;
}

t_window			*new_window(void *mlx_id, int width, int heigh, char *title)
{
	t_window		*win;

	if (!(win = (t_window *)ft_memalloc(sizeof(t_window))))
		return (0);
	if (!(win->id = mlx_new_window(mlx_id, width, heigh, title)))
		return (0);
	if (!(win->bg = new_image(mlx_id, width, heigh)))
		return (0);
	win->width = width;
	win->heigh = heigh;
	win->title = title;
	return (win);
}

void				framework_destroy(t_framework *framework)
{
	mlx_destroy_window(framework->id, framework->win->id);
	window_destroy(framework->win);
	ft_memdel((void **)&framework);
	return ;
}

t_framework			*new_framework(void)
{
	t_framework		*mlx;

	if (!(mlx = (t_framework *)ft_memalloc(sizeof(t_framework))))
		return (0);
	if (!(mlx->id = mlx_init()))
		return (0);
	if (!(mlx->win = new_window(mlx->id, WIDTH, HEIGH, "SKETCH")))
		return (0);
	return (mlx);
}
