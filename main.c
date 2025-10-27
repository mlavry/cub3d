/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:01:28 by mlavry            #+#    #+#             */
/*   Updated: 2025/10/23 21:06:44 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	print_params_debug(t_params *p)
{
	printf("=== DEBUG PARAMETERS ===\n");
	if (p->no_path)
		printf("NO texture: %s\n", p->no_path);
	if (p->so_path)
		printf("SO texture: %s\n", p->so_path);
	if (p->we_path)
		printf("WE texture: %s\n", p->we_path);
	if (p->ea_path)
		printf("EA texture: %s\n", p->ea_path);
	printf("Floor RGB : %d,%d,%d\n", p->f_rgb[0], p->f_rgb[1], p->f_rgb[2]);
	printf("Ceil  RGB : %d,%d,%d\n", p->c_rgb[0], p->c_rgb[1], p->c_rgb[2]);
	printf("========================\n");
}

void print_map_debug(char **map)
{
	int i = 0;
	printf("=== DEBUG MAP ===\n");
	while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
}


void    debug_map_lengths(char **map)
{
    int i = 0;
    while (map[i])
    {
        printf("Ligne %d: '%s' (len=%zu)\n", i, map[i], strlen(map[i]));
        i++;
    }
}*/

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = calloc(1, sizeof(*data));
	if (!data)
	{
		perror("calloc");
		return (1);
	}
	if (parser(data, argc, argv))
		return (0);
	data->tiles_y = data->count;
	data->tiles_x = data->max_len;
	launch_game(data);
}
