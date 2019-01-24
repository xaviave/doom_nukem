/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 16:03:34 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 16:41:28 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "tools.h"

# include "../minilibx_macos/mlx.h"

/*
** Test graphique
*/ 

# define W 1280
# define H 800

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
	t_level				*level;
	int					z;
	int					x;
	int					y;
}						t_mem;

void					ft_create_img(t_mem *mem);
void					ft_put_pixel(t_mem *mem, int x, int y, t_color color);
t_color					get_color(int a, t_mem *mem);
void					render_map(t_mem *mem);
void					draw_line(t_mem *mem);
void					draw_to_line(int x1, int y1, int x2, int y2, t_mem *mem);
void					fill_column(int x, int y1, int y2, t_mem *mem);
void					draw_camera(t_mem *mem);
void					draw_minimap(t_mem *mem);
void					draw_square(t_mem *mem);
void					draw_circle(t_mem *mem);
void 					refresh_screen(t_mem *mem);
void					event_loop(t_mem *mem);
void					change_color(t_color *color, int hex);

/*
** event.c
*/

int						mouse_move_hook(int x, int y, t_mem *mem);
int						mouse_click_hook(int k, int x, int y, t_mem *mem);
int						add_key(int k, t_mem *mem);
int						remove_key(int k, t_mem *mem);
int						cross_close(t_mem *mem);

/*
** send_info.c
*/

int						send_vx(t_level *level, int id);
int						send_vy(t_level *level, int id);
int						send_l_vx(t_level *level, int id_l, int vertex);
int						send_l_vy(t_level *level, int id_l, int vertex);

/*
** math.c
*/

int						return_min(int x1, int x2);
void					intersect(float x1, float y1, float x2, float y2, float x3,
	float y3, float x4, float y4, float *x, float *y);
int						fn_cross(float x1, float y1, float x2, float y2);


#endif
