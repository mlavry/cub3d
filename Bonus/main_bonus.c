/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:22:05 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/28 01:09:05 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

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

int	main(int argc, char **argv)
{
	t_data	*data;

	data = calloc(1, sizeof(*data));
	if (!data)
	{
		perror("calloc");
		return (1);
	}
	if (parser(data, argc, argv))
		return (0);
	data->tiles_y = data->count;
	data->tiles_x = data->max_len;
	launch_game_bonus(data);
}
