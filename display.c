/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:49:21 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/22 11:11:37 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_all(t_data *data)
{
	print_ground(data);
	print_cpe(data);
	return (0);
}

void	print_ground(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (data->map[y] != NULL)
	{
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == data->content.wall)
				print_img(data, data->img.img_wall, x, y);
			if (data->map[y][x] == data->content.space)
				print_img(data, data->img.img_floor, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	print_cpe(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (data->map[y] != NULL)
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == data->content.collectible)
				print_img(data, data->img.img_collectible, x, y);
			if (data->map[y][x] == data->content.player)
			{
				data->pos.x = x * data->img.width;
				data->pos.y = y * data->img.height;
				print_img(data, data->img.img_player, x, y);
			}
			if (data->map[y][x] == data->content.exit)
				print_img(data, data->img.img_exit, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	game_display(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx_ptr,
			(data->width * data->img.width), (data->height * data->img.height),
			"so_long");
	if (data->mlx_win == NULL)
	{
		free(data->mlx_ptr);
		return ;
	}
	mlx_loop_hook(data->mlx_ptr, &print_all, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &key_press, data);
	mlx_hook(data->mlx_win, 17, 0, &end, data);
	mlx_loop(data->mlx_ptr);
	end(data);
}

void	print_img(t_data *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img,
		data->img.width * x, data->img.height * y);
}
