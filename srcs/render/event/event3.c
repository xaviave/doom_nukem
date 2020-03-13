/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 13:13:18 by xamartin          #+#    #+#             */
/*   Updated: 2020/03/13 13:58:31 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void		alloc_left(t_mem *mem)
{
	mem->col_x += 1 * mem->cos_angle;
	mem->col_y -= 1 * mem->sin_angle;
	mem->level->player.x += (8 * mem->sin_angle);
	mem->level->player.y -= (8 * mem->cos_angle);
}

void		alloc_right(t_mem *mem)
{
	mem->col_x -= 1 * mem->cos_angle;
	mem->col_y += 1 * mem->sin_angle;
	mem->level->player.x -= (8 * mem->sin_angle);
	mem->level->player.y += (8 * mem->cos_angle);
}

void		alloc_up(t_mem *mem)
{
	mem->col_x += 1 * mem->cos_angle;
	mem->col_y += 1 * mem->sin_angle;
	mem->level->player.x += (8 * mem->cos_angle);
	mem->level->player.y += (8 * mem->sin_angle);
}

void		alloc_down(t_mem *mem)
{
	mem->col_x -= 1 * mem->cos_angle;
	mem->col_y -= 1 * mem->sin_angle;
	mem->level->player.x -= (8 * mem->cos_angle);
	mem->level->player.y -= (8 * mem->sin_angle);
}
