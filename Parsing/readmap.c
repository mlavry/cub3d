/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:42:09 by aboutale          #+#    #+#             */
/*   Updated: 2025/11/04 01:43:16 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_extra_data(int fd, char *line)
{
	char	*trim;

	while (line)
	{
		trim = whitespace(line);
		if (*trim != '\0')
			return (free(line),
				write(2, "Error: extra data after map\n", 28), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

static int	fill_line(t_data *game, char *line, int i)
{
	int	j;

	j = 0;
	game->map[i] = malloc(sizeof(char) * (game->max_len + 1));
	if (!game->map[i])
		return (0);
	while (line[j] && line[j] != '\n')
	{
		game->map[i][j] = line[j];
		j++;
	}
	while (j < game->max_len)
		game->map[i][j++] = ' ';
	game->map[i][j] = '\0';
	return (1);
}

int	read_map_lines(t_data *game, int fd, char *first_line, int count)
{
	char	*line;
	int		i;

	line = first_line;
	i = 0;
	while (line && i < count)
	{
		if (!fill_line(game, line, i))
			return (0);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->count = i;
	game->map[i] = NULL;
	return (check_extra_data(fd, line));
}

int	count_long(char *file)
{
	int		fd;
	int		len;
	int		max_len;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	max_len = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			len = ft_strlen(line);
			if (line[len - 1] == '\n')
				len--;
			if (len > max_len)
				max_len = len;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (max_len);
}

char	**readmap(t_data *game, char *file)
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
		return (close(fd), NULL);
	close(fd);
	if (!valid_map(game))
		return (write(2, "Error: invalid map\n", 20), NULL);
	return (game->map);
}
