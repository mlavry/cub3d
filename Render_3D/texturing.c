/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:19:30 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/04 15:53:43 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*pick_wall_texture(t_data *d, int side, double rdx, double rdy)
{
	if (side == 0)
	{
		if (rdx > 0.0)
			return (d->textures.west);
		return (d->textures.east);
	}
	if (rdy > 0.0)
		return (d->textures.north);
	return (d->textures.south);
}

uint32_t	read_pixel_in_tex(mlx_texture_t *tex, int tx, int ty)
{
	uint8_t	*r;
	int		i;

	if (!tex || tx < 0 || ty < 0 || tx >= (int)tex->width
		|| ty >= (int)tex->height)
		return (C_DARK);
	i = (ty * (int)tex->width + tx) * 4;
	r = tex->pixels;
	return (((uint32_t)r[i + 0] << 24)
		| ((uint32_t)r[i + 1] << 16)
		| ((uint32_t)r[i + 2] << 8)
		| ((uint32_t)r[i + 3]));
}

static mlx_texture_t	*col_prepare(t_data *data, t_column *c, int *tex_x)
{
	mlx_texture_t	*tex;
	double			wall_x;

	tex = pick_wall_texture(data, c->side, c->rdx, c->rdy);
	if (c->side == 0)
		wall_x = data->player.pos_y + c->dist * c->rdy;
	else
		wall_x = data->player.pos_x + c->dist * c->rdx;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)tex->width);
	if (c->side == 0 && c->rdx > 0.0)
		*tex_x = (int)tex->width - *tex_x - 1;
	if (c->side == 1 && c->rdy < 0.0)
		*tex_x = (int)tex->width - *tex_x - 1;
	return (tex);
}

void	col_blit(t_data *d, t_column *c, mlx_texture_t *tex, int tex_x)
{
	double	step;
	double	tex_pos;
	int		line_h;
	int		y;

	line_h = c->y1 - c->y0 + 1;
	if (line_h <= 0)
		return ;
	step = (double)tex->height / (double)line_h;
	tex_pos = (c->y0 - d->monitor_h / 2 + line_h / 2) * step;
	if (c->y0 < 0)
	{
		tex_pos += (-c->y0) * step;
		c->y0 = 0;
	}
	if (c->y1 >= (int)d->window.img->height)
		c->y1 = (int)d->window.img->height - 1;
	y = c->y0;
	while (y <= c->y1)
	{
		mlx_put_pixel(d->window.img, c->x, y,
			read_pixel_in_tex(tex, tex_x, (int)tex_pos));
		tex_pos += step;
		y++;
	}
}

void	draw_textured_column(t_data *d, t_column *c)
{
	mlx_texture_t	*tex;
	int				tex_x;

	tex = col_prepare(d, c, &tex_x);
	if (!tex)
		return ;
	col_blit(d, c, tex, tex_x);
}
