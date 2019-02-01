/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   color.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 13:23:13 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 14:30:36 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_color get_color(int a, t_mem *mem)
{
	t_color color;

	color.r = (a * 5 + 30) + mem->color.i % 255;
	color.g = (255 - (a * 10 + 150)) + mem->color.i % 255;
	color.b = (255 - (a * 2 + 45)) + mem->color.i % 255;
	return (color);
}

void change_color(t_color *color, int hex)
{
	color->r = hex >> 16;
	color->g = hex >> 8;
	color->b = hex;
}

t_color add_rgb(t_color color, unsigned char r, unsigned char g, unsigned char b)
{
	if (color.r + r > 255)
		color.r = 255;
	else
		color.r += r;
	if (color.g + g > 255)
		color.g = 255;
	else
		color.g += g;
	if (color.b + b > 255)
		color.b = 255;
	else
		color.b += b;
	return (color);
}
