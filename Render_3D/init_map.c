/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 01:55:04 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/23 20:57:36 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				data->player.pos_x = x + 0.5;
				data->player.pos_y = y + 0.5;
				init_player_dir(data, x, y);
				set_camera_plane(&data->player);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	draw_background(t_data *data, mlx_image_t *img)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	while (y < (int)img->height)
	{
		if (y < (int)img->height / 2)
			color = rgb_to_u32(data->param.c_rgb[0], data->param.c_rgb[1],
					data->param.c_rgb[2]);
		else
			color = rgb_to_u32(data->param.f_rgb[0], data->param.f_rgb[1],
					data->param.f_rgb[2]);
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	set_background(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	draw_background(data, data->window.img);
	//draw_minimap(data);
}

void	set_image(t_data *data)
{
	int32_t	win_w;
	int32_t	win_h;

	mlx_get_monitor_size(0, &win_w, &win_h);
	data->monitor_h = (int)win_h;
	data->monitor_w = (int)win_w;
	mlx_set_window_size(data->mlx, (int32_t)win_w, (int32_t)win_h);
	data->window.img = mlx_new_image(data->mlx, win_w, win_h);
	mlx_image_to_window(data->mlx, data->window.img, 0, 0);
}

void	launch_game(t_data *data)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!data->mlx)
		return ;
	set_image(data);
	init_textures(data);
	//minimap_init(data);
	init_player(data);
	mlx_loop_hook(data->mlx, render_frame_basic, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
