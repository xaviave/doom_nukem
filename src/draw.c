/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 17:33:22 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 10:59:42 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

void				image_clear(t_image *img)
{
	ft_bzero(img->data, img->width * img->heigh * img->bpp);
	return ;
}

void				image_pixel_put(t_image *img, int x, int y, int color)
{
	*(int *)(img->data + ((x + y * img->width) * img->bpp)) = color;
	return ;
}

void				image_fill(t_image *img, int color)
{
	int				n;

	n = (img->width - 1) + ((img->heigh - 1) * img->width);
	while (n)
		*(int *)(img->data + (n-- * img->bpp)) = color;
	return ;
}

void				image_square(t_image *img, t_vertex *v, int color)
{
	int				heigh;
	int				width;

	heigh = 0;
	while (heigh < HEIGH)
	{
		width = 0;
		while (width < O_SKETCH)
			image_pixel_put(img, v->x + width++, v->y + heigh, color);
		heigh++;
	}
	return ;
}
