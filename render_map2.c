/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:10:01 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/22 10:41:34 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**create_map(int fd, t_data *data)
{
	char	*map_str;

	map_str = get_map(fd);
	if (!map_str)
		return (NULL);
	data->map = ft_split(map_str, '\n');
	free(map_str);
	check_count(data);
	if (!(check_format(data->map)))
		return (free_map(data));
	if (!(check_line(data->map[0], data->content.wall)))
		return (free_map(data));
	return (map_checker(1, data));
}

char	**open_map(char **str, t_data *data)
{
	int		fd;

	data->map = NULL;
	if (ft_strchr(str[1], ".ber") == 0)
	{
		ft_printf("Error\nThe program need 1 .ber file\n");
		return (0);
	}
	fd = open(str[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCan't open the file\n");
		return (0);
	}
	data->map = create_map(fd, data);
	return (data->map);
}

void	*free_map_copy(t_data *data)
{
	int	i;

	i = 0;
	if (!data->map_copy)
		return (NULL);
	while (data->map_copy[i] != NULL)
	{
		free(data->map_copy[i]);
		i++;
	}
	free(data->map_copy);
	data->map_copy = NULL;
	return (0);
}
