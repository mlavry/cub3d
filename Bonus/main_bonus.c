/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:22:05 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/12 22:18:10 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mm_player_px_radius(t_data *d)
{
	double	r;

	r = 3.0 * d->minimap.zoom;
	if (r < 2.0)
		r = 2.0;
	if (r > (double)d->minimap.radius / 6.0)
		r = (double)d->minimap.radius / 6.0;
	return ((int)r);
}

int	allocate_doors(t_data *data)
{
	data->doors_count = count_doors_in_map(data);
	if (data->doors_count <= 0)
		return (1);
	data->doors = malloc(sizeof(t_doors) * data->doors_count);
	if (!data->doors)
		exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(*data));
	if (!data)
	{
		perror("calloc");
		return (1);
	}
	if (parser_bonus(data, argc, argv))
		return (0);
	data->tiles_y = data->count;
	data->tiles_x = data->max_len;
	launch_game_bonus(data);
}
