/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw2.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 21:23:50 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 21:26:14 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void draw_to_line(int x1, int y1, int x2, int y2, t_mem *mem)
{
    t_line line;

    line.dx = abs(x2 - x1);
    line.sx = x1 < x2 ? 1 : -1;
    line.dy = abs(y2 - y1);
    line.sy = y1 < y2 ? 1 : -1;
    line.err = (line.dx > line.dy ? line.dx : -line.dy) >> 1;
    line.e2 = line.err;

    while (!(x1 == x2 && y1 == y2))
    {
        if (x1 > 0 && x1 < W && y1 > 0 && y1 < H)
            ft_put_pixel(mem, x1, y1, mem->color);
        line.e2 = line.err;
        if (line.e2 > -line.dx)
        {
            line.err -= line.dy;
            x1 += line.sx;
        }
        if (line.e2 < line.dy)
        {
            line.err += line.dx;
            y1 += line.sy;
        }
    }
}

void fill_column(int x, t_coord p1, t_coord step_bot, t_coord step_top, int sect, t_mem *mem)
{
    int i;
    t_color floor;
    t_color ceil;
    t_color step;

    i = 0;

    sect += 1;
    ceil.g = sect * 10;
    ceil.b = sect * 10;
    floor.r = sect * 10;
    floor.g = sect * 10;
    step.r = 35 * sect;
    step.b = 15 * sect;
    step.g = 0;

    if (x >= 0 && x < W)
        mem->fill_screen[x] = 1;

    // cette partie dessine les plafond (hauteur murs  sur haut de l'ecran)
    if (mem->level->sector[sect - 1].h_ceil > (int)mem->level->player.z)
        while (i < p1.y1)
        {
            if (i >= 0 && i < H)
                ft_put_pixel(mem, x, i, ceil);
            i++;
        }
    // cette partie dessine les "contres plafonds"
    while (step_top.y1 < step_top.y2)
    {
        if (step_top.y1 >= 0 && step_top.y1 < H)
            ft_put_pixel(mem, x, step_top.y1, step);
        step_top.y1++;
    }
    // cette partie dessine les murs
      while (p1.y1 < p1.y2)
    {
        if (p1.y1 >= 0 && p1.y1 < H && mem->color.r != 255 && mem->color.g != 0 && mem->color.b != 0)
            ft_put_pixel(mem, x, p1.y1, step);
        p1.y1++;
    }
    // cette partie dessine les contres marches
    while (step_bot.y1 < step_bot.y2)
    {
        if (step_bot.y1 >= 0 && step_bot.y1 < H)
            ft_put_pixel(mem, x, step_bot.y1, step);
        step_bot.y1++;
    }
    // cette partie dessine le sol
    p1.y1 = step_bot.y1;

    if (mem->level->sector[sect - 1].h_floor < (int)mem->level->player.z)
        while (p1.y1 < H)
        {
            if (p1.y1 >= 0 && p1.y1 < H)
                ft_put_pixel(mem, x, p1.y1, floor);
            p1.y1++;
        }
}
