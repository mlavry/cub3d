/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:26:20 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/29 22:05:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parser_bonus(t_data *data, int argc, char **argv)
{
	t_params param = {0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, {0, 0, 0},
	{0, 0, 0}};

	data->param = param;
	data->map = NULL;
	if (argc != 2)
		return (write(2, "Error usage : ./cub3D map.cub\n", 30), 1);
	if (!is_cub(argv[1]))
		return (write(2, "Error usage name\n", 17));
	if (!check_param(data, argv[1]))
		return (1);
	data->map = readmap_bonus(data, argv[1]);
	if (!data->map)
		return (write(2, "Error : could not read the mapp\n", 31));
	if (!is_close(data))
    	exit(0);
	if (!check_holes(data))
    	exit(0);
	//print_params_debug(&param);
	//print_map_debug(data->map);
	//debug_map_lengths(data->map);
	return (0);
}

char	**readmap_bonus(t_data *game, char *file)
{
	int		fd;
	int		count;
	char	*first_line;

	game->max_len = count_long(file);
	count = countline(file);
	game->count = count;
	if (count <= 0 || game->max_len == 0)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		return (close(fd), NULL);
	first_line = skip_to_map(fd);
	if (!first_line)
		return (close(fd), NULL);
	if (!read_map_lines(game, fd, first_line, count))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	if (!valid_map_bonus(game))
		return (write(2, "Error: invalid map\n", 20), NULL);
	return (game->map);
}

int valid_map_bonus(t_data *game)
{
	int	i;
	int	j;
	int	len;
	int	player;

	j = 0;
	i = 0;
	player = 0;
	while (game->map[i])
	{
		len = ft_strlen(game->map[i]);
		if (len == 0)
			return (0);
		j = 0;
		while (j < len)
		{
			if (game->map[i][j] != '1' && game->map[i][j] != '0'
				&& game->map[i][j] != 'N' && game->map[i][j] != 'E'
				&& game->map[i][j] != 'S' && game->map[i][j] != 'W'
				&& game->map[i][j] != ' ' && game->map[i][j] != 'P')
				return (0);
			if (game->map[i][j] == 'S' || game->map[i][j] == 'N'
			|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (write(2, "Error: invalid number of players\n", 33), 0);
	return (1);
}

static int	count_doors_in_map(t_data *data)
{
	int	x;
	int	y;
	int	n;

	y = 0;
	n = 0;
	while (y < data->tiles_y && data->map[y])
	{
		x = 0;
		while (x < line_len_no_nl(data->map[y]))
		{
			if (data->map[y][x] == 'P')
				n++;
			x++;
		}
		y++;
	}
	return (n);
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
