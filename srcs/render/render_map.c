/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 01:42:14 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			render_calc(t_render *coor, t_vector *vec, t_mem *mem, int sect)
{
	intersect(*vec, &vec->ix1, &vec->iz1);
	intersect_down(*vec, &vec->ix2, &vec->iz2);
	*vec = calc_vec(*vec);
	coor->p1.x1 = -vec->tx1 * 800 / vec->tz1 + (W >> 1);
	coor->p1.x2 = -vec->tx2 * 800 / vec->tz2 + (W >> 1);
	coor->p2.x1 = coor->p1.x1;
	coor->p2.x2 = coor->p1.x2;
	coor->step.x1 = coor->p1.x1;
	coor->step.x2 = coor->p1.x2;
	coor->top.x1 = coor->p1.x1;
	coor->top.x2 = coor->p1.x2;
	coor->p1.y1 = H * (mem->level->player.z - mem->level->sector[sect].h_ceil)
	/ vec->tz1 + (H >> 1);
	coor->p1.y2 = H * (mem->level->player.z - mem->level->sector[sect].h_ceil)
	/ vec->tz2 + (H >> 1);
	coor->p2.y1 = H * (mem->level->player.z - mem->level->sector[sect].h_floor)
	/ vec->tz1 + (H >> 1);
	coor->p2.y2 = H * (mem->level->player.z - mem->level->sector[sect].h_floor)
	/ vec->tz2 + (H >> 1);
}

void			calc_step(t_mem *mem, t_render *coor, t_vector vec, int sect)
{
	if (mem->level->sector[mem->neighbour].h_floor
	>= mem->level->sector[sect].h_floor && mem->neighbour > 0)
	{
		coor->p2.y1 = H * (mem->level->player.z -
		mem->level->sector[sect].h_floor) / vec.tz1 + (H >> 1) - fabs(H *
		((mem->level->player.z - mem->level->sector[mem->neighbour].h_floor))
		/ vec.tz1 + (H >> 1) - coor->p2.y1);
		coor->p2.y2 = H * (mem->level->player.z -
mem->level->sector[sect].h_floor)
	/ vec.tz2 + (H >> 1) - fabs(H * ((mem->level->player.z -
mem->level->sector[mem->neighbour].h_floor)) / vec.tz2 + (H >> 1)
	- coor->p2.y2);
	}
	coor->step.y1 = coor->p2.y1 + 1;
	coor->step.y2 = coor->p2.y2 + 1;
}

void			calc_top(t_mem *mem, t_render *coor, t_vector vec, int sect)
{
	if (mem->level->sector[mem->neighbour].h_ceil <=
mem->level->sector[sect].h_ceil && mem->neighbour > 0)
	{
		coor->p1.y1 = H * mem->level->player.z - mem->level->sector[sect].h_ceil
	/ vec.tz1 + (H >> 1) + fabs(H * ((mem->level->player.z -
mem->level->sector[mem->neighbour].h_ceil)) / vec.tz1 + (H >> 1) - coor->p1.y1);
		coor->p1.y2 = H * mem->level->player.z - mem->level->sector[sect].h_ceil
	/ vec.tz2 + (H >> 1) + fabs(H * ((mem->level->player.z -
mem->level->sector[mem->neighbour].h_ceil)) / vec.tz2 + (H >> 1) - coor->p1.y2);
	}
	coor->top.y1 = coor->p1.y1;
	coor->top.y2 = coor->p1.y2;
}

void			render(t_mem *mem, int sect)
{
	int			j;
	t_render	coor;
	t_vector	vec;

	ft_bzero(&coor, sizeof(coor));
	j = -1;
	while (++j < mem->level->sector[sect].nb_linedef)
	{
		mem->neighbour = 0;
		vec = calc_wall(mem, vec, sect, j);
		if (vec.tz1 > 0 || vec.tz2 > 0)
		{
			render_calc(&coor, &vec, mem, sect);
			calc_step(mem, &coor, vec, sect);
			calc_top(mem, &coor, vec, sect);
			change_color(&mem->color, mem->level->c[mem->level->linedef
[send_l_id(mem, mem->level->sector[sect].linedef[j])].side.text[0]]);
		}
		mem->p1 = coor.p1;
		mem->p2 = coor.p2;
		mem->step = coor.step;
		mem->top = coor.top;
		paint_linedef(coor, sect, mem);
		further_sector(mem, sect);
	}
}

void			refresh_screen(t_mem *mem)
{
	int			i;
	int			j;

	j = -1;
	bzero(mem->fill_screen, (sizeof(char) * W));
	ft_bzero(mem->img.data, W * H * 4);
	i = -1;
	while (++i < mem->level->nb_sector && j == -1)
		j = pre_render(mem, send_s_id(mem, mem->level->n_sector[i]), i);
	skybox(mem, &mem->skybox);
	while (i > -1)
	{
		render(mem, send_s_id(mem, mem->level->n_sector[i]));
		render_sprites(mem, send_s_id(mem, mem->level->n_sector[i--]));
	}
	if (mem->level->player.shoot > 0)
		shoot(mem, mem->level->player.shoot);
	process(mem);
	set_hud(mem);
	if (mem->end)
		end_screen(mem);
}
