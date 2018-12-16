/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_sector.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:31:32 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/16 22:21:50 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

static int		double_vertex(t_psector *sector, int error)
{
	int			i;
	int			j;
	int			*tmp2;
	t_psector	*tmp;

	tmp = sector;
	while (!error && tmp)
	{
		j = -1;
		tmp2 = tmp->vertex;
		while (!error && ++j < tmp->nu_vertex)
		{
			i = -1;
			while (++i < tmp->nu_vertex)
				if (i != j && tmp2[i] == tmp->vertex[j])
					error++;
		}
		tmp = tmp->next;
	}
	return (error);
}

static void		check_vertex(char *str, t_parse *parse, int *error)
{
	int			i;
	int			ok;
	int			tmp;
	t_pvertex	*v;

	tmp = 0;
	i = pass_digit_space(&str[0]);
	while (!(*error) && i < (int)ft_strlen(str) && ++tmp)
	{
		ok = 0;
		*error += (!(*error) && !check_int(&str[i])) ? 1 : 0;
		v = parse->vertex;
		while (!(*error) && v)
		{
			if (v->id == ft_atoi(&str[i]))
			{
				ok++;
				break ;
			}
			v = v->next;
		}
		*error += (ok != 1) ? 1 : 0;
		i += pass_digit_space(&str[i]);
	}
	*error += (!(*error) && tmp < 3) ? 1 : 0;
}

static void		check_nu(t_parse *parse, char *nu, int *error)
{
	int			i;
	int			tmp;

	i = 0;
	tmp = 0;
	while (nu[i] && (nu[i] == ' ' || nu[i] == '\t'))
		i++;
	*error += !check_int(&nu[i]) ? 1 : 0;
	while (!(*error) && ++tmp < 3)
	{
		i += pass_digit_space(&nu[i]);
		*error += (!(*error) && !check_int(&nu[i])) ? 1 : 0;
	}
	check_vertex(&nu[i], parse, error);
	if (!(*error))
		add_list_s(&parse->sector, nu);
}

void			parse_sector(t_parse *parse, char *str)
{
	int			i;
	int			error;

	error = (ft_strlen(str) < 15) ? 1 : 0;
	i = 0;
	while (!error && str[++i])
		if (!ft_isdigit(str[i]) && str[i] != '\t' && str[i] != ' ')
			error = 1;
	if (!error)
		check_nu(parse, &str[1], &error);
	if (double_vertex(parse->sector, error))
	{
		free(str);
		return_error(4, parse);
	}
}
