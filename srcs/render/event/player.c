#include "doom.h"

// static inline void	check_mobs(t_mem *mem);

void				on_shoot(t_mem *mem)
{
	int				i;
	float			zoom;
	t_vertex		lim;

	i = -1;
	while(++i < mem->level->nb_monsters)
	{
		if (!mem->level->monsters[i].alive)
			continue;
		zoom = (H * 0.02) / mem->level->monsters[i].distance;
		lim.x = (365 * zoom * 0.5);
		lim.y = (285 * zoom) * 1.5;
		if ((W / 2 >= mem->level->monsters[i].s_x - lim.x && W / 2 <=
		mem->level->monsters[i].s_x + lim.x) &&
		(H / 2 >= mem->level->monsters[i].s_y - lim.y - mem->camera_y &&
		H / 2 <= mem->level->monsters[i].s_y - mem->camera_y))
			mem->level->monsters[i].alive = 0;
	}
}

void				on_reload(t_mem *mem)
{
	if (!mem->level->player.magazine)
		return ;
	play_audio(mem->level->sounds.reload);
	mem->level->player.magazine--;
	mem->level->player.ammos = 30;
}