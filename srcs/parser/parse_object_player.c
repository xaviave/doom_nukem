/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_object_player.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 20:14:20 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 11:13:31 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

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
	{
		free(str);
		return_error(5, parse);
	}
	parse->player.x = (float)ft_atoi(&str[2]);
	parse->player.y = (float)ft_atoi(&str[i]);
	parse->player.angle = 1.570796;
}

static void		check_nu(t_parse *parse, char *nu, int *error)
{
	int			i;
	int			j;
	int			tmp;

	i = 0;
	tmp = 0;
	while (nu[i] && (nu[i] == ' ' || nu[i] == '\t'))
		i++;
	j = i + pass_digit_space(&nu[i]);
	*error += !check_int(&nu[i]) ? 1 : 0;
	while (!(*error) && ++tmp < 5)
	{
		i += pass_digit_space(&nu[i]) + 1;
		*error += (!(*error) && !check_int(&nu[i])) ? 1 : 0;
	}
	if (!(*error))
		add_list_e(&parse->entity, nu);
}

static void		parse_entity(t_parse *parse, char *str)
{
	int			error;
	int			i;

	error = (ft_strlen(str) < 9) ? 1 : 0;
	i = 0;
	while (!error && str[++i])
		if (!ft_isdigit(str[i]) && str[i] != '\t' && str[i] != ' '
			&& str[i] != ':')
			error = 1;
	if (!error)
		check_nu(parse, &str[1], &error);
	if (error)
	{
		free(str);
		return_error(9, parse);
	}
}

void			suite_parse(t_parse *parse, char *line)
{
	if (line[0] == 'e')
		parse_entity(parse, line);
	else if (line[0] != '#' && line[0] != '\0')
	{
		free(line);
		return_error(6, parse);
	}
}
