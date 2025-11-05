/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:26:20 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/05 23:55:55 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parser_bonus(t_data *data, int argc, char **argv)
{
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
	return (0);
}

char	**readmap_bonus(t_data *game, char *file)
{
	int		fd;
	int		count;
	char	*first_line;

	game->max_len = count_long(file);
	count = countline_bonus(file);
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
		return (close(fd), NULL);
	close(fd);
	if (!valid_map_bonus(game))
		return (write(2, "Error: invalid map\n", 20), NULL);
	return (game->map);
}

int	valid_map_bonus(t_data *game)
{
	int	i;
	int	j;
	int	len;
	int	player;

	j = 0;
	i = -1;
	player = 0;
	while (game->map[++i])
	{
		len = ft_strlen(game->map[i]);
		if (len == 0)
			return (0);
		j = -1;
		while (++j < len)
		{
			if (!is_valid_char_bonus(game->map[i][j]))
				return (0);
			if (is_valid_direction(game->map[i][j]))
				player++;
		}
	}
	if (player != 1)
		return (write(2, "Error: invalid number of players\n", 33), 0);
	return (1);
}

int	countline_bonus(char *file)
{
	int		fd;
	int		count;
	char	*line;
	char	*trimmed;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = whitespace(line);
		if (*trimmed != '\0' && is_map_line_bonus(trimmed))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	is_map_line_bonus(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	while (!line[i])
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != 'P'
			&& line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
