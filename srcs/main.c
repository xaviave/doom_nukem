/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 10:14:48 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 14:27:38 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

static void init_parse(t_parse *parse)
{
	parse->vertex = NULL;
	parse->sector = NULL;
	parse->player.x = -1;
	parse->player.y = -1;
}

static void init_level(t_level *level)
{
	level->vertex = NULL;
	level->sector = NULL;
	level->next = NULL;
}

static void init_mem(t_mem *mem)
{
	mem->mlx_ptr = mlx_init();
	mem->win.width = W;
	mem->win.height = H;
	mem->win.win_ptr = mlx_new_window(mem->mlx_ptr, mem->win.width,
		mem->win.height, "doomy nukoom");
	mem->color.r = 130;
	mem->color.g = 35;
	mem->color.b = 235;
	mem->color.a = 0;
	mem->color.i = 0;
	ft_create_img(mem);
}

int main(int ac, char **av)
{
	t_parse parse;
	t_level level;
	t_mem	mem;

	init_parse(&parse);
	parse_map(ac, av, &parse);
	init_level(&level);
	parse_to_level(&parse, &level);
	init_mem(&mem);
	render_map(&mem, &level);
	free_level(&level);
	return (0);
}
