/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:12:45 by aboutale          #+#    #+#             */
/*   Updated: 2025/10/22 22:49:25 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if ((len <= 4) || (ft_strcmp(filename + len - 4, ".cub") != 0))
		return (0);
	return (1);
}

int	param_is(t_params *param, char *line)
{
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (param->ea)
			return (1);
		param->ea = 1;
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		if (param->f)
			return (1);
		param->f = 1;
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (param->c)
			return (1);
		param->c = 1;
	}
	return (-1);
}

int	is_param(t_params *param, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (param->no)
			return (1);
		param->no = 1;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (param->so)
			return (1);
		param->so = 1;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (param->we)
			return (1);
		param->we = 1;
	}
	else if (param_is(param, line) == 1)
		return (1);
	return (-1);
}

int	all_param_ok(t_params *param)
{
	return (param->no && param->so && param->we && param->ea
		&& param->f && param->c);
}

int	check_duplicate(t_data *game, char *trimmed)
{
	int	extra;

	extra = is_param(&game->param, trimmed);
	if (extra == 1)
	{
		return (write(2, "Error: duplicate parameter\n", 27), 0);
	}
	return (1);
}

static char *skip_empty_lines(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = whitespace(line);
		if (*trimmed != '\0')
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

static int handle_param_line(t_data *game, char *line)
{
	char	*trimmed;

	trimmed = whitespace(line);
	if (!check_duplicate(game, trimmed))
		return (0);
	if (ft_strncmp(trimmed, "F ", 2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (!parse_colour(game, trimmed))
			return (0);
	}
	else if (!ft_strncmp(trimmed, "NO", 2) || !ft_strncmp(trimmed, "SO", 2)
		|| !ft_strncmp(trimmed, "WE", 2) || !ft_strncmp(trimmed, "EA", 2))
	{
		if (!parse_texture(game, trimmed))
			return (0);
	}
	else if (is_map_line(trimmed))
	{
		if (!all_param_ok(&game->param))
			return (write(2, "Error: missing parameters\n", 26), 0);
		return (2);
	}
	else
		return (write(2, "Error : invalid parameter\n", 26), 0);
	return (1);
}

int check_param(t_data *game, char *file)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ((void)write(2, "Error: cannot open file\n", 24), 0);
	line = skip_empty_lines(fd);
	while (line)
	{
		status = handle_param_line(game, line);
		free(line);
		if (status == 0)
			return (get_next_line(-1), (void)close(fd), 0);
		if (status == 2)
			break ;
		line = skip_empty_lines(fd);
	}
	close(fd);
	return (1);
}
