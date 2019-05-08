/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 10:14:48 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 13:31:13 by xamartin    ###    #+. /#+    ###.fr     */
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
	init_hud(mem);
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
	mem->level->player.sector = player_sector(mem, 1);
	mem->level->player.prev_sector = mem->level->player.sector;
	mem->level->c[0] = 0xFF0000;
	mem->level->c[1] = 0x71e045;
	mem->level->c[2] = 0x943ad8;
	mem->level->c[3] = 0x1a78a1;
	mem->level->c[4] = 0x63ffe5;
	mem->level->c[5] = 0x00ffff;
	mem->level->nb_monsters = 2;
	if (!(mem->level->monsters = (t_monster *)malloc(sizeof(t_monster) * mem->level->nb_monsters)))
		return ;
	mem->level->monsters[0].sector = 3;
	mem->level->monsters[0].alive = 1;
	mem->level->monsters[0].x = 483;
	mem->level->monsters[0].y = 299;

	mem->level->monsters[1].sector = 3;
	mem->level->monsters[1].alive = 1;
	mem->level->monsters[1].x = 460;
	mem->level->monsters[1].y = 280;
	mem->fps = 0;
	mem->tv1.tv_sec = 0;
	mem->tv2.tv_sec = 0;
	mem->ai1.tv_sec = 0;
	mem->ai2.tv_sec = 0;
	mem->level->player.god_mode = 0;
	mem->level->player.heigth_player = 5;
	level->player.hp = 100;
	level->player.ammos = 30;
	level->player.magazine = 1;
	if (level->nb_sector > 1)
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
	if (!(mem.fill_screen = (char *)malloc(sizeof(char) * W)))
		return (0);
	init_parse(&parse);
	parse_map(ac, av, &parse);
	init_level(&level);
	parse_to_level(&parse, &level);
	init_mem(&mem, &level);
	mem.level->player.z = 5;
	mem.level->player.motion_state = 0.40;
	textures_init(&mem);
	init_sound(&mem);
	play_music(mem.level->sounds.music1);
	event_loop(&mem);
	free_mem(&mem);
	return (0);
}
