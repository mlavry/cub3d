/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:36:13 by mlavry            #+#    #+#             */
/*   Updated: 2025/08/29 03:21:35 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 800
# define HEIGHT 600
# define C_TOP 0x87CEFAFF
# define C_FLOOR 0x2F4F4FFF
# define C_WHITE 0xFFFFFFFF
# define C_GREY 0x808080FFu
# define C_MINI_VOID   0x00000000u
# define C_MINI_BG     0x00000080u 

# include "Libft/libft.h"
# include "GNL/get_next_line.h"
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "MLX42/MLX42.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_rect
{
	int	x;
	int	y;
	int	size_x;
	int	size_y;
}	t_rect;

typedef struct s_minimap
{
	mlx_image_t	*img;
	int			tile;
	int			margin;
	int			wpx;
	int			hpx;
}	t_minimap;

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
	int			monitor_h;
	int			monitor_w;
	int			tiles_y;
	int			tiles_x;
	mlx_t		*mlx;
	t_window	window;
	t_minimap	minimap;
}	t_data;

t_data	*open_map(void);
char	**create_tab(t_data *data, char *map_path);
void	print_map(t_data *data);
void	launch_game(t_data *data);
void	draw_fake_wall(mlx_image_t *img);
void	fill_rect(t_data *data, mlx_image_t *img, t_rect dim, uint32_t color);
int		line_len_no_nl(const char *s);
void	count_tile_in_map(t_data *data);
void	draw_minimap(t_data *data);
void	minimap_init(t_data *data);

#endif