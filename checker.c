/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:54:35 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/22 11:11:37 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_col(char *map_line, char wall, t_data *data)
{
	int		i;

	i = 0;
	while (map_line[i])
		i++;
	if (map_line[0] != wall || map_line[i - 1] != wall)
	{
		ft_printf("Error\nThe map is not close\n");
		return (0);
	}
	data->width = i;
	return (1);
}

int	check_line(char *map_line, char wall)
{
	int		i;

	i = 0;
	while (map_line[i])
	{
		if (map_line[i] != wall)
		{
			ft_printf("Error\nThe map is not close\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_wrong_char(char *map_line, t_content *content)
{
	int		i;

	i = 0;
	while (map_line[i])
	{
		if (map_line[i] != content->wall && map_line[i] != content->player
			&& map_line[i] != content->exit
			&& map_line[i] != content->collectible
			&& map_line[i] != content->space)
		{
			ft_printf("Error\nExtra char in the map\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_count(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == data->content.collectible)
				data->content.count_coll += 1;
			if (data->map[y][x] == data->content.player)
				data->content.count_player += 1;
			if (data->map[y][x] == data->content.exit)
				data->content.count_exit += 1;
			x++;
		}
		x = 0;
		y++;
	}
}

int	check_format(char **map)
{
	int		y;
	int		x;
	int		count_x;

	x = 0;
	y = 0;
	count_x = 0;
	while (map[0][count_x])
		count_x++;
	while (map[y] != NULL)
	{
		while (map[y][x])
			x++;
		if (x != count_x)
		{
			ft_printf("Error\nMap is not rectangular\n");
			return (0);
		}
		x = 0;
		y++;
	}
	return (1);
}
