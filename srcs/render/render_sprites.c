/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_sprites.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/25 17:43:33 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void render_sprites(t_mem *mem, int sect)
{
    int j;
    int i;
    float ix1;
    float iz1;
    float mx;
    float my;
    float mz1;
    float mx1;

    

    j = -1;

    while (++j < mem->level->sector[sect].nb_linedef)
    {
        i = 0;
        while (i < mem->level->nb_monsters)
        {
            if (mem->level->monsters[i].sector == sect)
            {
                mx = mem->level->monsters[i].x - mem->level->player.x;
                my = mem->level->monsters[i].y - mem->level->player.y;
                mz1 = mx * cos(mem->level->player.angle) + my * sin(mem->level->player.angle);
                mx1 = mx * sin(mem->level->player.angle) - my * cos(mem->level->player.angle);
                intersect(mx1, mz1, mx1, mz1, -2, 5, -20, 5, &ix1, &iz1);
                if (mz1 >= 0)
                {
                    mx = -mx1 * 800 / mz1 + W / 2;
                    my = H * (mem->level->player.z - mem->level->sector[sect].h_floor) / mz1 + H / 2;
                    if (mx > 0 && mx < W)
                        put_img_to_img(mem, &mem->monster, mx, my, (H * 0.03) / distance(mem->level->monsters[i].x, mem->level->monsters[i].y, mem->level->player.x, mem->level->player.y));
                }
            }
            i++;
        }
    }
}
