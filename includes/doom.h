/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 16:03:34 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/16 22:55:07 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdio.h>
# include <stdlib.h>
# include "fcntl.h"
# include <math.h>
# include "../libft/header/libft.h"
/*
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>
# include <SDL2_ttf/SDL_ttf.h>
*/

/*
** Define window size
*/

#define W 1000
#define H 789

#define hfov (0.73f*H)  // Affects the horizontal field of vision
#define vfov (.2f*H)    // Affects the vertical field of vision
#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1)) // Overlap:  Determine whether the two number ranges overlap.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3)) // IntersectBox: Determine whether two 2D-boxes intersect.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0)) // PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct s_xy) { \
		vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
		vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) }) // Intersect: Calculate the point of intersection between two lines.
#define Yaw(y,z) (y + z*player.yaw)

/*
** Structures & Binary tree
*/

typedef struct      	s_vertex
{
	float           	x;
	float           	y;
}                   	t_vertex;

typedef struct      	s_linedef
{
	float           	x;
	float           	y;
}                   	t_linedef;

typedef struct			s_player
{
	int					x;
	int					y;
}						t_player;

typedef struct      	s_sidedef
{
	char            	upper[8];
	char            	middle[8];
	char            	lower[8];
	float           	texture;
}                   	t_sidedef;

typedef struct      	s_sector
{
	float           	h_floor;
	float           	h_ceil;
	char           		tex_floor;
	char           		tex_ceil;
	char            	*neighbors; 
}                   	t_sector;

typedef struct			s_pvertex
{
	int					x;
	int					y;
	int					id;
	struct s_pvertex	*next;
}						t_pvertex;

typedef struct			s_psector
{
	int					id;
	int					ceiling;
	int					ground;
	int					*vertex;
	int					nu_vertex;
	struct s_psector	*next;
}						t_psector;

typedef struct			s_parse
{
	t_pvertex			*vertex;
	t_psector			*sector;
	t_player			player;
}						t_parse;

typedef struct      	s_level
{
	t_vertex        	*point;
	t_linedef       	line;
	t_sidedef       	side[2];
	t_sector        	sector;
	t_player			player;
	struct s_level		*next;
}                   	t_level;

/*
**	Parsing functions
*/

void					parse_map(int aac, char **av, t_parse *parse);
void					parse_sector(t_parse *parse, char *str);
void					parse_vertex(t_parse *parse, char *str);

/*
**	Error case & free
*/

void					free_parse(t_parse *parse);
void					return_error(int error, t_parse *parse);

/*
**	Tools functions
*/

int						check_int(char *tmp);
int						pass_digit_space(char *str);
int						count_int(char *str);
int						*create_vertex(char *str);
void					add_list_v(t_pvertex **vertex, char *y, char *x, char *id);
void					add_list_s(t_psector **sector, char *str);

#endif
