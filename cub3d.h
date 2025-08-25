/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:36:13 by mlavry            #+#    #+#             */
/*   Updated: 2025/08/25 17:54:27 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "GNL/get_next_line.h"
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "MLX42/MLX42.h"

typedef struct s_data
{
	char	**map;
	int		y;
}	t_data;

t_data	*open_map(void);
char	**create_tab(t_data *data, char *map_path);
void	print_tab(t_data *data);

#endif