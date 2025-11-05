/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 21:44:19 by aboutale          #+#    #+#             */
/*   Updated: 2025/11/05 21:44:25 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_cub(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if ((len <= 4) || (ft_strcmp(filename + len - 4, ".cub") != 0))
		return (0);
	return (1);
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

int	all_param_ok(t_params *param)
{
	return (param->no && param->so && param->we && param->ea
		&& param->f && param->c);
}

int	is_close(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < game->max_len)
	{
		if (game->map[0][j] != '1' && game->map[0][j] != ' ')
			return ((void)write(2, "Error : map not closed on top\n", 29), 0);
	}
	while (++i < game->count - 1)
	{
		if ((game->map[i][0] != '1' && game->map[i][0] != ' ')
		|| (game->map[i][game->max_len - 1] != '1'
			&& game->map[i][game->max_len - 1] != ' '))
			return ((void)write(2, "Error : map not closed on sides\n", 32), 0);
	}
	j = -1;
	while (++j < game->max_len)
	{
		if (game->map[game->count - 1][j] != '1'
			&& game->map[game->count - 1][j] != ' ')
			return ((void)write(2, "Error: map not closed at bottom\n", 32), 0);
	}
	return (1);
}

int	check_holes(t_data *game)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < game->count)
	{
		j = -1;
		while (++j < game->max_len)
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
		}
	}
	return (1);
}
