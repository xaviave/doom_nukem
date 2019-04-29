/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   image.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 20:38:20 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 22:20:12 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/wolf.h"

void				image_destroy(t_image *img)
{
	mlx_destroy_image(img->mlx_id, img->id);
	ft_memdel((void **)&img);
	return ;
}

t_image				*new_image(void *mlx_id, int width, int heigh)
{
	t_image			*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		return (0);
	if (!(img->id = mlx_new_image(mlx_id, width, heigh)))
		return (0);
	img->mlx_id = mlx_id;
	img->width = width;
	img->heigh = heigh;
	img->data = mlx_get_data_addr(img->id, &img->bpp, &img->size_l, &img->endian);
	img->bpp /= 8;
	return (img);
}

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
	
	n = (img->width - 1) + ((img->heigh - 1)*img->width);
	while (n)
			*(int *)(img->data + (n-- * img->bpp)) = color;
	return ;
}