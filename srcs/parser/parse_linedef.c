/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_linedef.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:30:10 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 11:08:27 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static int		id_ok(t_pvertex *v, char *str)
{
	int			ok;

	ok = 0;
	while (v)
	{
		if (v->id == ft_atoi(str))
		{
			ok++;
			break ;
		}
		v = v->next;
	}
	return (ok);
}

static void		check_vertex(char *str, t_parse *parse, int *error)
{
	int			i;
	int			tmp;
	t_pvertex	*v;

	tmp = -1;
	i = 0;
	while (!(*error) && ++tmp < 2)
	{
		*error += (!(*error) && !check_int(&str[i])) ? 1 : 0;
		v = parse->vertex;
		*error += (id_ok(v, &str[i]) != 1) ? 1 : 0;
		i += pass_digit_space(&str[i]);
		i += (str[i] == ':') ? 1 : 0;
	}
	*error += (!(*error) && tmp >= 1) ? 0 : 1;
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
	while (!(*error) && ++tmp < 3)
	{
		i += pass_digit_space(&nu[i]) + 1;
		*error += (!(*error) && !check_int(&nu[i])) ? 1 : 0;
	}
	check_vertex(&nu[j], parse, error);
	if (!(*error))
		add_list_l(&parse->linedef, nu);
}

static int		check_same_id(t_parse *parse, int error)
{
	t_plinedef	*tmp;

	tmp = parse->linedef;
	while (tmp)
	{
		if (tmp->id_v1 == tmp->id_v2)
			error++;
		tmp = tmp->next;
	}
	return (error);
}

void			parse_linedef(t_parse *parse, char *str)
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
	if (check_same_id(parse, error))
	{
		free(str);
		return_error(9, parse);
	}
}
