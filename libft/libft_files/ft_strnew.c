/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 15:07:56 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 14:19:15 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strnew(size_t size)
{
	char *newstr;

	if ((newstr = (char *)malloc(size + 1)) == NULL)
		return (NULL);
	else
		ft_bzero(newstr, size + 1);
	return (newstr);
}
