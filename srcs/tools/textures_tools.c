/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures_tools.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:28:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 10:20:25 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void				textures_init(t_mem *mem)
{
	mem->gun.w = 402;
	mem->gun.h = 402;
	mem->crosshair.w = 32;
	mem->crosshair.h = 32;
	mem->monster.w = 285;
	mem->monster.h = 365;
	mem->skybox.w = 1280;
	mem->skybox.h = 800;
	make_mask(mem, &mem->gun, "backgrounds/gun2.xpm");
	make_mask(mem, &mem->crosshair, "backgrounds/crosshair.xpm");
	make_mask(mem, &mem->monster, "backgrounds/shooting_monster.xpm");
	make_mask(mem, &mem->shooting_monster, "backgrounds/shooting_monster2.xpm");
	make_mask(mem, &mem->skybox, "backgrounds/sky.xpm");
	make_mask(mem, &mem->hud.hp, "backgrounds/hp.xpm");
	make_mask(mem, &mem->hud.ammo, "backgrounds/ammo.xpm");
}

void				make_mask(t_mem *mem, t_img *img, char xpm[255])
{
	int				i[3];

	img->ptr = mlx_xpm_file_to_image(mem->mlx_ptr,
									xpm, &img->w, &img->h);
	img->data = mlx_get_data_addr(img->ptr, &i[0], &i[1],
								&i[2]);
}

unsigned int		rgb(unsigned char o, unsigned char r,
	unsigned char g, unsigned char b)
{
	if (r > 255)
		r = 255;
	if (r > 255)
		g = 255;
	if (r > 255)
		b = 255;
	if (o > 255)
		o = 255;
	return (((unsigned int)o * 16777216) + ((unsigned int)r * 65536) +
		((unsigned int)g * 256) + (unsigned int)b);
}

void				put_img_to_img(t_mem *mem, t_img *img,
	int x, int y, float zoom)
{
	int				i;
	int				j;
	int				k;
	unsigned int	color;
	t_coord			pos;

	x -= img->w * zoom * 0.5;
	y -= img->h * zoom + mem->camera_y;
	i = 0;
	j = -1;
	while (++j < img->h)
	{
		k = -1;
		while (++k < img->w)
		{
			color = rgb(img->data[i + 3], img->data[i + 2],
				img->data[i + 1], img->data[i]);
			pos.y2 = 0;
			while (pos.y2 < zoom)
			{
				while (pos.x1 < k * zoom)
				{
					if (color < 4278190080 && pos.x1 + x > 0 &&
						pos.x1 + x < W && pos.y1 + pos.y2 + y > 0 &&
						pos.y1 + pos.y2 + y < H)
						ft_put_pixel(mem, pos.x1 + x,
							pos.y1 + pos.y2 + y, set_color(color));
					pos.x1++;
				}
				pos.x1 -= zoom;
				pos.y2++;
			}
			i += 4;
			pos.x1 = k * zoom;
		}
		pos.y1 = j * zoom;
	}
}

void				skybox(t_mem *mem, t_img *img)
{
	int				i;
	int				j;
	int				k;
	unsigned int	color;

	i = 0;
	j = -1;
	while (++j < img->h)
	{
		k = -1;
		while (++k < img->w)
		{
			color = rgb(img->data[i + 3], img->data[i + 2], img->data[i + 1],
			img->data[i]);
			ft_put_pixel(mem, k, j, set_color(color));
			i += 4;
		}
	}
}
