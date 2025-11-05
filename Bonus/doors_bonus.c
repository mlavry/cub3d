/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:36:30 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/05 23:26:02 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_doors	*door_at(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->doors_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

//Pour t on calcule la case devant le joueur 
void	handle_doors_movement(t_data *data)
{
	static int	prev_e;
	t_point		t;
	int			press;
	t_doors		*door;

	press = mlx_is_key_down(data->mlx, MLX_KEY_E);
	if (!press || prev_e)
	{
		prev_e = press;
		return ;
	}
	t.x = (int)(data->player.pos_x + data->player.dir_x * 0.8);
	t.y = (int)(data->player.pos_y + data->player.dir_y * 0.8);
	door = door_at(data, t.x, t.y);
	if (door)
	{
		if (door->open >= 1.0 && !player_is_in_tile(data, t.x, t.y))
			door->moving = -1;
		else if (door->open <= 0.0)
			door->moving = 1;
	}
	prev_e = press;
}

int	is_wall_bonus(t_data *data, int mx, int my)
{
	t_doors	*dr;

	if (mx < 0 || my < 0 || mx >= data->tiles_x || my >= data->tiles_y)
		return (1);
	if (data->map[my][mx] == '1')
		return (1);
	if (data->map[my][mx] == 'P')
	{
		dr = door_at(data, mx, my);
		if (dr && dr->open < 0.95)
			return (1);
	}
	return (0);
}

void	try_move_bonus(t_data *d, double dx, double dy)
{
	const double	r = 0.20;
	double			new_x;
	double			new_y;
	double			cx;
	double			cy;

	new_x = d->player.pos_x + dx;
	new_y = d->player.pos_y + dy;
	cx = -r;
	if (dx > 0)
		cx = r;
	cy = -r;
	if (dy > 0)
		cy = r;
	if (!is_wall_bonus(d, (int)(new_x + cx), (int)(d->player.pos_y)))
		d->player.pos_x = new_x;
	if (!is_wall_bonus(d, (int)(d->player.pos_x), (int)(new_y + cy)))
		d->player.pos_y = new_y;
}

int	count_doors_in_map(t_data *data)
{
	int	x;
	int	y;
	int	n;

	y = 0;
	n = 0;
	while (y < data->tiles_y && data->map[y])
	{
		x = 0;
		while (x < line_len_no_nl(data->map[y]))
		{
			if (data->map[y][x] == 'P')
				n++;
			x++;
		}
		y++;
	}
	return (n);
}
