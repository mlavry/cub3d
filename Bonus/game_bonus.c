/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:23:01 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/04 23:38:05 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	compute_ray_dir(t_data *data, int x, double *rdx, double *rdy)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (double)data->monitor_w - 1.0;
	*rdx = data->player.dir_x + data->player.plane_x * camera_x;
	*rdy = data->player.dir_y + data->player.plane_y * camera_x;
}

static void	project_column(t_data *data, double dist, int *y0, int *y1)
{
	int	line_h;
	int	mid;

	if (dist < 1e-6)
		dist = 1e-6;
	line_h = (int)((double)data->monitor_h / dist);
	mid = data->monitor_h / 2;
	*y0 = -line_h / 2 + mid;
	*y1 = line_h / 2 + mid;
}

void	render_frame_bonus(void *param)
{
	int			x;
	t_column	c;
	t_data		*data;
	double		dt;

	data = (t_data *)param;
	dt = get_dt_seconds(data);
	handle_movement_bonus(data, dt);
	doors_update(data, dt);
	handle_doors_movement(data);
	set_background(data);
	x = 0;
	while (x < data->monitor_w)
	{
		c.x = x;
		compute_ray_dir(data, x, &c.rdx, &c.rdy);
		c.dist = dda_first_hit_bonus(data, c.rdx, c.rdy, &c);
		project_column(data, c.dist, &c.y0, &c.y1);
		draw_textured_column_bonus(data, &c);
		x++;
	}
	handle_minimap_keys(data);
	minimap_draw_rot_fov(data);
	weapon_draw(data, dt);
}

void	launch_game_bonus(t_data *data)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!data->mlx)
		return ;
	set_image(data);
	init_textures_bonus(data);
	weapon_init(data);
	minimap_init(data);
	init_mouse(data);
	init_player(data);
	init_all_doors(data);
	mlx_loop_hook(data->mlx, render_frame_bonus, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
