/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 16:09:57 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 17:09:37 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void 			draw_line(t_sdl *sdl)
{
	t_line		line;
	
	line.dx = abs(sdl->coord.x2 - sdl->coord.x1);
	line.sx = sdl->coord.x1 < sdl->coord.x2 ? 1 : -1;
  	line.dy = abs(sdl->coord.y2 - sdl->coord.y1);
	line.sy = sdl->coord.y1 < sdl->coord.y2 ? 1 : -1; 
  	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2
  	line.e2 = line.err;
 
  	while (101)
	{
    	setPixel(sdl->coord.x1, sdl->coord.y1);
		if (sdl->coord.x1 == sdl->coord.x2 && sdl->coord.y1 == sdl->coord.y2)
			break;
    	line.e2 = line.err;
    	if (line.e2 >-line.dx)
		{
			line.err -= line.dy;
			sdl->coord.x1 += line.sx;
		}
    	if (line.e2 < line.dy)
		{
			line.err += line.dx;
			sdl->coord.y1 += line.sy;
		}
  	}
}

void			draw_circle(t_sdl *sdl)
{
	if (sdl)
	;
	/*
	int	radius = 5;
	int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y2 = -2 * radius;
    int sdl->coord.x2 = 0;
    int y2 = radius;
 
    SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2, sdl->coord.y2 - radius);
    SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 + radius, sdl->coord.y2);
    SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 - radius, sdl->coord.y2);
 
    while(sdl->coord.x2 < y2) 
    {
        if(f >= 0) 
        {
            y2--;
            ddF_y2 += 2;
            f += ddF_y2;
        }
        sdl->coord.x2++;
        ddF_x += 2;
        f += ddF_x + 1;    
        SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 + sdl->coord.x2, sdl->coord.y2 + y2);
        SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 - sdl->coord.x2, sdl->coord.y2 + y2);
        SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 + sdl->coord.x2, sdl->coord.y2 - y2);
        SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 - sdl->coord.x2, sdl->coord.y2 - y2);
        SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 + y2, sdl->coord.y2 + sdl->coord.x2);
        SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 - y2, sdl->coord.y2 + sdl->coord.x2);
        SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 + y2, sdl->coord.y2 - sdl->coord.x2);
        SDL_RenderDrawPoint(sdl->rend, sdl->coord.sdl->coord.x2 - y2, sdl->coord.y2 - sdl->coord.x2);
    }
	*/
}
