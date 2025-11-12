/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:20:08 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/12 16:19:29 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	line_len_no_nl(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != '\n' )
		len++;
	return (len);
}

void	init_player_dir(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
	}
	else if (data->map[y][x] == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
	}
	else if (data->map[y][x] == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
	}
	else if (data->map[y][x] == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
	}
}
