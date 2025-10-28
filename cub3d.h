/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:36:13 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/28 20:52:31 by mlavry           ###   ########.fr       */
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
# define C_RED 0xFF0000FFu
# define COL_WALL_DARK 0xFFBFBFBFu
# define C_DARK 0x000000FF

# include "Libft/libft.h"
# include "GNL/get_next_line.h"
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "MLX42/MLX42.h"
# include <math.h>
# include <sys/time.h>

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

typedef struct s_dda
{
	int		mx;
	int		my;
	int		stepx;
	int		stepy;
	double	ddx;
	double	ddy;
	double	sdx;
	double	sdy;
}	t_dda;

typedef struct s_column
{
	int		x;
	double	rdx;
	double	rdy;
	double	dist;
	int		side;
	int		y0;
	int		y1;
}	t_column;

typedef struct s_rect
{
	int	x;
	int	y;
	int	size_x;
	int	size_y;
}	t_rect;

typedef struct s_circle
{
	int	px;
	int	py;
	int	r;
}	t_circle;

typedef struct s_minimap
{
	mlx_image_t	*img;
	int			tile;
	int			margin;
	int			wpx;
	int			hpx;
	int			show;
	double		zoom;
	int			radius;
	double		fov_deg;
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
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_params
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		f_rgb[3];
	int		c_rgb[3];
}	t_params;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_textures;

typedef struct s_data
{
	char		**map;
	int			monitor_h;
	int			monitor_w;
	int			tiles_y;
	int			tiles_x;
	int			count;
	int			max_len;
	long		last_us;
	mlx_t		*mlx;
	t_window	window;
	t_player	player;
	t_textures	textures;
	t_minimap	minimap;
	t_params	param;
}	t_data;

t_data		*open_map(void);
char		**create_tab(t_data *data, char *map_path);
void		print_map(t_data *data);
void		launch_game(t_data *data);
void		fill_rect(t_data *data, mlx_image_t *img, t_rect dim,
				uint32_t color);
int			line_len_no_nl(const char *s);
void		count_tile_in_map(t_data *data);
void		draw_minimap(t_data *data);
void		minimap_init(t_data *data);
void		fill_circle(t_data *data, t_circle circle, uint32_t color);
void		set_camera_plane(t_player *player);
void		init_player(t_data *data);
void		init_player_dir(t_data *data, int x, int y);
void		set_background(void *param);

void		dda_init_axis(double *delta, double dir);
char		map_at(t_data *data, int x, int y);
double		dda_first_hit(t_data *data, double rdx, double rdy, int *side_hit);
void		render_frame_basic(void *param);
double		get_dt_seconds(t_data *data);
void		handle_movement(t_data *d);

void		print_player_info(t_data *data);

int			parser(t_data *data, int argc, char **argv);

int			is_cub(char *argv);
int			is_param(t_params *param, char *line);
char		**readmap(t_data *game, char *file);
int			is_map_line(char *line);
int			all_param_ok(t_params *param);
int			check_param(t_data *game, char *file);
int			parse_colour(t_data *game, char *line);
int			parse_texture(t_data *game, char *line);
int			valid_map(t_data *game);
int			is_close(t_data *game);
int			check_holes(t_data *game);
char		*whitespace(char *line);
int			ft_strcmp(char *s1, char *s2);
int			count_lines(char *map_path);
int			init_textures(t_data *data);
void		draw_textured_column(t_data *d, t_column *c);
uint32_t	rgb_to_u32(int r, int g, int b);
void		set_image(t_data *data);

t_dpoint	minimap_px_to_world_rot(t_data *data, int px, int py);
void		launch_game_bonus(t_data *data);
t_dpoint	rotate_local_to_world_delta(t_data *data, t_dpoint loc);
t_dpoint	pixels_to_local_tiles(t_data *data, int px, int py);
double		player_angle_rad(t_player *p);
void		minimap_clear_disk_and_player(t_data *data);
void		handle_minimap_keys(t_data *data);
void		minimap_draw_rot_fov(t_data *d);
uint32_t	minimap_color_for_tile(t_data *data, double wx, double wy);
int			mm_compute_radius(t_minimap *m);
int			in_bounds(t_data *d, int tx, int ty);
void		draw_player_center(t_data *data, t_point c);
int			mm_player_px_radius(t_data *d);
t_dpoint	minimap_px_to_world_rot(t_data *d, int px, int py);
void		minimap_draw_circle_border(t_data *d, uint32_t col);

#endif