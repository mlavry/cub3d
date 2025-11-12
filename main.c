/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:01:28 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/12 16:18:18 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		free(data);
		return (0);
	}
	data->tiles_y = data->count;
	data->tiles_x = data->max_len;
	launch_game(data);
}
