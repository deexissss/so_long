/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:58:07 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/22 11:11:37 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_content(t_content *content)
{
	content->exit = 'E';
	content->player = 'P';
	content->wall = '1';
	content->space = '0';
	content->collectible = 'C';
	content->count_player = 0;
	content->count_exit = 0;
	content->count_coll = 0;
}

void	set_img(t_data *data)
{
	data->img.player = "./assets/player_left.xpm";
	data->img.exit = "./assets/exit_texture.xpm";
	data->img.collectible = "./assets/collectible.xpm";
	data->img.floor = "./assets/floor_texture.xpm";
	data->img.wall = "./assets/wall_texture.xpm";
	data->img.height = 80;
	data->img.width = 80;
	data->img.img_wall = mlx_xpm_file_to_image(data->mlx_ptr, data->img.wall,
			&(data->img.width), &(data->img.height));
	data->img.img_floor = mlx_xpm_file_to_image(data->mlx_ptr, data->img.floor,
			&(data->img.width), &(data->img.height));
	data->img.img_exit = mlx_xpm_file_to_image(data->mlx_ptr, data->img.exit,
			&(data->img.width), &(data->img.height));
	data->img.img_collectible = mlx_xpm_file_to_image(data->mlx_ptr,
			data->img.collectible, &(data->img.width), &(data->img.height));
	data->img.img_player = mlx_xpm_file_to_image(data->mlx_ptr,
			data->img.player, &(data->img.width), &(data->img.height));
}

int	count_collect(t_data *data)
{
	int		y;
	int		x;
	int		count;

	y = 0;
	x = 0;
	count = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == data->content.collectible)
				count++;
			x++;
		}
		x = 0;
		y++;
	}
	return (count);
}

int	end(t_data *data)
{
	int		i;

	i = 0;
	if (data->map != NULL)
	{
		free_map(data);
		mlx_destroy_image(data->mlx_ptr, data->img.img_wall);
		mlx_destroy_image(data->mlx_ptr, data->img.img_floor);
		mlx_destroy_image(data->mlx_ptr, data->img.img_collectible);
		mlx_destroy_image(data->mlx_ptr, data->img.img_player);
		mlx_destroy_image(data->mlx_ptr, data->img.img_exit);
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	}
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
