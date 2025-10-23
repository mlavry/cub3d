/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:21:06 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/23 19:54:08 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_data *data, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= data->tiles_x || my >= data->tiles_y)
		return (1);
	return (data->map[my][mx] == '1');
}

static void	try_move(t_data *d, double dx, double dy)
{
	const double	r = 0.20;
	double			new_x;
	double			new_y;
	double			cx;
	double			cy;

	new_x = d->player.pos_x + dx;
	new_y = d->player.pos_y + dy;
	cx = -r;
	if (dx > 0)
		cx = r;
	cy = -r;
	if (dy > 0)
		cy = r;
	if (!is_wall(d, (int)(new_x + cx), (int)(d->player.pos_y)))
		d->player.pos_x = new_x;
	if (!is_wall(d, (int)(d->player.pos_x), (int)(new_y + cy)))
		d->player.pos_y = new_y;
}

static void	rotate_player(t_player *p, double ang)
{
	double	old_dir_x;
	double	old_plane_x;
	double	c;
	double	s;

	c = cos(ang);
	s = sin(ang);
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * c - p->dir_y * s;
	p->dir_y = old_dir_x * s + p->dir_y * c;
	p->plane_x = p->plane_x * c - p->plane_y * s;
	p->plane_y = old_plane_x * s + p->plane_y * c;
}

void	handle_movement(t_data *d)
{
	double	dt;
	double	speed;
	double	rot;

	dt = get_dt_seconds(d);
	speed = 4.0 * dt;
	rot = 2.2 * dt;
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= 1.8;
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
		try_move(d, d->player.dir_x * speed, d->player.dir_y * speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
		try_move(d, -d->player.dir_x * speed, -d->player.dir_y * speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
		try_move(d, d->player.dir_y * speed, -d->player.dir_x * speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
		try_move(d, -d->player.dir_y * speed, d->player.dir_x * speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		rotate_player(&d->player, -rot);
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		rotate_player(&d->player, rot);
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
}
