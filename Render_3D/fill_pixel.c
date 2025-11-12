/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 00:17:14 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/12 20:38:54 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*Fonction pour convertir en u32*/
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

void	draw_background(t_data *data, mlx_image_t *img)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	while (y < (int)img->height)
	{
		if (y < (int)img->height / 2)
			color = rgb_to_u32(data->param.c_rgb[0], data->param.c_rgb[1],
					data->param.c_rgb[2]);
		else
			color = rgb_to_u32(data->param.f_rgb[0], data->param.f_rgb[1],
					data->param.f_rgb[2]);
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
