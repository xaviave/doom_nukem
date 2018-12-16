/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_map.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 13:25:17 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/16 23:00:59 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void			init_player(int x, int y, t_player *player)
{
	player->x = x;
	player->y = y;
}

void			parse_player(t_parse *parse, char *str)
{
	int			i;
	int			j;
	int			error;

	error = (ft_strlen(str) < 5) ? 1 : 0;
	i = 0;
	while (!error && str[++i])
		if (!ft_isdigit(str[i]) && str[i] != '\t' && str[i] != ' ')
			error = 1;
	i = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	i += pass_digit_space(&str[i]);
	if (!error && (!check_int(&str[1]) || !check_int(&str[i])))
		error = 1;
	j = pass_digit_space(&str[i]);
	if (error || i + j != (int)ft_strlen(str))
		return_error(5, parse);
	parse->player.x = ft_atoi(&str[2]);
	parse->player.y = ft_atoi(&str[i]);
}

void			parse_file(int fd, t_parse *parse)
{
	int			check;
	char		*line;

	check = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && !check)
			parse_vertex(parse, line);
		else if (line[0] == 's')
		{
			check = 1;
			parse_sector(parse, line);
		}
		else if (line[0] == 'p')
		{
			check = 2;
			parse_player(parse, line);
		}
		else if (line[0] != '#' && line[0] != '\0')
		{
			free(line);
			return_error(6, parse);
		}
		free(line);
	}
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
	parse_file(fd, parse);
	



	t_pvertex *tmp;

	tmp = parse->vertex;
	ft_printf("_________________________________________\n");
	ft_printf("||     y     |      x     |      id    ||\n");
	ft_printf("_________________________________________\n");
	while (tmp)
	{
		ft_printf("|| y = %5d | x = %5d  | id = %5d ||\n", tmp->y, tmp->x, tmp->id);
		tmp = tmp->next;
	}
	ft_printf("_________________________________________\n");

	t_psector *tmp1;

	tmp1 = parse->sector;
	ft_printf("\n______________________________\n");
	ft_printf("|| sector |      vertex     ||\n");
	ft_printf("______________________________\n");
	int j;
	while (tmp1)
	{
		j = -1;
		ft_printf("|| %5d  |", tmp1->id);
		while (++j < tmp1->nu_vertex)
			ft_printf(" %3d", tmp1->vertex[j]);
		ft_printf(" ||\n");
	ft_printf("______________________________\n");
		tmp1 = tmp1->next;
	}
	ft_printf("player x = %d y = %d", parse->player.x, parse->player.y);
}
