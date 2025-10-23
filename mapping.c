/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:58:04 by aboutale          #+#    #+#             */
/*   Updated: 2025/10/23 19:46:08 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int valid_map(t_data *game)
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
				&& game->map[i][j] != ' ')
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

int is_close(t_data *game)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	//printf("Debug: map has %d lines, max_len = %d\n", game->count, game->max_len);
	/*for (int i = 0; i < game->count; i++)
	{
		printf("Line %d (len %zu): '%s'\n", i, ft_strlen(game->map[i]), game->map[i]);
	}*/
	while (j < game->max_len)
	{
		if (game->map[0][j] != '1' && game->map[0][j] != ' ')
			return ((void)write(2, "Error : map not closed on top\n", 29), 0);
		j++;
	}
	while (i < game->count - 1)
	{
		if ((game->map[i][0] != '1' && game->map[i][0] != ' ')
		|| (game->map[i][game->max_len - 1] != '1'
			&& game->map[i][game->max_len - 1] != ' '))
			return ((void)write(2, "Error : map not closed on sides\n", 32), 0);
		i++;
	}
	j = 0;
	while (j < game->max_len)
	{
		if (game->map[game->count - 1][j] != '1'
			&& game->map[game->count - 1][j] != ' ')
			return ((void)write(2, "Error: map not closed at bottom\n", 32), 0);
		j++;
	}
	return (1);
}

int check_holes(t_data *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->count)
	{
		j = 0;
		while (j < game->max_len)
		{
			c = game->map[i][j];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (i == 0 || game->map[i - 1][j] == ' ')
					return ((void)write(2, "Error : hole detected\n", 22), 0);
				if (i == game->count - 1 || game->map[i + 1][j] == ' ')
					return ((void)write(2, "Error : hole detected\n", 22), 0);
				if (j == 0 || game->map[i][j - 1] == ' ')
					return ((void)write(2, "Error : hole detected\n", 22), 0);
				if (j == game->max_len - 1 || game->map[i][j + 1] == ' ')
					return ((void)write(2, "Error : hole detected\n", 22), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parser(t_data *data, int argc, char **argv)
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
	data->map = readmap(data, argv[1]);
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
