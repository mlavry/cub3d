/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:46:45 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/12 23:47:22 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	drain_gnl(int fd)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// }

static void	free_texture(t_data *data)
{
	if (data->param.no_path)
	{
		free(data->param.no_path);
		data->param.no_path = NULL;
	}
	if (data->param.so_path)
	{
		free(data->param.so_path);
		data->param.so_path = NULL;
	}
	if (data->param.ea_path)
	{
		free(data->param.ea_path);
		data->param.ea_path = NULL;
	}
	if (data->param.we_path)
	{
		free(data->param.we_path);
		data->param.we_path = NULL;
	}
}

static void	free_all(t_data *data)
{
	if (data->map_fd >= 0)
	{
		get_next_line(-1);
		close(data->map_fd);
		data->map_fd = -1;
	}
	free_texture(data);
	if (data)
		free(data);
}

void	put_error_and_exit(t_data *data, char *str)
{
	free_all(data);
	ft_putstr_fd(str, 1);
	exit (1);
}
