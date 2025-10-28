/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mm_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:26:25 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/28 01:58:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_minimap_keys(t_data *data)
{
	double		zoom_step;
	static int	prev_m = 0;
	int			curr_m;

	curr_m = mlx_is_key_down(data->mlx, MLX_KEY_M);
	if (curr_m && !prev_m)
	{
		data->minimap.show = !data->minimap.show;
		data->minimap.img->enabled = data->minimap.show;
	}
	prev_m = curr_m;
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

/*t_dpoint	minimap_px_to_world_rot(t_data *data, int px, int py)
{
	t_dpoint	loc;
	t_dpoint	dr;
	t_dpoint	w;

	loc = pixels_to_local_tiles(data, px, py);
	dr = rotate_local_to_world_delta(data, loc);
	w.x = data->player.pos_x + dr.x;
	w.y = data->player.pos_y + dr.y;
	return (w);
}*/

// Renvoie la position "monde" correspondant au pixel minimap (px,py)
// en tenant compte de la rotation: haut minimap = direction joueur.
t_dpoint	minimap_px_to_world_rot(t_data *d, int px, int py)
{
	t_dpoint	w;
	double		scale;
	double		lx;
	double		ly;
	double		fx;
	double		fy;
	double		rx;
	double		ry;
	int			cx;
	int			cy;

	cx = d->minimap.wpx / 2;
	cy = d->minimap.hpx / 2;
	scale = (double)d->minimap.tile * d->minimap.zoom;
	lx = ((double)px - (double)cx) / scale;
	ly = -(((double)py - (double)cy) / scale);
	fx = d->player.dir_x;
	fy = d->player.dir_y;
	rx = fy;
	ry = -fx;
	w.x = d->player.pos_x + lx * rx + ly * fx;
	w.y = d->player.pos_y + lx * ry + ly * fy;
	return (w);
}
