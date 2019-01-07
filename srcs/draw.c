/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 14:41:12 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/07 14:58:14 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void 			draw_line(t_sdl *sdl)
{
	int			dx;
	int			sx;
	int			dy;
	int			sy; 
	int			err;
	int			e2;
	
	dx = abs(sdl->tmp.x1 - sdl->tmp.x);
	dy = abs(sdl->tmp.y1 - sdl->tmp.y);
	sx = sdl->tmp.x < sdl->tmp.x1 ? 1 : -1;
	sy = sdl->tmp.y < sdl->tmp.y1 ? 1 : -1;
	err = (dx > dy ? dx : -dy ) / 2;
  	while (101)
	{
		SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x, sdl->tmp.y);
    	if (sdl->tmp.x == sdl->tmp.x1 && sdl->tmp.y==sdl->tmp.y1)
			break;
    	e2 = err;
    	if (e2 >-dx)
		{
			err -= dy;
			sdl->tmp.x += sx;
		}
    	if (e2 < dy)
		{
			err += dx;
			sdl->tmp.y += sy;
		}
	}
}

void			draw_circle(t_sdl *sdl)
{
	int	radius = 5;
	int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x, sdl->tmp.y - radius);
    SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x + radius, sdl->tmp.y);
    SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x - radius, sdl->tmp.y);
 
    while(x < y) 
    {
        if(f >= 0) 
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;    
        SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x + x, sdl->tmp.y + y);
        SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x - x, sdl->tmp.y + y);
        SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x + x, sdl->tmp.y - y);
        SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x - x, sdl->tmp.y - y);
        SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x + y, sdl->tmp.y + x);
        SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x - y, sdl->tmp.y + x);
        SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x + y, sdl->tmp.y - x);
        SDL_RenderDrawPoint(sdl->rend, sdl->tmp.x - y, sdl->tmp.y - x);
    }
}
