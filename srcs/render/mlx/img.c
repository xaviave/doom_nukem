/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   img.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:28:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 19:23:44 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void		ft_put_pixel(t_mem *mem, int x, int y, t_color color)
{
	int		bpp;

	bpp = mem->img.bpp >> 3;
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
