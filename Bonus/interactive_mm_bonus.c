/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mm_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:26:25 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/28 20:50:30 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_minimap_zoom(t_data *data)
{
	double	zoom_step;

	zoom_step = 0.0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_KP_ADD)
		|| mlx_is_key_down(data->mlx, MLX_KEY_EQUAL))
		zoom_step = 0.02;
	if (mlx_is_key_down(data->mlx, MLX_KEY_KP_SUBTRACT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_MINUS))
		zoom_step = -0.02;
	if (zoom_step != 0.0)
	{
		data->minimap.zoom += zoom_step;
		if (data->minimap.zoom < 0.4)
			data->minimap.zoom = 0.4;
		if (data->minimap.zoom > 3.0)
			data->minimap.zoom = 3.0;
	}
}

void	handle_minimap_keys(t_data *data)
{
	static int	prev_m = 0;
	int			curr_m;

	curr_m = mlx_is_key_down(data->mlx, MLX_KEY_M);
	if (curr_m && !prev_m)
	{
		data->minimap.show = !data->minimap.show;
		data->minimap.img->enabled = data->minimap.show;
	}
	prev_m = curr_m;
	handle_minimap_zoom(data);
}

t_dpoint	minimap_px_to_world_rot(t_data *data, int px, int py)
{
	t_dpoint	loc;
	t_dpoint	dr;
	t_dpoint	w;

	loc = pixels_to_local_tiles(data, px, py);
	dr = rotate_local_to_world_delta(data, loc);
	w.x = data->player.pos_x + dr.x;
	w.y = data->player.pos_y + dr.y;
	return (w);
}

void	minimap_draw_circle_border(t_data *d, uint32_t col)
{
	t_point	c;
	int		r;
	double	a;
	int		x;
	int		y;

	if (!d->minimap.img)
		return ;
	r = d->minimap.radius;
	if (r <= 0)
		return ;
	c.x = d->minimap.wpx / 2;
	c.y = d->minimap.hpx / 2;
	a = 0.0;
	while (a <= 6.283185307179586)
	{
		x = c.x + (int)((double)r * cos(a));
		y = c.y + (int)((double)r * sin(a));
		if (x >= 0 && y >= 0
			&& x < (int)d->minimap.wpx
			&& y < (int)d->minimap.hpx)
			mlx_put_pixel(d->minimap.img, x, y, col);
		a += 0.005;
	}
}
