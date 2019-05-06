/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_vertex.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:31:40 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 21:24:23 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static int		double_coord(t_parse *parse, int error)
{
	t_pvertex	*tmp;
	t_pvertex	*tmp2;

	tmp = parse->vertex;
	while (!error && tmp)
	{
		tmp2 = parse->vertex;
		while (!error && tmp2)
		{
			if (tmp != tmp2 && ((tmp->x == tmp2->x && tmp->y == tmp2->y)
				|| tmp->id == tmp2->id))
				error++;
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (error);
}

static void		recup_nu(t_parse *parse, char *nu, int *error)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	while (nu[i] && (nu[i] == ' ' || nu[i] == '\t'))
		i++;
	*error += !check_int(&nu[i]) ? 1 : 0;
	while (!(*error) && k < (int)ft_strlen(nu))
	{
		j = (k) ? (k - 1) : i;
		j += pass_digit_space(&nu[j]);
		*error += (!check_int(&nu[j])) ? 1 : 0;
		k = j;
		while (!(*error) && nu[k] && ft_isdigit(nu[k]))
			k++;
		*error += (!(*error) && nu[k] == ';') ? 0 : 1;
		*error += (!(*error) && !check_int(&nu[++k])) ? 1 : 0;
		if (!(*error))
			add_list_v(&parse->vertex, &nu[i], &nu[j], &nu[k]);
		while (!(*error) && nu[k] && ft_isdigit(nu[k]))
			k++;
	}
}

void			parse_vertex(t_parse *parse, char *str)
{
	int			i;
	int			error;

	error = (ft_strlen(str) < 7) ? 1 : 0;
	i = 0;
	while (!error && str[++i])
		if (!ft_isdigit(str[i]) && str[i] != '\t'
				&& str[i] != ' ' && str[i] != ';')
			error += 1;
	if (!error)
		recup_nu(parse, &str[1], &error);
	if (double_coord(parse, error))
	{
		ft_printf("%s\n", str);
		free(str);
		return_error(3, parse);
	}
}
