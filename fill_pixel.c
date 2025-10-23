/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 00:17:14 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/23 18:02:06 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_rect(t_data *data, mlx_image_t *img, t_rect dim, uint32_t color)
{
	int	x;
	int	y;

	if (!img || dim.x < 0 || dim.x > data->monitor_w
		|| dim.y < 0 || dim.y > data->monitor_h)
		return ;
	if (dim.x + dim.size_x > data->monitor_w
		|| dim.y + dim.size_y > data->monitor_h)
		return ;
	x = dim.x;
	y = dim.y;
	while (dim.y < y + dim.size_y)
	{
		while (dim.x < x + dim.size_x)
		{
			mlx_put_pixel(img, (uint32_t)dim.x, (uint32_t)dim.y, color);
			dim.x++;
		}
		dim.y++;
		dim.x = x;
	}
}

void	fill_circle(t_data *data, t_circle circle, uint32_t color)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = -circle.r;
	while (y <= circle.r)
	{
		x = -circle.r;
		while (x <= circle.r)
		{
			if (x * x + y * y <= circle.r * circle.r)
			{
				px = circle.px + x;
				py = circle.py + y;
				if (px >= 0 && py >= 0
					&& px < (int)data->minimap.img->width && py
					< (int)data->minimap.img->height)
					mlx_put_pixel(data->minimap.img,
						(uint32_t)px, (uint32_t)py, color);
			}
			x++;
		}
		y++;
	}
}

uint32_t	rgb_to_u32(int r, int g, int b)
{
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return (((uint32_t)r << 24)
		| ((uint32_t)g << 16)
		| ((uint32_t)b << 8)
		| 0xFF);
}
