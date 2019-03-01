/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_sprites.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/01 13:29:06 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void render_sprites(t_mem *mem, int sect)
{
    int i;
    float ix1;
    float iz1;
    float mx;
    float my;
    float mz1;
    float mx1;

    i = -1;
    while (++i < mem->level->nb_monsters)
        if (mem->level->monsters[i].sector == sect)
        {
            mx = mem->level->monsters[i].x - mem->level->player.x;
            my = mem->level->monsters[i].y - mem->level->player.y;
            mz1 = mx * mem->cos_angle + my * mem->sin_angle;
            mx1 = mx * mem->sin_angle - my * mem->cos_angle;
            intersect(mx1, mz1, mx1, mz1, -2, 5, -20, 5, &ix1, &iz1);
            if (mz1 >= 0)
            {
                mx = -mx1 * 800 / mz1 + W * 0.5;
                my = H * (mem->level->player.z - mem->level->sector[sect].h_floor) / mz1 + H * 0.5 + mem->level->player.recoil;
                if (mx > 0 && mx < W)
                    put_img_to_img(mem, &mem->monster, mx, my, (H * 0.02) / mem->level->monsters[i].distance);
            }
        }
}
