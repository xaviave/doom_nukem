/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_map.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 13:25:17 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 11:16:35 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			parse_file(int fd, t_parse *parse)
{
	int			check;
	char		*line;

	check = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && !check)
			parse_vertex(parse, line);
		else if (line[0] == 'l')
		{
			check++;
			parse_linedef(parse, line);
		}
		else if (line[0] == 's')
			parse_sector(parse, line);
		else if (line[0] == 'p')
			parse_player(parse, line);
		else
			suite_parse(parse, line);
		free(line);
	}
}

static int		return_line_h(t_plinedef *list, t_psector *sector)
{
	int			i;

	i = -1;
	while (++i < list->nb_text)
	{
		if (list->heigth[i] != -1 && (sector->ground > list->heigth[i]
			|| sector->ceiling < list->heigth[i]))
			return (1);
	}
	return (0);
}

static int		check_text_heigth(t_parse *parse)
{
	int			i;
	int			j;
	t_plinedef	*tmp;
	t_psector	*tmp1;

	j = 0;
	tmp1 = parse->sector;
	while (tmp1)
	{
		i = 0;
		while (++i < tmp1->nb_linedef + 1)
		{
			tmp = parse->linedef;
			while (tmp && i != tmp->id)
				tmp = tmp->next;
			if (return_line_h(tmp, tmp1))
				return (1);
		}
		tmp1 = tmp1->next;
	}
	return (0);
}

void			parse_map(int ac, char **av, t_parse *parse)
{
	int			fd;

	if (ac != 2 || ft_strlen(av[1]) < 4)
		return_error(ac != 2 ? 0 : 1, NULL);
	if (ft_strcmp(&av[1][ft_strlen(av[1]) - 3], ".dk"))
		return_error(1, NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 1)
		return_error(2, NULL);
	parse->player.angle = 0;
	parse_file(fd, parse);
	if (check_text_heigth(parse) || parse->player.angle == 0)
		return_error(-1, parse);
	if (list_len_s(parse->sector) < 1 || list_len_v(parse->vertex) < 3
		|| list_len_l(parse->linedef) < 3 || list_len_e(parse->entity) < 1)
		return_error(7, parse);
}
