/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: mem->z19/01/10 14:14:48 by mel-akio     #+#   ##    ##    #+#       */
/*   Updated: mem->z19/01/10 15:58:17 by mel-akio    ###    #+. /#+    ###.fr     */
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

int add_key(int k, t_mem *mem)
{
    if (!mem->level->player.keys[k])
        mem->level->player.keys[k] = 1;
    return (0);
}

int remove_key(int k, t_mem *mem)
{
    mem->level->player.keys[k] = 0;
    return (0);
}

static int cross_close(t_mem *mem)
{
    if (mem)
        ;
    exit(1);
    return (1);
}

int send_vx(t_level *level, int id)
{
    int i;

    i = -1;
    while (++i < level->nb_vertex)
    {
        if (level->vertex[i].id == id)
            return (level->vertex[i].x);
    }
    return (0);
}

int send_vy(t_level *level, int id)
{
    int i;

    i = -1;
    while (++i < level->nb_vertex)
    {
        if (level->vertex[i].id == id)
            return (level->vertex[i].y);
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
            mem->coord.x1 = send_vx(mem->level, mem->level->sector[i].vertex[j]) * mem->z;
            mem->coord.y1 = send_vy(mem->level, mem->level->sector[i].vertex[j]) * mem->z;
            if (j + 1 == mem->level->sector[i].nb_vertex)
            {
                mem->coord.x2 = send_vx(mem->level, mem->level->sector[i].vertex[0]) * mem->z;
                mem->coord.y2 = send_vy(mem->level, mem->level->sector[i].vertex[0]) * mem->z;
            }
            else
            {
                mem->coord.x2 = send_vx(mem->level, mem->level->sector[i].vertex[j + 1]) * mem->z;
                mem->coord.y2 = send_vy(mem->level, mem->level->sector[i].vertex[j + 1]) * mem->z;
            }
            draw_line(mem);
            draw_circle(mem);
        }
    }

    draw_camera(mem);
    mem->coord.x2 = ((3* mem->z * (cos(mem->level->player.angle)) + mem->coord.x1));
    mem->coord.y2 = ((3* mem->z *(sin(mem->level->player.angle)) + mem->coord.y1));
    draw_line(mem);
}

int update_keys(t_mem *mem)
{
    int i;

    i = 0;

    while (i != 127)
    {
        if (mem->level->player.keys[i])
        {
            if (i == TOUCH_LEFT)
            {
                mem->level->player.x -= 5;
            }
            else if (i == TOUCH_RIGHT)
            {
                mem->level->player.x += 5;
            }
            else if (i == TOUCH_UP)
            {
                mem->level->player.y -= 5;
            }
            else if (i == TOUCH_DOWN)
            {
                mem->level->player.y += 5;
            }
            else if (i == TOUCH_A)
            {
                mem->level->player.angle -= 0.05;
            }
            else if (i == TOUCH_D)
            {
                mem->level->player.angle += 0.05;
            }
            else if (i == TOUCH_NUMPAD_LESS)
                mem->z -= 2;
            else if (i == TOUCH_NUMPAD_PLUS)
                mem->z += 2;
            else if (i == TOUCH_ECHAP)
            {
                exit(1);
            }
        }
        i++;
    }
    refresh_screen(mem);
    return (1);
}

void refresh_screen(t_mem *mem)
{
     if (mem->img.ptr)
        mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);
    ft_create_img(mem);
    draw_minimap(mem);

    mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->img.ptr, 100, 100);
}

void event_loop(t_mem *mem)
{
    mlx_hook(mem->win.win_ptr, 17, 0L, cross_close, mem);
    mlx_hook(mem->win.win_ptr, MOTION_NOTIFY, PTR_MOTION_MASK,
            mouse_move_hook, mem);
    mlx_mouse_hook(mem->win.win_ptr, mouse_click_hook, mem);

    mlx_hook(mem->win.win_ptr, 2, 1L << 0, add_key, mem);
    mlx_hook(mem->win.win_ptr, 3, 1L << 1, remove_key, mem);
    mlx_loop_hook(mem->mlx_ptr, update_keys, mem);
    mlx_loop(mem->mlx_ptr);
}
