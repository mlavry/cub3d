/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:46:45 by mlavry            #+#    #+#             */
/*   Updated: 2025/08/25 18:19:41 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_empty(t_data *data)
{
	data->map = NULL;
	data->y = 0;
}

static int	count_lines(char *map_path)
{
	char	*line;
	int		count;
	int		fd;

	fd = open(map_path, O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	free(line);
	while (line)
	{
		count++;
		line = get_next_line(fd);
		free(line);
	}
	close (fd);
	return (count);
}

t_data	*open_map(void)
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

char	**create_tab(t_data *data, char *map_path)
{
	int		i;
	char	*line;
	int		fd;

	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	data->y = count_lines(map_path);
	while (i < data->y)
	{
		line = get_next_line(fd);
		if (!line)
		{
			while (--i >= 0)
				free(data->map[i]);
			return (free(data->map), close(fd), NULL);
		}
		data->map[i] = line;
		i++;
	}
	line = get_next_line(fd);
	free(line);
	data->map[i] = NULL;
	return (close(fd), data->map);
}

void	print_tab(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->y)
	{
		printf("%s", data->map[i]);
		i++;
	}
}
