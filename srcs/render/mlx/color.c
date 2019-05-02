/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   color.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 13:23:13 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 19:23:33 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

t_color		get_color(int a, t_mem *mem)
{
	t_color	color;

	color.r = (a * 5 + 30) + mem->color.i % 255;
	color.g = (255 - (a * 10 + 150)) + mem->color.i % 255;
	color.b = (255 - (a * 2 + 45)) + mem->color.i % 255;
	return (color);
}

void		change_color(t_color *color, int hex)
{
	color->r = hex >> 16;
	color->g = hex >> 8;
	color->b = hex;
}

t_color		set_color(int a)
{
	t_color color;

	color.r = a >> 16;
	color.g = a >> 8;
	color.b = a;
	return (color);
}
