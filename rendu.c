/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:39:37 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/20 17:37:44 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_wall_color(int side)
{
	if (side == 1)
		return (C_WHITE);
	return (C_RED);
}

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

void	render_frame_basic(void *param)
{
	int			x;
	t_column	c;
	t_data		*data;

	data = (t_data *)param;
	set_background(data);
	x = 0;
	while (x < data->monitor_w)
	{
		compute_ray_dir(data, x, &c.rdx, &c.rdy);
		c.dist = dda_first_hit(data, c.rdx, c.rdy, &c.side);
		project_column(data, c.dist, &c.y0, &c.y1);
		draw_vline(data->window.img, x, c.y0, c.y1, get_wall_color(c.side));
		x++;
	}
}
