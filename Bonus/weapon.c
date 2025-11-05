/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:57:15 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/05 22:28:58 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	weapon_anim_update(t_data *d, double dt)
{
	double	speed;

	if (!d->weapon.tex)
		return ;
	d->weapon.shot_timer += dt;
	if (d->weapon.recoil > 0.0)
	{
		d->weapon.recoil -= 50.0 * dt;
		if (d->weapon.recoil < 0.0)
			d->weapon.recoil = 0.0;
	}
	speed = 2.0;
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
		speed = 8.0;
	d->weapon.phase += dt * speed;
}

void	weapon_shoot(t_data *d)
{
	if (!d->weapon.tex)
		return ;
	if (d->weapon.shot_timer < d->weapon.cooldown)
		return ;
	d->weapon.shot_timer = 0.0;
	d->weapon.recoil = 12.0;
}

static void	weapon_draw_loop(t_data *d, int start_x, int start_y)
{
	t_point		s;
	int			screen_x;
	int			screen_y;
	uint32_t	col;

	s.y = 0;
	while (s.y < d->weapon.h)
	{
		s.x = 0;
		while (s.x < d->weapon.w)
		{
			screen_x = start_x + s.x;
			screen_y = start_y + s.y;
			if (screen_x >= 0 && screen_x < d->monitor_w
				&& screen_y >= 0 && screen_y < d->monitor_h)
			{
				col = read_pixel_in_tex(d->weapon.tex, s.x, s.y);
				if ((col & 0xFFu) != 0)
					mlx_put_pixel(d->window.img,
						(uint32_t)screen_x, (uint32_t)screen_y, col);
			}
			s.x++;
		}
		s.y++;
	}
}

void	weapon_draw(t_data *d, double dt)
{
	int		start_x;
	int		base_y;
	int		offset_y;
	double	amp;

	if (!d->weapon.tex)
		return ;
	weapon_anim_update(d, dt);
	amp = 5.0;
	offset_y = (int)(sin(d->weapon.phase) * amp);
	offset_y -= (int)d->weapon.recoil;
	start_x = d->monitor_w / 2 - d->weapon.w / 2;
	base_y = d->monitor_h - d->weapon.h - 30;
	weapon_draw_loop(d, start_x, base_y + offset_y);
}

void	weapon_init(t_data *d)
{
	d->weapon.tex = mlx_load_png("Textures/weapon3.png");
	if (!d->weapon.tex)
		return ;
	d->weapon.w = (int)d->weapon.tex->width;
	d->weapon.h = (int)d->weapon.tex->height;
	d->weapon.phase = 0.0;
	d->weapon.recoil = 0.0;
	d->weapon.shot_timer = 1000.0;
	d->weapon.cooldown = 0.15;
}
