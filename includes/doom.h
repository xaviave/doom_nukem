/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 16:03:34 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 17:44:00 by mel-akio    ###    #+. /#+    ###.fr     */
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
	int					w;
	int					h;
}						t_img;

typedef struct 			s_vector
{
	float 				tx1;
	float 				tx2;
	float 				ty1;
	float 				ty2;
	float 				tz1;
	float 				tz2;
	float				iz1;
	float				ix1;
	float				iz2;
	float				ix2;
}						t_vector;

typedef struct 			s_render
{
	t_fcoord			p1;
	t_fcoord			p2;
	t_fcoord			step;
	t_fcoord			top;
}						t_render;

	

typedef struct			s_mem
{
	t_win				win;
	t_img				img;
	t_color				color;
	void				*mlx_ptr;
	t_coord				coord;
	t_level				*level;
	float				z;
	int					x;
	int					y;
	char				*fill_screen;
	int					mouse_x;
	int					mouse_y;
	int					camera_x;
	int					camera_y;
	t_coord				step_bot;
	t_img				gun;
	t_img				crosshair;
	t_img				monster;
	float				cos_angle;
	float				sin_angle;
	int					FPS;
	struct timeval  	tv1, tv2;
	t_line				line;
	t_line				line2;
	t_line				line3;
	t_line				line4;
	t_coord 			p3;
	t_coord 			p4;
	t_coord 			p5;
	t_fcoord 			p1;
	t_fcoord 			p2;
	t_fcoord 			step;
	t_fcoord 			top;
}						t_mem;

void					ft_create_img(t_mem *mem);
void					ft_put_pixel(t_mem *mem, int x, int y, t_color color);
t_color					get_color(int a, t_mem *mem);
void					render_map(t_mem *mem, int sect);
void 					render_sprites(t_mem *mem, int sect);
void					draw_line(t_mem *mem);
void					draw_to_line(int x1, int y1, int x2, int y2, t_mem *mem);
void					fill_column(int x, int sect, t_mem *mem);
void					draw_camera(t_mem *mem);
void					draw_minimap(t_mem *mem);
void					draw_square(t_mem *mem);
void					draw_circle(t_mem *mem);
void 					refresh_screen(t_mem *mem);
void					event_loop(t_mem *mem);
void					change_color(t_color *color, int hex);
t_color					set_color(int a);
void					make_mask(t_mem *mem, t_img *img, char xpm[255]);

/*
** event.c
*/

int						mouse_move_hook(int x, int y, t_mem *mem);
int						mouse_click_hook(int k, int x, int y, t_mem *mem);
int						add_key(int k, t_mem *mem);
int						remove_key(int k, t_mem *mem);
int						cross_close(t_mem *mem);
int						camera_move(t_mem *mem);
int						update_keys(t_mem *mem);


/*
** send_info.c
*/

int						send_vx(t_level *level, int id);
int						send_vy(t_level *level, int id);
int						send_l_vx(t_level *level, int id_l, int vertex);
int						send_l_vy(t_level *level, int id_l, int vertex);
int						send_l_id(t_mem *mem, int id);
int						send_s_id(t_mem *mem, int id);
int						next_sector(t_mem *mem, int linedef_id, int actual_sector);
void					fill_n_sector(t_mem *mem, int i);
int						double_int(int *tab, int nu, int nb);
void					sort_dist_monsters(t_mem *mem);


/*
** math.c
*/

int						return_min(int x1, int x2);
void					intersect(float x1, float y1, float x2, float y2, float x3,
	float y3, float x4, float y4, float *x, float *y);
int						fn_cross(float x1, float y1, float x2, float y2);
int						player_sector(t_mem *mem);
void					physics(t_mem *mem);
void 					jump(t_mem *mem);
void					player_animation(t_mem *mem);
float					distance(float x1, float y1, float x2, float y2);

/*
** get infos
*/

int						further_sector(t_mem *mem, int sector);

/*
** textures process
*/

void					textures_init(t_mem *mem);
void					put_img_to_img(t_mem *mem, t_img *img, int x, int y, float dist);

/*
** animation
*/
void					shoot(t_mem *mem, char frame);

/*
** music // free
*/
void					init_sound(t_mem *mem);
void					play_music(t_audio m);
void					play_audio(t_audio m);
void					free_audio(t_mem *mem);
#endif
