/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: mem->z19/01/10 14:14:48 by mel-akio     #+#   ##    ##    #+#       */
/*   Updated: mem->z19/01/10 15:58:17 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int mouse_move_hook(int x, int y, t_mem *mem)
{
	if (x || y || mem)
		return (0);
	return (0);
}

int mouse_click_hook(int k, int x, int y, t_mem *mem)
{
	if (k || x || y || mem)
		return (0);
	return (0);
}

int add_key(int k, t_mem *mem)
{
	mem->level->player.keyspressed |= mem->level->player.keys_shortcuts[k];
	return (0);
}

int remove_key(int k, t_mem *mem)
{
	mem->level->player.keyspressed &= ~mem->level->player.keys_shortcuts[k];
	return (0);
}

static int cross_close(t_mem *mem)
{
	if (mem)
		;
	exit(1);
	return (1);
}

int send_vx(t_level *level, int id)
{
	int i;

	i = -1;
	while (++i < level->nb_vertex)
	{
		if (level->vertex[i].id == id)
			return (level->vertex[i].x);
	}
	return (0);
}

int send_vy(t_level *level, int id)
{
	int i;

	i = -1;
	while (++i < level->nb_vertex)
	{
		if (level->vertex[i].id == id)
			return (level->vertex[i].y);
	}
	return (0);
}

int send_l_vx(t_level *level, int id, int vertex)
{
	if (vertex == 1)
		return (send_vx(level, level->linedef[id].id_v1));
	else
		return (send_vx(level, level->linedef[id].id_v2));
}

int send_l_vy(t_level *level, int id, int vertex)
{
	if (vertex == 1)
		return (send_vy(level, level->linedef[id].id_v1));
	else
		return (send_vy(level, level->linedef[id].id_v2));
}

void draw_minimap(t_mem *mem)
{
	int i;
	int j;
	int tx1;
	int tx2;
	int ty1;
	int ty2;
	int tz1;
	int tz2;

	i = -1;
	mlx_clear_window(mem->mlx_ptr, mem->win.win_ptr);

	while (++i < mem->level->nb_sector)
	{
		j = -1;
		while (++j < mem->level->sector[i].nb_linedef)
		{
			
			mem->coord.x1 = MARGE + send_l_vx(mem->level, mem->level->sector[i].linedef[j], 1) * mem->z;
			mem->coord.y1 = MARGE + send_l_vy(mem->level, mem->level->sector[i].linedef[j], 1) * mem->z;
			mem->coord.x2 = MARGE + send_l_vx(mem->level, mem->level->sector[i].linedef[j], 2) * mem->z;
			mem->coord.y2 = MARGE + send_l_vy(mem->level, mem->level->sector[i].linedef[j], 2) * mem->z;
			tx1 = mem->coord.x2 - mem->coord.x1;
			tx2 = mem->coord.x2 - mem->coord.x2;
			ty1 = mem->coord.x2 - mem->coord.y1;
			ty2 = mem->coord.x2 - mem->coord.y2;
			tz1 = tx1 * cos(mem->level->player.angle) + ty1 * sin(mem->level->player.angle);
			tz2 = tx2 * cos(mem->level->player.angle) + ty2 * sin(mem->level->player.angle);
			tx1 = tx1 * sin(mem->level->player.angle) + ty1 * cos(mem->level->player.angle);
			tx2 = tx2 * sin(mem->level->player.angle) + ty2 * cos(mem->level->player.angle);




		//	ft_printf("Depart :x %d | y %d\n", send_l_vx(mem->level, mem->level->sector[i].linedef[j], 1), send_l_vy(mem->level, mem->level->sector[i].linedef[j], 1));
		//	ft_printf("Arriver : x %d | y %d\n", send_l_vx(mem->level, mem->level->sector[i].linedef[j], 2), send_l_vy(mem->level, mem->level->sector[i].linedef[j], 2));
		//	ft_printf("------------------------------\n");
			draw_circle(mem);
			draw_line(mem);
			draw_circle(mem);
		}
		ft_printf(mem->level->map[i]);
	}
//	ft_printf("______________________________________________________________\n");
	draw_camera(mem);
	mem->coord.x2 = ((3 * mem->z * (cos(mem->level->player.angle)) + mem->coord.x1));
	mem->coord.y2 = ((3 * mem->z * (sin(mem->level->player.angle)) + mem->coord.y1));
	draw_line(mem);
}

int update_keys(t_mem *mem)
{
	if (mem->level->player.keyspressed & MOVE_LEFT)
	{
		mem->level->player.x -= 5;
	}
	if (mem->level->player.keyspressed & MOVE_RIGHT)
	{
		mem->level->player.x += 5;
	}
	if (mem->level->player.keyspressed & MOVE_UP)
	{
		mem->level->player.y -= 5;
	}
	if (mem->level->player.keyspressed & MOVE_DOWN)
	{
		mem->level->player.y += 5;
	}
	if (mem->level->player.keyspressed & ROTATE_LEFT)
	{
		mem->level->player.angle -= 0.05;
	}
	if (mem->level->player.keyspressed & ROTATE_RIGHT)
	{
		mem->level->player.angle += 0.05;
	}
	if (mem->level->player.keyspressed & ZOOM_OUT)
		mem->z -= 2;
	if (mem->level->player.keyspressed & ZOOM_IN)
		mem->z += 2;
	if (mem->level->player.keyspressed & EXIT_GAME)
	{
		exit(1);
	}
	refresh_screen(mem);
	return (1);
}

void refresh_screen(t_mem *mem)
{
	if (mem->img.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);
	ft_create_img(mem);
	draw_minimap(mem);

	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->img.ptr, 0, 0);
}

void event_loop(t_mem *mem)
{
	mlx_hook(mem->win.win_ptr, 17, 0L, cross_close, mem);
	mlx_hook(mem->win.win_ptr, MOTION_NOTIFY, PTR_MOTION_MASK,
			 mouse_move_hook, mem);
	mlx_mouse_hook(mem->win.win_ptr, mouse_click_hook, mem);
	mlx_hook(mem->win.win_ptr, 2, 1L << 0, add_key, mem);
	mlx_hook(mem->win.win_ptr, 3, 1L << 1, remove_key, mem);
	mlx_loop_hook(mem->mlx_ptr, update_keys, mem);
	mlx_loop(mem->mlx_ptr);
}
