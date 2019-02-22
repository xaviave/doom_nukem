/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures_tools.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:28:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/22 15:35:53 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void textures_init(t_mem *mem)
{
	t_size gun_size;
	t_size crosshair_size;
	t_size monster_size;

	gun_size.width = 402;
	gun_size.lenght = 402;
	crosshair_size.width = 32;
	crosshair_size.lenght = 32;
	monster_size.width = 285;
	monster_size.lenght = 365;

	make_mask(mem, &mem->gun, "backgrounds/gun2.xpm", gun_size);
	make_mask(mem, &mem->crosshair, "backgrounds/crosshair.xpm", crosshair_size);
	make_mask(mem, &mem->monster, "backgrounds/monster.xpm", monster_size);
}

void make_mask(t_mem *mem, t_img *img, char xpm[255], t_size size)
{
	int i[3];

	img->ptr = mlx_xpm_file_to_image(mem->mlx_ptr,
									xpm, &size.width, &size.lenght);
	img->data = mlx_get_data_addr(img->ptr, &i[0], &i[1],
								&i[2]);
}

unsigned int rgb(unsigned char r, unsigned char g, unsigned char b)
{
	if (r > 255)
		r = 255;
	if (r > 255)
		g = 255;
	if (r > 255)
		b = 255;
	return ((r * 65536) + (g * 256) + b);
}

void put_img_to_img(t_mem *mem, t_img *img, t_size size, int x, int y, float zoom)
{
	int i;
	int j;
	int k;
	int color;
	t_coord pos;

	x -= size.width * zoom * 0.5;
	y -= size.lenght * zoom * 0.5;
	i = 0;
	j = 0;
	while (j < size.lenght)
	{
		k = 0;
		while (k < size.width)
		{
			color = rgb(img->data[i + 2], img->data[i + 1], img->data[i]);
			pos.y2 = 0;
			while (pos.y2 < zoom)
			{
				while (pos.x1 < k * zoom)
				{
					if (color != 0x00000000 && pos.x1 > 0 && pos.x1 < W && pos.y1 > 0 && pos.y1 < H)
						ft_put_pixel(mem, pos.x1 + x, pos.y1 + pos.y2 + y, set_color(color));
					pos.x1++;
				}
				pos.x1 -= zoom;
				pos.y2++;
			}
			i += 4;
			pos.x1 = k * zoom;
			k++;
		}
		pos.y1 = j * zoom;
		j++;
	}
}

/*void				texture_in_tab(t_param *param)
{
	int				i;
	int				j;

	j = 0;
	i = 0;
	while (param->wall.data[i])
	{
		param->wall_colors[j] = rgb(param->wall.data[i + 2], param->
wall.data[i + 1], param->wall.data[i]);
		i += 4;
		j++;
	}
}*/