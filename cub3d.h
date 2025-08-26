/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:36:13 by mlavry            #+#    #+#             */
/*   Updated: 2025/08/26 21:38:32 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define C_WALL 0xFFFFFFFF

# include "Libft/libft.h"
# include "GNL/get_next_line.h"
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "MLX42/MLX42.h"

typedef struct s_window
{
	mlx_image_t	*img;
}	t_window;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_data
{
	char		**map;
	int			y;
	mlx_t		*mlx;
	t_window	window;	
}	t_data;

t_data	*open_map(void);
char	**create_tab(t_data *data, char *map_path);
void	print_tab(t_data *data);
void	launch_game(t_data *data);
void	draw_fake_wall(mlx_image_t *img);

#endif