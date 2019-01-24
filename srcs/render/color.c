/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   color.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 13:23:13 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 17:40:11 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_color				get_color(int a, t_mem *mem)
{
	t_color			color;

	color.r = (a * 5 + 30) + mem->color.i % 255;
	color.g = (255 - (a * 10 + 150)) + mem->color.i % 255;
	color.b = (255 - (a * 2 + 45)) + mem->color.i % 255;
	return (color);
}
