/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 01:15:27 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/29 23:46:39 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap_init(t_data *data)
{
	data->minimap.tile = 16;
	data->minimap.margin = 8;
	data->minimap.wpx = data->monitor_w / 4;
	data->minimap.hpx = data->monitor_h / 4;
	data->minimap.img = mlx_new_image(data->mlx,
			data->minimap.wpx, data->minimap.hpx);
	if (!data->minimap.img)
		return ;
	if (mlx_image_to_window(data->mlx, data->minimap.img, 8, 8) < 0)
	{
		mlx_delete_image(data->mlx, data->minimap.img);
		data->minimap.img = NULL;
	}
	data->minimap.img->enabled = true;
	data->minimap.show = 0;
	data->minimap.zoom = 1.0;
	data->minimap.fov_deg = 60.0;
	data->minimap.radius = mm_compute_radius(&data->minimap);
}

static void	minimap_clear(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->minimap.hpx)
	{
		x = 0;
		while (x < data->minimap.wpx)
		{
			mlx_put_pixel(data->minimap.img, x, y, C_MINI_VOID);
			x++;
		}
		y++;
	}
}

/*Équation d’un cercle : 
𝑥2 + 𝑦2 ≤ 𝑟2 
Si le point (dx, dy) respecte cette équation → il est dans le disque.*/
void	minimap_draw_disk(t_data *data)
{
	t_point	c;
	int		r;
	int		dx;
	int		dy;

	c.x = data->minimap.wpx / 2;
	c.y = data->minimap.hpx / 2;
	r = data->minimap.radius;
	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
				mlx_put_pixel(data->minimap.img, c.x + dx, c.y + dy, C_DARK);
			dx++;
		}
		dy++;
	}
}

void	draw_player_center(t_data *data, t_point c)
{
	int	r;
	int	x;
	int	y;

	r = mm_player_px_radius(data);
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
				mlx_put_pixel(data->minimap.img, c.x + x, c.y + y, C_RED);
			x++;
		}
		y++;
	}
}

void	minimap_clear_disk_and_player(t_data *data)
{
	minimap_clear(data);
	minimap_draw_disk(data);
}
