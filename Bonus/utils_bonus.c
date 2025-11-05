/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:35:53 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/05 22:32:29 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_all_doors(t_data *data)
{
	int	x;
	int	y;
	int	i;

	if (allocate_doors(data) == 1)
		return ;
	y = 0;
	i = 0;
	while (y < data->tiles_y && data->map[y])
	{
		x = 0;
		while (x < line_len_no_nl(data->map[y]))
		{
			if (data->map[y][x] == 'P')
			{
				data->doors[i].x = x;
				data->doors[i].y = y;
				data->doors[i].open = 0.0;
				data->doors[i].moving = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	update_close(t_data *data, double speed, double dt, int i)
{
	if (data->doors[i].moving < 0)
	{
		data->doors[i].open -= speed * dt;
		if (data->doors[i].open <= 0.0)
		{
			data->doors[i].open = 0.0;
			data->doors[i].moving = 0;
		}
	}
}

void	doors_update(t_data *data, double dt)
{
	double	speed;
	int		i;

	i = 0;
	speed = 1.5;
	while (i < data->doors_count)
	{
		if (data->doors[i].moving > 0)
		{
			data->doors[i].open += speed * dt;
			if (data->doors[i].open >= 1.0)
			{
				data->doors[i].open = 1.0;
				data->doors[i].moving = 0;
			}
		}
		else if (data->doors[i].moving < 0)
			update_close(data, speed, dt, i);
		i++;
	}
}

int	player_is_in_tile(t_data *data, int tx, int ty)
{
	return ((int)data->player.pos_x == tx && (int)data->player.pos_y == ty);
}

int	init_textures_bonus(t_data *data)
{
	data->textures.north = mlx_load_png(data->param.no_path);
	data->textures.south = mlx_load_png(data->param.so_path);
	data->textures.east = mlx_load_png(data->param.ea_path);
	data->textures.west = mlx_load_png(data->param.we_path);
	data->textures.door = mlx_load_png("Textures/door.png");
	if (!data->textures.north || !data->textures.south || !data->textures.east
		|| !data->textures.west)
	{
		printf("Error when loading textures\n");
		exit (1);
	}
	if ((!data->textures.door))
	{
		printf("Error when loading door texture\n");
		exit (1);
	}
	return (0);
}
