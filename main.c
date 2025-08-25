/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:01:28 by mlavry            #+#    #+#             */
/*   Updated: 2025/08/21 14:53:25 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_empty(t_data *data)
{
	data->map = NULL;
	data->y = 0;
}

t_data	*open_map(char *map_path)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	init_empty(data);
	data->map = malloc(sizeof(char *) * 1000);
	if (!data->map)
		return (free(data), NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (0);
	data = open_map(argv[1]);
	if (!data)
		return (0);
	
}
