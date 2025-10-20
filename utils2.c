/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:56:03 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/20 17:35:45 by mlavry           ###   ########.fr       */
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

void	print_player_info(t_data *data)
{
	printf("\n===== PLAYER DEBUG INFO =====\n");
	printf("Position : (%.2f, %.2f)\n",
		data->player.pos_x, data->player.pos_y);
	printf("Direction : (%.2f, %.2f)\n",
		data->player.dir_x, data->player.dir_y);
	printf("Camera plane : (%.2f, %.2f)\n",
		data->player.plane_x, data->player.plane_y);
	printf("=============================\n\n");
}

void	dda_init_axis(double *delta, double dir)
{
	if (dir == 0.0)
		*delta = 1e30;
	else
		*delta = fabs(1.0 / dir);
}
