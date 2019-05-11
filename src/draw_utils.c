/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 23:55:41 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 23:56:37 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

static void			image_line2(t_image *img, t_vertex *v1,
	int *n, double mult_diff)
{
	if (n[1])
	{
		n[0] = 0;
		while (n[0] != n[4])
		{
			image_pixel_put(img, v1->x + (int)((double)n[0]
				* mult_diff), v1->y + n[0], n[5]);
			n[0] += n[2];
		}
	}
	else
	{
		n[0] = 0;
		while (n[0] != n[4])
		{
			image_pixel_put(img, v1->x + n[0], v1->y + (int)((double)n[0]
				* mult_diff), n[5]);
			n[0] += n[2];
		}
	}
	return ;
}

void				image_line(t_image *img, t_vertex *v1, t_vertex *v2, int c)
{
	double			mult_diff;
	int				n[6];
	int				swap;

	n[1] = 0;
	n[5] = c;
	n[3] = v2->y - v1->y;
	n[4] = v2->x - v1->x;
	if (abs(n[3]) > abs(n[4]))
	{
		swap = n[3];
		n[3] = n[4];
		n[4] = swap;
		n[1] = 1;
	}
	n[2] = n[4] < 0 ? -1 : 1;
	mult_diff = n[4] != 0 ? (double)n[3] / (double)n[4] : (double)n[3];
	image_line2(img, v1, n, mult_diff);
	return ;
}
