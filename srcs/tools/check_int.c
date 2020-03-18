/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_int.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 19:12:49 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 19:46:42 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int			check_int(char *tmp)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	ret = 1;
	while (tmp[i] && (tmp[i] != ' ' || tmp[i] != '\t'))
		i++;
	while (tmp[i + j] && ft_isdigit(tmp[i + j]))
		j++;
	if (j > 11 || ft_atoi(tmp) > 2147483647 || ft_atoi(tmp) < 0)
		ret = 0;
	return (ret);
}

int			pass_digit_space(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int			pass_space_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

int			*copy_int(int *vertex, int nu)
{
	int		i;
	int		*copy;

	i = -1;
	if (!(copy = (int *)malloc(sizeof(int) * nu)))
		return (NULL);
	while (++i < nu)
		copy[i] = vertex[i];
	return (copy);
}
