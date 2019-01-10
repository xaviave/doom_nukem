/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 16:03:34 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 15:02:00 by mel-akio    ###    #+. /#+    ###.fr     */
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

# include "../minilibx_macos/mlx.h"

/*
** Structures & Binary tree
*/

typedef struct      	s_vertex
{
	float           	x;
	float           	y;
	int					id;
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
	int					id;
	float           	h_floor;
	float           	h_ceil;
	char           		tex_floor; // no initialise
	char           		tex_ceil; // no initialise
	int					nb_vertex;
	int					*vertex; // id of vertex which compose the sector
	int					nb_neighbors;
	int           	 	*neighbors; // id of neighbors's sector 
}                   	t_sector;

typedef struct      	s_level
{
	int					nb_vertex;
	t_vertex        	*vertex; //coord vertex
	int					nb_sector;
	t_sector        	*sector;
	t_linedef       	line; // no initialise
	t_sidedef       	side[2]; // no initialise
	t_player			player;
	struct s_level		*next;
}                   	t_level;

/*
**	Parsing functions & Stucture
*/

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

void					parse_map(int aac, char **av, t_parse *parse);
void					parse_sector(t_parse *parse, char *str);
void					parse_vertex(t_parse *parse, char *str);
void					parse_to_level(t_parse *parse, t_level *level);

/*
**	Error case & free
*/

void					free_parse(t_parse *parse);
void					free_level(t_level *level);
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
int						list_len_s(t_psector *list);
int						list_len_v(t_pvertex *list);

/*
** Test graphique
*/

# define W 1280
# define H 720

typedef struct			s_coord
{
	int					x1;
	int					y1;
	int					x2;
	int					y2;
}						t_coord;

typedef struct			s_line
{
	int					dx;
	int					sx;
	int					dy;
	int					sy;
	int					err;
	int					e2;
}						t_line;

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		a;
	int					i;
}						t_color;

typedef struct			s_win
{
	void				*win_ptr;
	int					width;
	int					height;
}						t_win;

typedef struct			s_img
{
	void				*ptr;
	char				*data;
	int					sizeline;
	int					bpp;
	int					endian;
}						t_img;

typedef struct			s_mem
{
	t_win				win;
	t_img				img;
	t_color				color;
	void				*mlx_ptr;
	t_coord				coord;
}						t_mem;

void					ft_create_img(t_mem *mem);
void					ft_put_pixel(t_mem *mem, int x, int y, t_color color);
t_color					get_color(int a, t_mem *mem);
void					render_map(t_mem *mem, t_level *level);
void 					draw_line(t_mem *mem);


/*
** keyboard touch value
*/

# define MOUSE_ZOOM_IN 5
# define MOUSE_ZOOM_OUT 4
# define TOUCH_1 18
# define TOUCH_2 19
# define TOUCH_3 20
# define TOUCH_4 21
# define TOUCH_5 23
# define TOUCH_6 22
# define TOUCH_7 26
# define TOUCH_8 28
# define TOUCH_9 25
# define TOUCH_0 29
# define TOUCH_Q 12
# define TOUCH_W 13
# define TOUCH_E 14
# define TOUCH_R 15
# define TOUCH_T 17
# define TOUCH_Y 16
# define TOUCH_A 0
# define TOUCH_S 1
# define TOUCH_D 2
# define TOUCH_F 3
# define TOUCH_G 5
# define TOUCH_Z 6
# define TOUCH_X 7
# define TOUCH_C 8
# define TOUCH_V 9
# define TOUCH_B 11
# define TOUCH_ECHAP 53
# define TOUCH_ENTER 36
# define TOUCH_LEFT 123
# define TOUCH_RIGHT 124
# define TOUCH_DOWN 125
# define TOUCH_UP 126
# define TOUCH_NUMPAD_0 82
# define TOUCH_NUMPAD_1 83
# define TOUCH_NUMPAD_2 84
# define TOUCH_NUMPAD_3 85
# define TOUCH_NUMPAD_4 86
# define TOUCH_NUMPAD_5 87
# define TOUCH_NUMPAD_6 88
# define TOUCH_NUMPAD_7 89
# define TOUCH_NUMPAD_8 91
# define TOUCH_NUMPAD_9 92
# define TOUCH_NUMPAD_POINT 65
# define TOUCH_NUMPAD_ENTER 76
# define TOUCH_NUMPAD_PLUS 69
# define TOUCH_NUMPAD_LESS 78
# define TOUCH_NUMPAD_TIMES 67
# define TOUCH_NUMPAD_DIVIDE 75
# define TOUCH_NUMPAD_NUM 71
# define TOUCH_NUMPAD_INSERT 114
# define TOUCH_NUMPAD_END 119
# define TOUCH_NUMPAD_DELL 117
# define TOUCH_NUMPAD_PAGEUP 116
# define TOUCH_NUMPAD_PAGEDOWN 121
# define TOUCH_NUMPAD_HOME 115
# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6

#endif
