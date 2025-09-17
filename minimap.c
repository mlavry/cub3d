/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 01:15:27 by mlavry            #+#    #+#             */
/*   Updated: 2025/09/17 01:49:56 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_init(t_data *data)
{

	data->minimap.tile = 16;
	data->minimap.margin = 8;
	data->minimap.wpx = data->tiles_x
		* data->minimap.tile + 2 * data->minimap.margin;
	data->minimap.hpx = data->tiles_y
		* data->minimap.tile + 2 * data->minimap.margin;
	data->minimap.img = mlx_new_image(data->mlx,
			data->minimap.wpx, data->minimap.hpx);
	if (!data->minimap.img)
		return ;
	if (mlx_image_to_window(data->mlx, data->minimap.img, 8, 8) < 0)
	{
		mlx_delete_image(data->mlx, data->minimap.img);
		data->minimap.img = NULL;
	}
}

void	fill_background_minimap(t_data *data)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.size_x = data->minimap.wpx;
	rect.size_y = data->minimap.hpx;
	fill_rect(data, data->minimap.img, rect, C_MINI_BG);
}

void	paint_player_on_minimap(t_data *data, int x, int y, uint32_t color)
{
	t_circle	circle;
	t_rect		rect;

	rect.x = data->minimap.margin + x * data->minimap.tile;
	rect.y = data->minimap.margin + y * data->minimap.tile;
	rect.size_x = data->minimap.tile;
	rect.size_y = data->minimap.tile;
	fill_rect(data, data->minimap.img, rect, C_GREY);
	circle.px = data->minimap.margin + x
		* data->minimap.tile + data->minimap.tile / 2;
	circle.py = data->minimap.margin + y
		* data->minimap.tile + data->minimap.tile / 2;
	circle.r = data->minimap.tile / 3;
	fill_circle(data, circle, color);
}

void	paint_minimap(t_data *data, char c, int x, int y)
{
	t_rect		rect;
	uint32_t	color;

	if (c == 'P')
	{
		color = C_RED;
		paint_player_on_minimap(data, x, y, color);
		return ;
	}
	if (c == '1')
		color = C_WHITE;
	else if (c == '0')
		color = C_GREY;
	else if (c == ' ' || c == '\t')
		color = C_MINI_VOID;
	else
		color = C_GREY;
	rect.x = data->minimap.margin + x * data->minimap.tile;
	rect.y = data->minimap.margin + y * data->minimap.tile;
	rect.size_x = data->minimap.tile;
	rect.size_y = data->minimap.tile;
	fill_rect(data, data->minimap.img, rect, color);
}

void	draw_minimap(t_data *data)
{
	int			y;
	int			x;
	int			row_len;
	char		c;

	fill_background_minimap(data);
	y = 0;
	while (y < data->tiles_y && data->map[y])
	{
		row_len = line_len_no_nl(data->map[y]);
		x = 0;
		while (x < data->tiles_x)
		{
			if (x < row_len)
				c = data->map[y][x];
			else
				c = ' ';
			paint_minimap(data, c, x, y);
			x++;
		}
		y++;
	}
}
