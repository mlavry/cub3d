/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:39:37 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/12 20:43:45 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*Calcule la direction du rayon pour chaque colone de pixel*/
static void	compute_ray_dir(t_data *data, int x, double *rdx, double *rdy)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (double)data->monitor_w - 1.0;
	*rdx = data->player.dir_x + data->player.plane_x * camera_x;
	*rdy = data->player.dir_y + data->player.plane_y * camera_x;
}

/*Transforme la distance d'un mur en hauteur de mur a afficher*/
static void	project_column(t_data *data, double dist, int *y0, int *y1)
{
	int	line_h;
	int	mid;

	if (dist < 1e-6)
		dist = 1e-6;
	line_h = (int)((double)data->monitor_h / dist);
	mid = data->monitor_h / 2;
	*y0 = -line_h / 2 + mid;
	*y1 = line_h / 2 + mid;
}

/*Loop de rendu*/
void	render_frame_basic(void *param)
{
	int			x;
	t_column	c;
	t_data		*data;

	data = (t_data *)param;
	handle_movement(data);
	set_background(data);
	x = 0;
	while (x < data->monitor_w)
	{
		c.x = x;
		compute_ray_dir(data, x, &c.rdx, &c.rdy);
		c.dist = dda_first_hit(data, c.rdx, c.rdy, &c.side);
		project_column(data, c.dist, &c.y0, &c.y1);
		draw_textured_column(data, &c);
		x++;
	}
}

int	init_textures(t_data *data)
{
	data->textures.north = mlx_load_png(data->param.no_path);
	data->textures.south = mlx_load_png(data->param.so_path);
	data->textures.east = mlx_load_png(data->param.ea_path);
	data->textures.west = mlx_load_png(data->param.we_path);
	if (!data->textures.north || !data->textures.south || !data->textures.east
		|| !data->textures.west)
	{
		printf("Error when loading textures\n");
		exit (1);
	}
	return (0);
}
