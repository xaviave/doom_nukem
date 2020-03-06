/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hud.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 16:22:11 by izoukhai     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 23:43:44 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void					init_hud(t_mem *mem)
{
	mem->hud.x_hp = 0;
	mem->hud.y_hp = H - 50;
	mem->hud.x_ammo = W - 110;
	mem->hud.y_ammo = H - 50;
	mem->hud.x_str_hp = mem->hud.x_hp + 49;
	mem->hud.y_str_hp = H - 38;
	mem->hud.x_str_ammo = mem->hud.x_ammo + 40;
	mem->hud.y_str_ammo = H - 40;
	mem->hud.x_str_magazine = mem->hud.x_str_ammo + 35;
	mem->hud.y_str_magazine = H - 40;
}

void					set_hud(t_mem *mem)
{
	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->hud.hp.ptr,
			mem->hud.x_hp, mem->hud.y_hp);
	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->hud.ammo.ptr,
			mem->hud.x_ammo, mem->hud.y_ammo);
	mem->hud.str_hp = ft_itoa(mem->level->player.hp);
	mem->hud.str_ammo = ft_itoa(mem->level->player.ammos);
	mem->hud.str_magazine = ft_itoa(mem->level->player.magazine);
	mlx_string_put(mem->mlx_ptr, mem->win.win_ptr, mem->hud.x_str_hp,
			mem->hud.y_str_hp, 0xFFFFFF, mem->hud.str_hp);
	mlx_string_put(mem->mlx_ptr, mem->win.win_ptr, mem->hud.x_str_ammo,
			mem->hud.y_str_ammo, 0xFFFFFF, mem->hud.str_ammo);
	mlx_string_put(mem->mlx_ptr, mem->win.win_ptr, mem->hud.x_str_ammo + 21,
			mem->hud.y_str_ammo, 0xFFFFFF, "/");
	mlx_string_put(mem->mlx_ptr, mem->win.win_ptr, mem->hud.x_str_magazine,
			mem->hud.y_str_magazine, 0xFFFFFF, mem->hud.str_magazine);
	if (mem->hud.str_ammo)
		free(mem->hud.str_ammo);
	if (mem->hud.str_hp)
		free(mem->hud.str_hp);
	if (mem->hud.str_magazine)
		free(mem->hud.str_magazine);
}
