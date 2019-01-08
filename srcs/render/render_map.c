/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/08 15:40:54 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/08 17:08:56 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static t_map	find_extremums(t_level *level)
{
	t_map	ret;
	int		i;

	i = -1;
	ret.xmin = level->vertex[0].x;
	ret.ymin = level->vertex[0].y;
	ret.xmax = level->vertex[0].x;
	ret.ymax = level->vertex[0].y;
	while (++i < level->nb_vertex)
	{
		if (ret.xmax < level->vertex[i].x)
			ret.xmax = level->vertex[i].x;
		else if (ret.xmin > level->vertex[i].x)
			ret.xmin = level->vertex[i].x;
		if (ret.ymax < level->vertex[i].y)
			ret.ymax = level->vertex[i].y;
		else if (ret.ymin > level->vertex[i].y)
			ret.ymin = level->vertex[i].y;
	}
	ret.sizex = WID / (ret.xmax - ((ret.xmin > 0) ? ret.xmin : -ret.xmin) + 1);
	ret.sizey = HEI / (ret.ymax - ((ret.ymin > 0) ? ret.ymin : -ret.ymin) + 1);
	return (ret);
}

void			render_map(t_render *r, t_level *level)
{
	t_map	map;
	
	map = find_extremums(level);
	;
}
