/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 01:55:04 by mlavry            #+#    #+#             */
/*   Updated: 2025/08/29 03:22:36 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(mlx_image_t *img)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	while (y < (int)img->height)
	{
		if (y < (int)img->height / 2)
			color = C_TOP;
		else
			color = C_FLOOR;
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	try_rect(t_data *data)
{
	t_rect		rect;
	mlx_image_t	*img;

	img = mlx_new_image(data->mlx, (int32_t)data->monitor_w,
			(int32_t)data->monitor_h);
	mlx_image_to_window(data->mlx, img, 0, 0);
	rect.x = 1;
	rect.y = 1;
	rect.size_x = data->monitor_w / 4 - 1;
	rect.size_y = data->monitor_h / 4 - 1;
	fill_rect(data, img, rect, C_WHITE);
}

void	set_background(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	draw_background(data->window.img);
	draw_fake_wall(data->window.img);
	draw_minimap(data);
	//try_rect(data);
}

void	set_image(t_data *data)
{
	int32_t	win_w;
	int32_t	win_h;

	mlx_get_monitor_size(0, &win_w, &win_h);
	data->monitor_h = (int)win_h;
	data->monitor_w = (int)win_w;
	printf("\nMonitor W : %d\nMonitor H : %d\n", data->monitor_w, data->monitor_h);
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
	minimap_init(data);
	mlx_loop_hook(data->mlx, set_background, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
