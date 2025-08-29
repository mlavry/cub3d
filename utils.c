/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:20:08 by mlavry            #+#    #+#             */
/*   Updated: 2025/08/29 03:00:31 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vline(mlx_image_t *img, int x, int y0, int y1, uint32_t color)
{
	int	y;

	if (y0 < 0)
		y0 = 0;
	if (y1 >= (int)img->height)
		y1 = img->height;
	y = y0;
	while (y <= y1)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void	draw_fake_wall(mlx_image_t *img)
{
	int	center_x;
	int	y0;
	int	y1;

	center_x = (int)img->width / 2;
	y0 = (int)img->height / 2 - 100;
	y1 = (int)img->height / 2 + 100;
	draw_vline(img, center_x, y0, y1, C_WHITE);
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

void	count_tile_in_map(t_data *data)
{
	int	max_x;
	int	y;
	int	x;

	y = 0;
	max_x = 0;
	x = 0;
	while (y < data->tiles_y && data->map[y])
	{
		x = line_len_no_nl(data->map[y]);
		if (x > max_x)
			max_x = x;
		y++;
	}
	data->tiles_x = max_x;
	printf("Taille en x : %d\n", data->tiles_x);
	printf("Taille en y : %d\n", data->tiles_y);
}
