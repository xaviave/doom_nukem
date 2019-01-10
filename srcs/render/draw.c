/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 16:09:57 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 14:29:06 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void 			draw_line(t_mem *mem)
{
	t_line		line;
	
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
    	if (line.e2 >-line.dx)
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
/*
void			draw_circle(t_mem *mem)
{
	int	radius = 5;
	int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y2 = -2 * radius;
    int mem->coord.x2 = 0;
    int y2 = radius;
 
    mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2, mem->coord.y2 - radius);
    mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 + radius, mem->coord.y2);
    mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 - radius, mem->coord.y2);
 
    while(mem->coord.x2 < y2) 
    {
        if(f >= 0) 
        {
            y2--;
            ddF_y2 += 2;
            f += ddF_y2;
        }
        mem->coord.x2++;
        ddF_x += 2;
        f += ddF_x + 1;    
        mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 + mem->coord.x2, mem->coord.y2 + y2);
        mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 - mem->coord.x2, mem->coord.y2 + y2);
        mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 + mem->coord.x2, mem->coord.y2 - y2);
        mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 - mem->coord.x2, mem->coord.y2 - y2);
        mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 + y2, mem->coord.y2 + mem->coord.x2);
        mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 - y2, mem->coord.y2 + mem->coord.x2);
        mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 + y2, mem->coord.y2 - mem->coord.x2);
        mem_RenderDrawPoint(mem->rend, mem->coord.mem->coord.x2 - y2, mem->coord.y2 - mem->coord.x2);
    }
}
*/
