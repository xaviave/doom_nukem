/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   img.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:28:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/19 15:26:27 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		ft_put_pixel(t_mem *mem, int x, int y, t_color color)
{
	int		bpp;

	bpp = mem->img.bpp / 8;
	if ((x > 0 && x < mem->win.width) && (y > 0 && y < mem->win.height))
	{
		mem->img.data[(x * bpp) + (mem->img.sizeline * y)] = color.b;
		mem->img.data[(x * bpp) + (mem->img.sizeline * y) + 1] = color.g;
		mem->img.data[(x * bpp) + (mem->img.sizeline * y) + 2] = color.r;
		mem->img.data[(x * bpp) + (mem->img.sizeline * y) + 3] = color.a;
	}
}

void		ft_create_img(t_mem *mem)
{
	mem->img.ptr = mlx_new_image(mem->mlx_ptr, W, H);
	mem->img.data = mlx_get_data_addr(mem->img.ptr, &mem->img.bpp,
		&mem->img.sizeline, &mem->img.endian);
}

void				make_mask(t_mem *mem, t_img *img, char xpm[255],
t_size size)
{
	int i[3];

	img->ptr = mlx_xpm_file_to_image(mem->mlx_ptr,
xpm, &size.width, &size.lenght);
	img->data = mlx_get_data_addr(img->ptr, &i[0], &i[1],
	&i[2]);
}