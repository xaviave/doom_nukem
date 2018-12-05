/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_merge_sort.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:27:39 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:27:39 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static int		*ft_merge(int *left, int mid, int *right, int dim)
{
	int		i;
	int		j;
	int		k;
	int		*frsh;

	if (!(frsh = ft_memalloc((mid + dim) * sizeof(int))))
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (i < mid && j < dim)
	{
		if (left[i] < right[j])
			frsh[k++] = left[i++];
		else
			frsh[k++] = right[j++];
	}
	while (i < mid)
		frsh[k++] = left[i++];
	while (j < dim)
		frsh[k++] = right[j++];
	return (frsh);
}

static int		*ft_sort(int *tab, int length)
{
	int		*left;
	int		*right;
	int		mid;
	int		dim;

	if (length < 2)
		return (tab);
	mid = length / 2;
	dim = length - mid;
	if (!(left = (int *)ft_memalloc(mid * sizeof(int))))
		return (NULL);
	if (!(right = (int *)ft_memalloc(dim * sizeof(int))))
		return (NULL);
	ft_memcpy(left, tab, mid * sizeof(int));
	ft_memcpy(right, tab + mid, dim * sizeof(int));
	ft_sort(left, mid);
	ft_sort(right, dim);
	free(tab);
	if (!(tab = ft_merge(left, mid, right, dim)))
		return (NULL);
	free(left);
	free(right);
	return (tab);
}

int				*ft_merge_sort(int *tab, int length)
{
	int		*frsh;

	if (!tab)
		return (NULL);
	if (!(frsh = (int *)ft_memalloc(length * sizeof(int))))
		return (NULL);
	frsh = ft_memcpy(frsh, tab, length * sizeof(int));
	return (ft_sort(frsh, length));
}
