/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:22:28 by aboutale          #+#    #+#             */
/*   Updated: 2025/10/21 22:01:47 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*whitespace(char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line++;
	return (line);
}

int	parse_rgb(char *s)
{
	int	value;
	int	i;

	s = whitespace(s);
	if (!*s)
		return (-1);
	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		return (-1);
	value = ft_atoi(s);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

int	parse_colour(t_data *game, char *line)
{
	char	**split;
	int		rgb[3];

	split = ft_split(whitespace(line + 2), ',');
	if (!split[0] || !split[1] || !split[2] || split[3] != NULL )
		return (write(2, "Error colour not valid\n", 23), 0);
	rgb[0] = parse_rgb(split[0]);
	rgb[1] = parse_rgb(split[1]);
	rgb[2] = parse_rgb(split[2]);
	if (rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		return (write(2, "Error: invalid RGB value\n", 25), 0);
	if (line[0] == 'F')
	{
		game->param->f_rgb[0] = rgb[0];
		game->param->f_rgb[1] = rgb[1];
		game->param->f_rgb[2] = rgb[2];
	}
	else if (line[0] == 'C')
	{
		game->param->c_rgb[0] = rgb[0];
		game->param->c_rgb[1] = rgb[1];
		game->param->c_rgb[2] = rgb[2];
	}
	return (1);
}

int	check_texture(char *path)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if ((len < 4) || (ft_strcmp(path + len - 4, ".xpm") != 0))
	{
		write(2, "Error : format must be .xpm\n", 28);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error cannot open texture\n", 26);
		return (0);
	}
	else
		close(fd);
	return (1);
}

int	parse_texture(t_data *game, char *line)
{
	char	*path;
	char	*newline;

	path = ft_strdup(whitespace(line + 2));
	if (!line || !line[2] || line[2] != ' ')
		return (write(2, "Error: invalid texture format\n", 30), 0);
	if (!(path[0] == '.' && path[1] == '/'))
		return (write(2, "Error: texture path must start with ./\n", 40), 0);
	if (!path)
		return (0);
	newline = ft_strchr(path, '\n');
	if (newline)
		*newline = '\0';
	if (!ft_strncmp(line, "NO", 2))
		game->param->no_path = path;
	else if (!ft_strncmp(line, "SO", 2))
		game->param->so_path = path;
	else if (!ft_strncmp(line, "WE", 2))
		game->param->we_path = path;
	else if (!ft_strncmp(line, "EA", 2))
		game->param->ea_path = path;
	return (1);//check_texture(path));
}
