/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:27:27 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/29 19:25:11 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_mouse(t_data *data)
{
	data->mouse.sens = 0.0025;
	data->mouse.lock = true;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(data->mlx, data->monitor_w / 2, data->monitor_h / 2);
}

void	handle_mouse(t_data *data)
{
	t_point	mouse_pos;
	t_point	mid;
	int		dx;
	double	ang;

	if (!data->mouse.lock)
		return ;
	mid.x = data->monitor_w / 2;
	mid.y = data->monitor_h / 2;
	mlx_get_mouse_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	dx = mouse_pos.x - mid.x;
	if (dx != 0)
	{
		ang = dx * data->mouse.sens;
		rotate_player(&data->player, ang);
		mlx_set_mouse_pos(data->mlx, mid.x, mid.y);
	}
}

static void	handle_sensi_mouse(t_data *data)
{
	static int	left_br = 0;

	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_BRACKET))
	{
		if (!left_br)
		{
			data->mouse.sens -= 0.0002;
			if (data->mouse.sens < 0.0005)
				data->mouse.sens = 0.0005;
			left_br = 1;
		}
	}
	else
		left_br = 0;
	handle_sensi_right_mouse(data);
}

static void	handle_mouse_keys(t_data *data)
{
	static int	p_pressed = 0;

	if (mlx_is_key_down(data->mlx, MLX_KEY_P))
	{
		if (!p_pressed)
		{
			data->mouse.lock = !data->mouse.lock;
			if (data->mouse.lock)
			{
				mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
				mlx_set_mouse_pos(data->mlx, data->monitor_w / 2,
					data->monitor_h / 2);
			}
			else
				mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
			p_pressed = 1;
		}
	}
	else
		p_pressed = 0;
	handle_sensi_mouse(data);
}

void	handle_movement_bonus(t_data *d)
{
	double	dt;
	double	speed;
	double	rot;

	dt = get_dt_seconds(d);
	handle_mouse(d);
	handle_mouse_keys(d);
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
