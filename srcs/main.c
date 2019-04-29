/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 10:14:48 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 18:59:21 by lloyet      ###    #+. /#+    ###.fr     */
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
	parse->player.z = -1;
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
	mem->camera_y = H / 2;
	mem->camera_x = W / 2;
	mem->win.win_ptr = mlx_new_window(mem->mlx_ptr, mem->win.width,
									mem->win.height, "doomy nukoom");
	mem->z = 100;
	mem->x = 100 - level->player.x * 10;
	mem->y = 100 - level->player.y * 10;
	mem->z = 1;
	mem->level = level;
	mem->level->c[0] = 0xFF0000;
	mem->level->c[1] = 0x71e045;
	mem->level->c[2] = 0x943ad8;
	mem->level->c[3] = 0x1a78a1;
	mem->level->c[4] = 0x63ffe5;
	mem->level->c[5] = 0x00ffff;
	
	mem->level->nb_monsters = 2;
	mem->level->monsters = malloc(sizeof(t_monster) * mem->level->nb_monsters);

	mem->level->monsters[0].sector = 3;
	mem->level->monsters[0].x = 483;
	mem->level->monsters[0].y = 299;

	mem->level->monsters[1].sector = 3;
	mem->level->monsters[1].x = 460;
	mem->level->monsters[1].y = 280;

	mem->FPS = 0;
	mem->menu = 0;
	mem->mouseShow = 0;
	mem->mouse_sensi = 0.001;
	mem->gravity = 0.0;
	mem->tv1.tv_sec = 0;
	mem->tv2.tv_sec = 0;

	//dprintf(1, "%f %f\n", mem->level->player.x, mem->level->player.y);
	if (level->nb_sector > 1) //sizeof(int) = 4 in gcc *64 macOSX
		if (!(mem->level->n_sector = (int *)malloc(4 * level->nb_sector)))
			return ;
	ft_create_img(mem);
}

int main(int ac, char **av)
{
	t_parse parse;
	t_level level;
	t_mem mem;
	int i;

	i = 0;
	mem.fill_screen = malloc(sizeof(char) * W);
	init_parse(&parse);
	parse_map(ac, av, &parse);
	init_level(&level);
	parse_to_level(&parse, &level);
	init_mem(&mem, &level);
	//mem.level->player.z = 5;
	mem.camera_x = 500;
	mem.camera_y = -100;
	mem.level->player.motion_state = 0.40;
	textures_init(&mem);
	init_sound(&mem);
	play_music(mem.level->sounds.music1);
	event_loop(&mem);
	free_level(&level);
	free_audio(&mem);
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