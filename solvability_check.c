/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvability_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:01:07 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/23 11:04:54 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	copy_map(t_data *data)
{
	int	i;

	data->map_copy = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map_copy)
		return ;
	i = 0;
	while (i < data->height)
	{
		data->map_copy[i] = ft_strdup(data->map[i]);
		i++;
	}
	data->map_copy[i] = NULL;
}

void	flood_fill(char **map_copy, int x, int y, t_content *content)
{
	if (x < 0 || y < 0 || !map_copy[y] || !map_copy[y][x])
		return ;
	if (map_copy[y][x] == content->wall || map_copy[y][x] == '1')
		return ;
	if (map_copy[y][x] == content->collectible
	|| map_copy[y][x] == content->space)
		map_copy[y][x] = '1';
	if (map_copy[y][x] == content->exit)
		map_copy[y][x] = '1';
	flood_fill(map_copy, x + 1, y, content);
	flood_fill(map_copy, x - 1, y, content);
	flood_fill(map_copy, x, y + 1, content);
	flood_fill(map_copy, x, y - 1, content);
}

void	find_player_position(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->pos.x = x;
				data->pos.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	check_player_pos(t_data *data)
{
	if (data->pos.x == 0 || data->pos.y == 0)
	{
		free_map_copy(data);
		free_map(data);
		ft_printf("Error\nThe map need 1 Player/Exit ");
		ft_printf("and at least 1 collectible\n");
		return (0);
	}
	return (1);
}

int	is_solvable(t_data *data)
{
	int	y;
	int	x;

	find_player_position(data);
	check_player_pos(data);
	copy_map(data);
	flood_fill(data->map_copy, data->pos.x, data->pos.y, &data->content);
	y = 0;
	while (data->map_copy[y])
	{
		x = 0;
		while (data->map_copy[y][x])
		{
			if (data->map_copy[y][x] == data->content.collectible
			|| data->map_copy[y][x] == data->content.exit)
			{
				free_map_copy(data);
				return (0);
			}
			x++;
		}
		y++;
	}
	free_map_copy(data);
	return (1);
}
