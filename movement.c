/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:57:00 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/23 11:06:51 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		end(data);
	else if (keycode == 122)
		move_check(data, 'z');
	else if (keycode == 113)
		move_check(data, 'q');
	else if (keycode == 115)
		move_check(data, 's');
	else if (keycode == 100)
		move_check(data, 'd');
	return (0);
}

int	move_check(t_data *data, char direction)
{
	int	new_x;
	int	new_y;

	get_new_position(data, &new_x, &new_y, direction);
	if (data->map[new_y][new_x] == data->content.exit
			&& count_collect(data) != 0)
		return (0);
	if (data->map[new_y][new_x] != data->content.wall)
	{
		if (data->map[new_y][new_x] == data->content.exit
		&& count_collect(data) == 0)
			win_game(data);
		else
			move_player(data, new_x, new_y);
	}
	return (0);
}

void	get_new_position(t_data *data, int *new_x, int *new_y, char direction)
{
	*new_x = data->pos.x / data->img.height;
	*new_y = data->pos.y / data->img.width;
	if (direction == 'z')
		*new_y -= 1;
	else if (direction == 's')
		*new_y += 1;
	else if (direction == 'd')
		*new_x += 1;
	else if (direction == 'q')
		*new_x -= 1;
}

void	win_game(t_data *data)
{
	data->count += 1;
	ft_printf("GG you win in : %d moves !\n", data->count);
	end(data);
}

void	move_player(t_data *data, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	old_x = data->pos.x / data->img.height;
	old_y = data->pos.y / data->img.width;
	data->map[old_y][old_x] = data->content.space;
	data->map[new_y][new_x] = data->content.player;
	print_img(data, data->img.img_floor, old_x, old_y);
	print_img(data, data->img.img_player, new_x, new_y);
	data->pos.x = new_x * data->img.width;
	data->pos.y = new_y * data->img.height;
	data->count += 1;
	ft_printf("move n°%d\n", data->count);
}
