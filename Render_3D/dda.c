/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:10:24 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/23 20:57:21 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	dda_init(t_data *data, t_dda *a, double rdx, double rdy)
{
	t_player	*p;

	p = &data->player;
	a->mx = (int)p->pos_x;
	a->my = (int)p->pos_y;
	dda_init_axis(&a->ddx, rdx);
	dda_init_axis(&a->ddy, rdy);
}

static void	dda_setup_steps(t_data *data, t_dda *a, double rdx, double rdy)
{
	t_player	*p;

	p = &data->player;
	if (rdx < 0.0)
	{
		a->stepx = -1;
		a->sdx = (p->pos_x - a->mx) * a->ddx;
	}
	else
	{
		a->stepx = 1;
		a->sdx = (a->mx + 1.0 - p->pos_x) * a->ddx;
	}
	if (rdy < 0.0)
	{
		a->stepy = -1;
		a->sdy = (p->pos_y - a->my) * a->ddy;
	}
	else
	{
		a->stepy = 1;
		a->sdy = (a->my + 1.0 - p->pos_y) * a->ddy;
	}
}

static void	dda_walk(t_data *data, t_dda *a, int *side_hit)
{
	while (1)
	{
		if (a->sdx < a->sdy)
		{
			a->sdx += a->ddx;
			a->mx += a->stepx;
			*side_hit = 0;
		}
		else
		{
			a->sdy += a->ddy;
			a->my += a->stepy;
			*side_hit = 1;
		}
		if (map_at(data, a->mx, a->my) == '1')
			return ;
	}
}

static double	dda_perp_dist(t_data *d, t_dda *a,
	t_dpoint ray_dir, int side_hit)
{
	t_player	*p;
	double		num;
	double		den;

	p = &d->player;
	if (side_hit == 0)
	{
		num = (double)a->mx - p->pos_x + (1.0 - (double)a->stepx) / 2.0;
		den = ray_dir.x;
		if (den == 0.0)
			den = 1e-9;
		return (num / den);
	}
	num = (double)a->my - p->pos_y + (1.0 - (double)a->stepy) / 2.0;
	den = ray_dir.y;
	if (den == 0.0)
		den = 1e-9;
	return (num / den);
}

double	dda_first_hit(t_data *data, double rdx, double rdy, int *side_hit)
{
	t_dda		a;
	double		dist;
	t_dpoint	vec;

	dda_init(data, &a, rdx, rdy);
	dda_setup_steps(data, &a, rdx, rdy);
	dda_walk(data, &a, side_hit);
	vec.x = rdx;
	vec.y = rdy;
	dist = dda_perp_dist(data, &a, vec, *side_hit);
	if (dist < 1e-6)
		dist = 1e-6;
	return (dist);
}
