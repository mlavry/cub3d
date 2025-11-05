/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:29:12 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/06 00:13:25 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*pick_wall_texture_bonus(t_data *d, t_column *c)
{
	if (c->tile == 'P')
		return (d->textures.door);
	if (c->side == 0)
	{
		if (c->rdx > 0.0)
			return (d->textures.east);
		return (d->textures.west);
	}
	if (c->rdy > 0.0)
		return (d->textures.south);
	return (d->textures.north);
}

static mlx_texture_t	*col_prepare_b(t_data *data, t_column *c, int *tex_x)
{
	mlx_texture_t	*tex;
	double			wall_x;

	tex = pick_wall_texture_bonus(data, c);
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

// Ajuste la partie visible de la colonne si c'est une porte.
// Retourne 0 si on ne doit rien dessiner (porte totalement ouverte),
// 1 si on doit continuer à dessiner.
static int	door_clip_column(t_data *d, t_column *c, int *line_h)
{
	t_doors	*door;
	double	open;
	int		new_y1;

	if (c->tile != 'P')
		return (1);
	door = door_at(d, c->mx, c->my);
	open = 0.0;
	if (door)
		open = door->open;
	if (open >= 1.0)
		return (0);
	new_y1 = c->y0 + (int)((1.0 - open) * (double)(*line_h));
	c->y1 = new_y1;
	*line_h = c->y1 - c->y0 + 1;
	if (*line_h <= 0)
		return (0);
	return (1);
}

static void	col_blit_bonus(t_data *d, t_column *c,
					mlx_texture_t *tex, int tex_x)
{
	double	step;
	double	tex_pos;
	int		line_h;
	int		y;

	line_h = c->y1 - c->y0 + 1;
	if (!door_clip_column(d, c, &line_h))
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

void	draw_textured_column_bonus(t_data *d, t_column *c)
{
	mlx_texture_t	*tex;
	int				tex_x;

	tex = col_prepare_b(d, c, &tex_x);
	if (!tex)
		return ;
	col_blit_bonus(d, c, tex, tex_x);
}
