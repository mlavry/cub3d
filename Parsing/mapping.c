/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:58:04 by aboutale          #+#    #+#             */
/*   Updated: 2025/11/05 23:56:37 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_char_bonus(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'E'
		|| c == 'S' || c == 'W' || c == ' ' || c == 'P');
}

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'E'
		|| c == 'S' || c == 'W' || c == ' ');
}

int	is_valid_direction(char c)
{
	return (c == 'S' || c == 'N' || c == 'W' || c == 'E');
}

int	valid_map(t_data *game)
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
			if (!is_valid_char(game->map[i][j]))
				return (0);
			if (is_valid_direction(game->map[i][j]))
				player++;
		}
	}
	if (player != 1)
		return (write(2, "Error: invalid number of players\n", 33), 0);
	return (1);
}

int	parser(t_data *data, int argc, char **argv)
{
	data->map = NULL;
	if (argc != 2)
		return (write(2, "Error usage : ./cub3D map.cub\n", 30), 1);
	if (!is_cub(argv[1]))
		return (write(2, "Error usage name\n", 17));
	if (!check_param(data, argv[1]))
		return (1);
	data->map = readmap(data, argv[1]);
	if (!data->map)
		return (write(2, "Error : could not read the mapp\n", 31));
	if (!is_close(data))
		exit(0);
	if (!check_holes(data))
		exit(0);
	return (0);
}
