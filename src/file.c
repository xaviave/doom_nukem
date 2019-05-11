/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   file.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 23:48:13 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 03:34:09 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

int					file_save(t_gui *g)
{
	t_file			f;

	f.v_id = 0;
	f.s_id = 0;
	f.l_id = 0;
	if ((g->file = open("map.dk", O_RDWR | O_TRUNC | O_CREAT)))
	{
		f.l = g->layer->begin->child;
		while (f.l)
		{
			f.l_cur = (t_layer*)f.l->content;
			if (f.l_cur->shape)
			{
				f.s = f.l_cur->shape->begin;
				while (f.s)
				{
					f.s_cur = (t_shape*)f.s->content;
					if (f.s_cur)
					{
						f.v = f.s_cur->vertex->begin;
						while (f.v)
						{
							f.v_cur = (t_vertex*)f.v->content;
							ft_putstr_fd("V\t", g->file);
							ft_putstr_fd(ft_itoa(f.v_cur->x), g->file);
							ft_putstr_fd("\t\t", g->file);
							ft_putstr_fd(ft_itoa(f.v_cur->y), g->file);
							ft_putstr_fd(";", g->file);
							ft_putstr_fd(ft_itoa(f.v_id), g->file);
							ft_putstr_fd("\n", g->file);
							f.v = f.v->child;
							f.v_id++;
						}
					}
					f.s = f.s->child;
					f.l_id++;
				}
			}
			f.l = f.l->child;
			f.l_id++;
		}
	}
	return (0);
}