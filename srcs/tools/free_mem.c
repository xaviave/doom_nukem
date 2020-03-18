/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_mem.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 11:54:19 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 01:33:12 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	free_image(t_mem *mem)
{
	if (mem->wall.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->wall.ptr);
	if (mem->hud.hp.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->hud.hp.ptr);
	if (mem->hud.ammo.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->hud.ammo.ptr);
	if (mem->win.win_ptr)
		mlx_destroy_window(mem->mlx_ptr, mem->win.win_ptr);
	if (mem->mlx_ptr)
		free(mem->mlx_ptr);
	free_level(mem->level);
	free_audio(mem);
	exit(1);
}

void		free_mem(t_mem *mem)
{
	if (mem->fill_screen)
		free(mem->fill_screen);
	if (mem->img.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);
	if (mem->gun.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->gun.ptr);
	if (mem->crosshair.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->crosshair.ptr);
	if (mem->monster.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->monster.ptr);
	if (mem->skybox.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->skybox.ptr);
	if (mem->shooting_monster.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->shooting_monster.ptr);
	if (mem->hp_box.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->hp_box.ptr);
	if (mem->ammo_box.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->ammo_box.ptr);
	free_image(mem);
}
