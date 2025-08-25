/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:01:28 by mlavry            #+#    #+#             */
/*   Updated: 2025/08/25 17:59:12 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		printf("Invalid numer of args\n");
		return (0);
	}
	data = open_map();
	if (!data)
		return (0);
	if (!create_tab(data, argv[1]))
		return (0);
	print_tab(data);
}
