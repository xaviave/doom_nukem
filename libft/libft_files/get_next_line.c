/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:58 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 14:38:10 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static int		no_read(char **line, char **lastbuf, char *next)
{
	char	*tmp;

	if (!(*line = ft_strsub(*lastbuf, 0, next - *lastbuf)))
		return (-1);
	tmp = *lastbuf;
	if (!(*lastbuf = ft_strdup(next + 1)))
		return (-1);
	ft_memdel((void**)&tmp);
	return (1);
}

static void		clear_link(int fd, t_lastbuf **lst)
{
	t_lastbuf		*tmp;
	t_lastbuf		*before;

	before = *lst;
	if (before->fd != fd)
		while (before->next->fd != fd)
			before = before->next;
	tmp = *lst;
	while (tmp->fd != fd)
		tmp = tmp->next;
	if (tmp == *lst)
		*lst = tmp->next;
	else
		before->next = tmp->next;
	ft_memdel((void**)&(tmp->lastbuf));
	ft_memdel((void**)&tmp);
}

static int		fd_next_line(int fd, char **line, char **lastbuf,
		t_lastbuf **lst)
{
	char	*next;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];
	int		ret;
	int		i;

	i = 0;
	*lastbuf = *lastbuf ? *lastbuf : ft_memalloc(1);
	if ((next = ft_strchr(*lastbuf, '\n')))
		return (no_read(line, lastbuf, next));
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = *lastbuf;
		if (!(*lastbuf = ft_strjoin(*lastbuf, buf)))
			return (-1);
		ft_memdel((void**)&tmp);
		if ((next = ft_strchr(*lastbuf, '\n')))
			return (no_read(line, lastbuf, next));
		i = 1;
	}
	i == 1 ? *line = ft_strdup(*lastbuf) : 0;
	clear_link(fd, lst);
	return (ret == -1 ? -1 : i);
}

int				get_next_line(int fd, char **line)
{
	static t_lastbuf	*lst;
	t_lastbuf			*cur;

	if (lst)
	{
		cur = lst;
		while (cur && cur->fd != fd)
			cur = cur->next;
		if (cur)
			return (fd_next_line(fd, line, &cur->lastbuf, &lst));
	}
	if (!(cur = (t_lastbuf *)ft_memalloc(sizeof(t_lastbuf))))
		return (-1);
	cur->fd = fd;
	if (lst)
		cur->next = lst;
	else
		cur->next = NULL;
	lst = cur;
	if (!(cur->lastbuf = (char *)ft_memalloc(sizeof(char))))
		return (-1);
	return (fd_next_line(fd, line, &cur->lastbuf, &lst));
}
