/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:01:15 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/22 11:11:37 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*free_map(t_data *data)
{
	int		i;

	i = 0;
	if (!data->map)
		return (NULL);
	while (data->map[i] != NULL)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
	return (0);
}

char	*handle_read_error(char *buff)
{
	free(buff);
	ft_printf("Error\nCan't open the file\n");
	return (NULL);
}

char	*read_file_content(int fd, char *buff)
{
	char	c;
	int		char_count;
	int		i;

	i = 0;
	char_count = 1;
	while (char_count > 0)
	{
		char_count = read(fd, &c, 1);
		if (char_count == -1)
			return (handle_read_error(buff));
		if (char_count > 0)
			buff[i++] = c;
	}
	buff[i] = '\0';
	if (i == 0)
		return (handle_read_error(buff));
	return (buff);
}

char	*get_map(int fd)
{
	char	*buff;

	buff = malloc(10000);
	if (!buff)
		return (NULL);
	return (read_file_content(fd, buff));
}

char	**map_checker(int i, t_data *data)
{
	while (data->map[i] != NULL)
	{
		if (!(check_col(data->map[i], data->content.wall, data)))
			return (free_map(data));
		else if (!(check_wrong_char(data->map[i], &(data->content))))
			return (free_map(data));
		i++;
	}
	data->height = i;
	if (!(check_line(data->map[i - 1], data->content.wall)))
		return (free_map(data));
	if (data->content.count_coll == 0 || data->content.count_exit != 1
		|| data->content.count_player != 1)
	{
		free_map(data);
		ft_printf("Error\nThe map need 1 Player/Exit ");
		ft_printf("and at least 1 collectible\n");
		return (0);
	}
	if (data->map == NULL || !is_solvable(data))
	{
		ft_printf("Error\nMap is not solvable\n");
		return (free_map(data));
	}
	return (data->map);
}
