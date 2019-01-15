/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/12 16:22:43 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/12 16:23:29 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int mouse_move_hook(int x, int y, t_mem *mem)
{
    if (x || y || mem)
        return (0);
    return (0);
}

int mouse_click_hook(int k, int x, int y, t_mem *mem)
{
    if (k || x || y || mem)
        return (0);
    return (0);
}

int key_hook(int k, t_mem *mem)
{
    if (k == TOUCH_LEFT)
        mem->level->player.x -= 5;
    if (k == TOUCH_RIGHT)
        mem->level->player.x += 5;
    if (k == TOUCH_UP)
        mem->level->player.y -= 5;
    if (k == TOUCH_DOWN)
        mem->level->player.y += 5;
    if (k == TOUCH_NUMPAD_LESS)
        mem->z -= 2;
    if (k == TOUCH_NUMPAD_PLUS)
        mem->z += 2;
    if (k == TOUCH_ECHAP)
    {
        exit(1);
    }
    render_map(mem);
    return (0);
}

static int cross_close(t_mem *mem)
{
    if (mem)
        ;
    exit(1);
    return (1);
}

int send_vx(t_level *level, int id, int nb)
{
    int i;
    int j;

    i = -1;
    while (++i < level->nb_linedef)
    {
        if (level->linedef[i].id == id)
            break ;
    }
    j = -1;
    while (++j < level->nb_vertex)
    {
         if (level->vertex[i].id == i)
            return (nb == 1 ? level->vertex[level->linedef[i].id_v1].x
                : level->vertex[level->linedef[i].id_v2].x);
    } 
    return (0);
}

int send_vy(t_level *level, int id, int nb)
{
    int i;
    int j;

    i = -1;
    while (++i < level->nb_linedef)
    {
        if (level->linedef[i].id == id)
            break ;
    }
    j = -1;
    while (++j < level->nb_vertex)
    {
         if (level->vertex[i].id == i)
            return (nb == 1 ? level->vertex[level->linedef[i].id_v1].y
                : level->vertex[level->linedef[i].id_v2].y);
    } 
    return (0);
}

void draw_minimap(t_mem *mem)
{
    int i;
    int j;

    i = -1;
    mlx_clear_window(mem->mlx_ptr, mem->win.win_ptr);
    while (++i < mem->level->nb_sector)
    {
        j = -1;
        while (++j < mem->level->sector[i].nb_vertex)
        {
                mem->coord.x1 = send_vx(mem->level, mem->level->sector[i].linedef[j], 1) * mem->z + 100;
                mem->coord.y1 = send_vy(mem->level, mem->level->sector[i].linedef[j], 1) * mem->z + 100;
                if (j + 1 == mem->level->sector[i].nb_vertex)
                {
                    mem->coord.x2 = send_vx(mem->level, mem->level->sector[i].linedef[0], 2) * mem->z + 100;
                    mem->coord.y2 = send_vy(mem->level, mem->level->sector[i].linedef[0], 2) * mem->z + 100;
                }
                else\
                {
                    mem->coord.x2 = send_vx(mem->level, mem->level->sector[i].linedef[j + 1], 2) * mem->z + 100;
                    mem->coord.y2 = send_vy(mem->level, mem->level->sector[i].linedef[j + 1], 2) * mem->z + 100;
                }
                draw_line(mem);
                draw_circle(mem);
        }
        
    }
    draw_camera(mem);
}

void render_map(t_mem *mem)
{
    if (mem->img.ptr)
        mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);
    ft_create_img(mem);
    draw_minimap(mem);
    mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->img.ptr, 0, 0);
    mlx_hook(mem->win.win_ptr, 17, 0L, cross_close, mem);
    mlx_hook(mem->win.win_ptr, MOTION_NOTIFY, PTR_MOTION_MASK,
            mouse_move_hook, mem);
    mlx_mouse_hook(mem->win.win_ptr, mouse_click_hook, mem);
    mlx_key_hook(mem->win.win_ptr, key_hook, mem);
    mlx_loop(mem->mlx_ptr);
}