/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:56:03 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/12 16:20:12 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	map_at(t_data *data, int x, int y)
{
	int		len;
	char	c;

	if (y < 0 || y >= data->tiles_y || !data->map[y])
		return ('1');
	len = line_len_no_nl(data->map[y]);
	if (x < 0 || x >= len)
		return ('1');
	c = data->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		c = '0';
	return (c);
}

void	set_camera_plane(t_player *player)
{
	double	f;

	f = 0.66;
	player->plane_x = -player->dir_y * f;
	player->plane_y = player->dir_x * f;
}

void	dda_init_axis(double *delta, double dir)
{
	if (dir == 0.0)
		*delta = 1e30;
	else
		*delta = fabs(1.0 / dir);
}

double	get_dt_seconds(t_data *data)
{
	struct timeval	tv;
	long			now_us;
	double			dt;

	gettimeofday(&tv, NULL);
	now_us = (tv.tv_sec * 1000000L) + tv.tv_usec;
	if (data->last_us == 0)
	{
		data->last_us = now_us;
		return (0.0);
	}
	dt = (double)(now_us - data->last_us) / 1000000.0;
	data->last_us = now_us;
	if (dt > 0.05)
		dt = 0.05;
	return (dt);
}
