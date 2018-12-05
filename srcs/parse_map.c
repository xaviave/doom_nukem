/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_map.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 13:25:17 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 14:10:23 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void		return_error(int error)
{
	if (!error)
		ft_printf("\nError 0 : No args, need a map\n");
	else if (error == 1)
		ft_printf("\nError 1 : Bad name, must finish by .dk & have one char before\n");
	else if (error == 2)
		ft_printf("\nError 2 : File doesn't exist or can't be open\n");
	exit(0);
}

t_level		*parse_file(int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line))
	{

		i++;
	}
}

void		parse_map(int ac, char **av, t_level *level)
{
	char	*str;
	int		fd;
	int		diff;

	if (ac != 2 || ft_strlen(av[1]) < 4)
		return_error(ac != 2 ? 0 : 1);
	str = ft_strsub(av[1], ft_strlen(av[1]) - 3, ft_strlen(av[1]));
	diff = ft_strcmp(str, ".dk");
	free(str);
	if (diff)
		return_error(1);
	fd = open(av[1], O_RDONLY);
	if (fd < 1)
		return_error(2);
	level = parse_file(fd);
}