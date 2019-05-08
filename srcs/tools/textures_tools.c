/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures_tools.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:28:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 00:41:33 by mel-akio    ###    #+. /#+    ###.fr     */
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
	make_mask(mem, &mem->wall, "backgrounds/wood.xpm");
	make_mask(mem, &mem->gun, "backgrounds/gun2.xpm");
	make_mask(mem, &mem->crosshair, "backgrounds/crosshair.xpm");
	make_mask(mem, &mem->monster, "backgrounds/shooting_monster.xpm");
	make_mask(mem, &mem->shooting_monster, "backgrounds/shooting_monster2.xpm");
	make_mask(mem, &mem->skybox, "backgrounds/sky.xpm");
	make_mask(mem, &mem->hud.hp, "backgrounds/hp.xpm");
	make_mask(mem, &mem->hud.ammo, "backgrounds/ammo.xpm");
	make_mask(mem, &mem->ammo_box, "backgrounds/ammobox.xpm");
	make_mask(mem, &mem->hp_box, "backgrounds/hpbox.xpm");
}

void				make_mask(t_mem *mem, t_img *img, char xpm[255])
{
	img->ptr = mlx_xpm_file_to_image(mem->mlx_ptr,
									xpm, &img->w, &img->h);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->sizeline,
								&img->endian);
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
	t_vector coor, float zoom)
{
	int				i;
	int				j;
	int				k;

	ft_bzero(&mem->coord, sizeof(mem->coord));
	coor.mx -= img->w * zoom * 0.5;
	coor.my -= img->h * zoom + mem->camera_y;
	i = 0;
	j = -1;
	while (++j < img->h)
	{
		k = -1;
		while (++k < img->w && zoom < 1.5)
		{
			mem->colorize = rgb(img->data[i + 3], img->data[i + 2],
				img->data[i + 1], img->data[i]);
			mem->coord.y2 = -1;
			draw_objects(mem, coor, zoom, k);
			i += 4;
			mem->coord.x1 = k * zoom;
		}
		mem->coord.y1 = j * zoom;
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
