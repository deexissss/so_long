/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:04:11 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/18 13:58:24 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Error\nThe program need 1 .ber file\n");
		return (0);
	}
	else
	{
		data.count = 0;
		data.mlx_ptr = mlx_init();
		set_content(&(data.content));
		data.map = open_map(argv, &data);
		if (data.map != NULL)
		{
			set_img(&data);
			game_display(&data);
		}
		else
			end(&data);
	}
	return (1);
}
