/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map_3.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 01:43:23 by mel-akio     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 01:43:24 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	process(t_mem *mem)
{
	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->img.ptr, 0, 0);
	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->gun.ptr,
(W * 0.4) + 200 + (int)mem->level->player.motion + mem->level->player.recoil,
(H >> 1) + (int)mem->level->player.motion + mem->level->player.recoil);
	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->crosshair.ptr,
(W >> 1) - 16, (H >> 1) - 16);
}
