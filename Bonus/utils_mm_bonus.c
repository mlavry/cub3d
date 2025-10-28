/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mm_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:01:39 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/28 19:52:31 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Angle global du joueur dans le monde.
// atan2 retourne l'angle en radians entre l'axe des X positifs 
	//et le vecteur (x, y).
double	player_angle_rad(t_player *p)
{
	return (atan2(p->dir_y, p->dir_x));
}

t_dpoint	get_center_and_scale(t_data *data)
{
	t_dpoint	result;

	result.x = (double)(data->minimap.wpx / 2);
	result.y = (double)(data->minimap.hpx / 2);
	return (result);
}

// Permet de convertir la position d'un pixel dans l'image de la minimap
t_dpoint	pixels_to_local_tiles(t_data *data, int px, int py)
{
	t_dpoint	mid_mm;
	t_dpoint	loc;
	double		scale;

	mid_mm = get_center_and_scale(data);
	scale = (double)data->minimap.tile * data->minimap.zoom;
	loc.x = ((double)px - mid_mm.x) / scale;
	loc.y = -(((double)py - mid_mm.y) / scale);
	return (loc);
}

// Orienter le vecteur local loc dans le repère du monde 
	//en le tournant de l’angle du joueur,
	//pour que “le haut minimap” corresponde à “l’avant du joueur”.
/*t_dpoint	rotate_local_to_world_delta(t_data *data, t_dpoint loc)
{
	double		c;
	double		s;
	t_dpoint	rot;

	c = data->player.dir_x;
	s = data->player.dir_y;
	rot.x = loc.x * c - loc.y * s;
	rot.y = loc.x * s + loc.y * c;
	return (rot);
}*/

t_dpoint	rotate_local_to_world_delta(t_data *d, t_dpoint loc)
{
	t_dpoint	dr;
	t_dpoint	f;
	double		rx;
	double		ry;

	f.x = d->player.dir_x;
	f.y = d->player.dir_y;
	rx = -f.y;
	ry = f.x;
	dr.x = loc.x * rx + loc.y * f.x;
	dr.y = loc.x * ry + loc.y * f.y;
	return (dr);
}

//floor sert a arrondir vers le bas pour savoir la case dans laquelle se 
	//trouve le point
uint32_t	minimap_color_for_tile(t_data *data, double wx, double wy)
{
	int		tx;
	int		ty;
	char	c;

	tx = (int)floor(wx);
	ty = (int)floor(wy);
	if (!in_bounds(data, tx, ty))
		return (C_DARK);
	c = map_at(data, tx, ty);
	if (c == '1')
		return (C_DARK);
	if (c == '0')
		return (C_WHITE);
	return (C_MINI_VOID);
}
