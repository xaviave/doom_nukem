/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   math.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:39:18 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 00:54:52 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int			fn_cross(float x1, float y1, float x2, float y2)
{
	return ((x1 * y2) - (y1 * x2));
}

void		intersect(t_vector vec, float *x, float *y)
{
	float	det;

	*x = fn_cross(vec.tx1, vec.tz1, vec.tx2, vec.tz2);
	*y = fn_cross(5, 5, -20, 5);
	det = fn_cross(vec.tx1 - vec.tx2, vec.tz1 - vec.tz2, 5 - -20, 5 - 5);
	*x = fn_cross(*x, vec.tx1 - vec.tx2, *y, 5 - -20) / det;
	*y = fn_cross(*x, vec.tz1 - vec.tz2, *y, 5 - 5) / det;
}

void		intersect_down(t_vector vec, float *x, float *y)
{
	float det;

	*x = fn_cross(vec.tx1, vec.tz1, vec.tx2, vec.tz2);
	*y = fn_cross(5, 5, 20, 5);
	det = fn_cross(vec.tx1 - vec.tx2, vec.tz1 - vec.tz2, 5 - 20, 5 - 5);
	*x = fn_cross(*x, vec.tx1 - vec.tx2, *y, 5 - 20) / det;
	*y = fn_cross(*x, vec.tz1 - vec.tz2, *y, 5 - 5) / det;
}

int			return_min(int x1, int x2)
{
	return ((x1 > x2 ? x2 : x1));
}

float		distance(float x1, float y1, float x2, float y2)
{
	float	a;
	float	b;

	a = x1 - x2;
	b = y1 - y2;
	return (sqrt(a * a + b * b));
}
