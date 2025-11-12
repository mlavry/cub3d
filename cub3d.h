/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:36:13 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/13 00:19:51 by mlavry           ###   ########.fr       */
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
# define C_BLUE_SPECIAL 0x96FFFFFF

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
	char	tile;
	int		mx;
	int		my;
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

typedef struct s_weapon
{
	mlx_texture_t	*tex;
	int				w;
	int				h;
	double			phase;
	double			recoil;
	double			shot_timer;
	double			cooldown;
}	t_weapon;

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

typedef struct s_mouse
{
	double	sens;
	bool	lock;
}	t_mouse;

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
	mlx_texture_t	*door;
}	t_textures;

typedef struct s_doors
{
	int		x;
	int		y;
	double	open;
	int		moving;
}	t_doors;

typedef struct s_data
{
	int			map_fd;
	char		**map;
	int			monitor_h;
	int			monitor_w;
	int			tiles_y;
	int			tiles_x;
	int			count;
	int			max_len;
	long		last_us;
	int			doors_count;
	mlx_t		*mlx;
	t_window	window;
	t_player	player;
	t_textures	textures;
	t_minimap	minimap;
	t_params	param;
	t_mouse		mouse;
	t_doors		*doors;
	t_weapon	weapon;
}	t_data;

void		helper_error_parsing(t_data *data, char *line, char **split,
				char *str);
void		launch_game(t_data *data);;
int			line_len_no_nl(const char *s);
void		minimap_init(t_data *data);
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
int			count_long(char *file);
int			countline(char *file);
char		*skip_to_map(int fd);
int			read_map_lines(t_data *game, int fd, char *first_line, int count);
int			countline_bonus(char *file);
int			is_map_line_bonus(char *line);

int			parser(t_data *data, int argc, char **argv);
int			check_duplicate(t_data *game, char *trimmed, char *line);
int			is_valid_char_bonus(char c);
int			is_valid_direction(char c);

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
int			init_textures(t_data *data);
void		draw_textured_column(t_data *d, t_column *c);
uint32_t	rgb_to_u32(int r, int g, int b);
void		set_image(t_data *data);
void		rotate_player(t_player *p, double ang);
void		try_move(t_data *d, double dx, double dy);

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

void		init_mouse(t_data *data);
void		handle_mouse(t_data *data);
void		handle_movement_bonus(t_data *d, double dt);

int			parser_bonus(t_data *data, int argc, char **argv);
char		**readmap_bonus(t_data *game, char *file);
int			valid_map_bonus(t_data *game);
int			allocate_doors(t_data *data);
t_doors		*door_at(t_data *data, int x, int y);
void		doors_update(t_data *data, double dt);
int			player_is_in_tile(t_data *data, int tx, int ty);
void		handle_doors_movement(t_data *data);
void		init_all_doors(t_data *data);
int			is_wall_bonus(t_data *data, int mx, int my);
double		dda_first_hit_bonus(t_data *data, double rdx,
				double rdy, t_column *c);
void		dda_init(t_data *data, t_dda *a, double rdx, double rdy);
void		try_move_bonus(t_data *d, double dx, double dy);
int			count_doors_in_map(t_data *data);

int			init_textures_bonus(t_data *data);
void		draw_textured_column_bonus(t_data *d, t_column *c);
void		col_blit(t_data *d, t_column *c, mlx_texture_t *tex, int tex_x);
uint32_t	read_pixel_in_tex(mlx_texture_t *tex, int tx, int ty);

void		weapon_init(t_data *d);
void		weapon_draw(t_data *d, double dt);
void		weapon_shoot(t_data *d);

void		put_error_and_exit(t_data *data, char *str);
void		draw_background(t_data *data, mlx_image_t *img);

#endif