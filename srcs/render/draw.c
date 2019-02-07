/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:09 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/07 15:27:35 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void draw_line(t_mem *mem)
{
    t_line line;

    line.dx = abs(mem->coord.x2 - mem->coord.x1);
    line.sx = mem->coord.x1 < mem->coord.x2 ? 1 : -1;
    line.dy = abs(mem->coord.y2 - mem->coord.y1);
    line.sy = mem->coord.y1 < mem->coord.y2 ? 1 : -1;
    line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
    line.e2 = line.err;

    while (101)
    {
        ft_put_pixel(mem, mem->coord.x1, mem->coord.y1, mem->color);
        if (mem->coord.x1 == mem->coord.x2 && mem->coord.y1 == mem->coord.y2)
            break;
        line.e2 = line.err;
        if (line.e2 > -line.dx)
        {
            line.err -= line.dy;
            mem->coord.x1 += line.sx;
        }
        if (line.e2 < line.dy)
        {
            line.err += line.dx;
            mem->coord.y1 += line.sy;
        }
    }
}

void draw_to_line(int x1, int y1, int x2, int y2, t_mem *mem)
{
    t_line line;

    line.dx = abs(x2 - x1);
    line.sx = x1 < x2 ? 1 : -1;
    line.dy = abs(y2 - y1);
    line.sy = y1 < y2 ? 1 : -1;
    line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
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

void fill_column(int x, t_coord p1, t_mem *mem)
{
    int i;

    i = 0;

    while (p1.y1 < p1.y2)
    {
        if (p1.y1 > 0 && p1.y1 < H)
            ft_put_pixel(mem, x, p1.y1, mem->color);
        p1.y1++;
    }
}

void fill_row(int y, t_coord p1, t_mem *mem)
{
    int i;
    t_color ceil;

    i = 0;

    change_color(&ceil, 0x666666);
    while (p1.x1 < p1.x2)
    {
        if (p1.x1 > 0 && p1.x1 < W)
            ft_put_pixel(mem, p1.x1, y, ceil);
        p1.x1++;
    }
}

void draw_camera(t_mem *mem)
{
    t_color color;

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 0;

    ft_put_pixel(mem, (mem->z * 0.01 * mem->level->player.x), (mem->z * 0.01 * mem->level->player.y), color);
    mem->coord.x1 = (mem->z * 0.01 * mem->level->player.x);
    mem->coord.y1 = (mem->z * 0.01 * mem->level->player.y);
    draw_circle(mem);
}

void draw_square(t_mem *mem)
{
    t_color color;

    color.r = 0;
    color.g = 255;
    color.b = 0;
    color.a = 0;

    ft_put_pixel(mem, mem->coord.x1, mem->coord.y1, color);
}

void draw_circle(t_mem *mem)
{
    t_coord coord = {mem->coord.x1, mem->coord.y1, 0, 0};
    t_color color = {255, 0, 0, 0, 0};
    int radius = 2;
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y2 = -2 * radius;
    int x2 = 0;
    int y2 = radius;

    //ft_printf("\033[32mx = %d ; y = %d\n\033[0m", mem->coord.x1, mem->coord.y1);

    /*   ft_put_pixel(mem, coord.x1, coord.y1 + radius, color);
    ft_put_pixel(mem, coord.x1, coord.y1 - radius, color);
    ft_put_pixel(mem, coord.x1 + radius, coord.y1, color);
    ft_put_pixel(mem, coord.x1 - radius, coord.y1, color);
*/
    while (x2 < y2)
    {
        if (f >= 0)
        {
            y2--;
            ddF_y2 += 2;
            f += ddF_y2;
        }
        x2++;
        ddF_x += 2;
        f += ddF_x + 1;
        ft_put_pixel(mem, coord.x1 + x2, coord.y1 + y2, color);
        ft_put_pixel(mem, coord.x1 - x2, coord.y1 + y2, color);
        ft_put_pixel(mem, coord.x1 + x2, coord.y1 - y2, color);
        ft_put_pixel(mem, coord.x1 - x2, coord.y1 - y2, color);
        ft_put_pixel(mem, coord.x1 + y2, coord.y1 + x2, color);
        ft_put_pixel(mem, coord.x1 - y2, coord.y1 + x2, color);
        ft_put_pixel(mem, coord.x1 + y2, coord.y1 - x2, color);
        ft_put_pixel(mem, coord.x1 - y2, coord.y1 - x2, color);
    }
}
