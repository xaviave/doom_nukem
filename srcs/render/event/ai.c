/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ai.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 16:29:19 by izoukhai     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 01:38:40 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			ai_move(t_mem *mem, int i)
{
	if (mem->level->entity[i].distance <= 30 ||
			mem->level->entity[i].sector != mem->level->player.sector - 1)
		return ;
	if (distance(mem->level->entity[i].x, mem->level->entity[i].y - 2,
				mem->level->player.x, mem->level->player.y) <
			mem->level->entity[i].distance)
		mem->level->entity[i].y -= 0.2;
	if (distance(mem->level->entity[i].x, mem->level->entity[i].y + 2,
				mem->level->player.x, mem->level->player.y) <
			mem->level->entity[i].distance)
		mem->level->entity[i].y += 0.2;
	if (distance(mem->level->entity[i].x - 2, mem->level->entity[i].y,
				mem->level->player.x, mem->level->player.y) <
			mem->level->entity[i].distance)
		mem->level->entity[i].x -= 0.2;
	if (distance(mem->level->entity[i].x + 2, mem->level->entity[i].y,
				mem->level->player.x, mem->level->player.y) <
			mem->level->entity[i].distance)
		mem->level->entity[i].x += 0.2;
}

void			ai_shoot(t_mem *mem, int i)
{
	int			dmg;
	time_t		t;
	int			tmp;

	dmg = 0;
	tmp = mem->level->player.hp;
	srand((unsigned)time(&t));
	dmg = rand() % 5;
	mem->level->entity[i].shooting = 1;
	play_audio(mem->level->sounds.mobshoot);
	mem->level->player.hp -= mem->level->player.hp - dmg <= 0 ?
		mem->level->player.hp : dmg;
	if (tmp != mem->level->player.hp)
		play_audio(mem->level->sounds.hurt);
}

void			ai_delay(t_mem *mem, int i)
{
	if (!(mem->ai1.tv_sec))
		gettimeofday(&mem->ai1, NULL);
	gettimeofday(&mem->ai2, NULL);
	if (mem->ai2.tv_sec - mem->ai1.tv_sec >= 1)
	{
		ai_shoot(mem, i);
		mem->ai1.tv_sec = 0;
		mem->ai2.tv_sec = 0;
	}
}

static void		ai_mob(t_mem *mem, int i)
{
	if (mem->level->entity[i].text != MOB || !mem->level->entity[i].alive)
		return ;
	mem->level->entity[i].distance = distance(mem->level->entity[i].x,
			mem->level->entity[i].y, mem->level->player.x,
			mem->level->player.y);
	if (mem->level->entity[i].distance <= 90)
	{
		ai_move(mem, i);
		ai_delay(mem, i);
	}
	else
		mem->level->entity[i].shooting = 0;
}

void			ai_think(t_mem *mem)
{
	int			i;

	i = -1;
	while (++i < mem->level->nb_entity)
		ai_mob(mem, i);
}
