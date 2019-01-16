/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cmerel <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 15:24:12 by cmerel       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 15:16:25 by cmerel      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include <SDL2/SDL.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <math.h>

typedef struct		s_size
{
	int				len_x;
	int				len_y;
}					t_size;

typedef struct		s_cam
{
	t_sector		sector;
	t_tree			tree;
	float			x;
	float			y;
	float			z;
	double			dirX;
	double			dirY;
	double			rayX;
	double			rayY;
}					t_cam;

typedef struct		s_tree
{
	int				key;
	int				*left;
	int				*right;
}					t_tree

typedef struct		s_vertex
{
	float			x;
	float			y;
}					t_vertex;

typedef struct		s_linedef
{
	float			x;
	float			y;
	t_sidedef		side[2];
}					t_linedef;

typedef struct		s_sidedef
{
	t_vertex		point;
	int				side_line;
	char			upper[8];
	char			middle[8];
	char			lower[8];
	float			texture;
}					t_sidedef;

typedef struct		s_sector
{
	t_sidedef		side;
	float			h_floor;
	float			h_ceill;
	float			tex_floor;
	float			tex_ceill;
	char			*neighbors; //secteur voisin 
}					t_sector

//struct level qui prend tout en compte pr le level
typedef sruct		s_level
{
	t_vertex		point;
	t_linedef		line;
	t_sidedef		side;
	t_sector		sector;
}					*next;

void	new_tree(t_tree **tree, unsigned int x);
int		main(int argc, char **argv);

#endif
