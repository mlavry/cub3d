/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:45:43 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/28 02:35:39 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	in_bounds(t_data *d, int tx, int ty)
{
	int	len;

	if (ty < 0 || ty >= d->tiles_y || !d->map[ty])
		return (0);
	len = line_len_no_nl(d->map[ty]);
	if (tx < 0 || tx >= len)
		return (0);
	return (1);
}

int	mm_compute_radius(t_minimap *m)
{
	int	min_side;
	int	safe;

	min_side = m->wpx;
	if (min_side > m->hpx)
		min_side = m->hpx;
	safe = (min_side / 2) - 2;
	if (safe < 10)
		safe = 10;
	return (safe);
}

// Dessine un pixel de la zone monde si (x,y) est dans le disque
static void	mm_draw_world_px(t_data *d, int x, int y)
{
	int				dx;
	int				dy;
	t_dpoint		w;
	uint32_t		col;

	if (x < 0 || y < 0
		|| x >= (int)d->minimap.wpx || y >= (int)d->minimap.hpx)
		return ;
	dx = x - (int)(d->minimap.wpx / 2);
	dy = y - (int)(d->minimap.hpx / 2);
	if (dx * dx + dy * dy > d->minimap.radius * d->minimap.radius)
		return ;
	w = minimap_px_to_world_rot(d, x, y);
	col = minimap_color_for_tile(d, w.x, w.y);
	if (col != C_MINI_VOID)
		mlx_put_pixel(d->minimap.img, x, y, col);
}

// Balaye le carré englobant le disque et appelle mm_draw_world_px
static void	mm_scan_world(t_data *d)
{
	int	cx;
	int	cy;
	int	r;
	int	x;
	int	y;

	cx = d->minimap.wpx / 2;
	cy = d->minimap.hpx / 2;
	r = d->minimap.radius;
	y = cy - r;
	while (y <= cy + r)
	{
		x = cx - r;
		while (x <= cx + r)
		{
			mm_draw_world_px(d, x, y);
			x++;
		}
		y++;
	}
}

// Orchestration : clear+disk, remplissage monde, overlay joueur+FOV
void	minimap_draw_rot_fov(t_data *d)
{
	t_point	c;

	if (!d->minimap.img || !d->minimap.show)
		return ;
	minimap_clear_disk_and_player(d);
	mm_scan_world(d);
	//minimap_draw_fov_cone(d);
	c.x = d->minimap.wpx / 2;
	c.y = d->minimap.hpx / 2;
	draw_player_center(d, c);
}
