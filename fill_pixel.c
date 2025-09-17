/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 00:17:14 by mlavry            #+#    #+#             */
/*   Updated: 2025/09/17 01:29:54 by mlavry           ###   ########.fr       */
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
