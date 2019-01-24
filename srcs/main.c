/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 10:14:48 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 16:37:57 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

static void init_parse(t_parse *parse)
{
	parse->linedef = NULL;
	parse->vertex = NULL;
	parse->sector = NULL;
	parse->player.x = -1;
	parse->player.y = -1;
	parse->nb = 0;
}

static void init_level(t_level *level)
{
	level->vertex = NULL;
	level->sector = NULL;
	level->next = NULL;
	level->linedef = NULL;
}

static void init_mem(t_mem *mem, t_level *level)
{
	mem->mlx_ptr = mlx_init();
	mem->win.width = W;
	mem->win.height = H;
	mem->win.win_ptr = mlx_new_window(mem->mlx_ptr, mem->win.width,
									  mem->win.height, "doomy nukoom");
	mem->z = 100;
	mem->x = 100 - level->player.x * 10;
	mem->y = 100 - level->player.y * 10;
	mem->level = level;
	mem->level->c[0] = 0xff;
	mem->level->c[1] = 0xffffff;
	ft_create_img(mem);
}

int main(int ac, char **av)
{
	t_parse parse;
	t_level level;
	t_mem mem;

	init_parse(&parse);
	parse_map(ac, av, &parse);
	init_level(&level);
	parse_to_level(&parse, &level);
	init_mem(&mem, &level);
	event_loop(&mem);
	free_level(&level);
	return (0);
}

/*
**	XOR (^) 1 0 -> 1 / 1 1 -> 0 / 0 0 -> 0 
**	AND (&) 1 1 -> 1 / 0 0 -> 0 / 0 1 -> 0
**	OR	(|) 1 0 -> 1 / 0 0 -> 0 / 1 1 -> 1
**	NOT	(~)	1 -> 0 / 0 -> 1 / ~(010101) -> 101010


//octet |= mask;

	

	//octet &= ~mask;
	// OCTET ET= NOT(MASK)

	//octet |= mask1;
*/
