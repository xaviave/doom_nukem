/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_mem.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 11:54:19 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 13:30:16 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

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
	if (mem->win.win_ptr)
		mlx_destroy_window(mem->mlx_ptr, mem->win.win_ptr);
	if (mem->mlx_ptr)
		free(mem->mlx_ptr);
	free_level(mem->level);
	free_audio(mem);
	exit(1);
}
