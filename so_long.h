/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:39:30 by tjehaes           #+#    #+#             */
/*   Updated: 2024/10/22 11:12:37 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct img
{
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_wall;
	void	*img_collectible;
	int		height;
	int		width;
	char	*player;
	char	*floor;
	char	*wall;
	char	*collectible;
	char	*exit;
}				t_img;

typedef struct content
{
	char	exit;
	char	collectible;
	char	player;
	char	wall;
	char	space;
	int		count_player;
	int		count_exit;
	int		count_coll;
	int		count_coll_copy;
	int		count_exit_copy;
}				t_content;

typedef struct pos_s
{
	int		x;
	int		y;
}				t_pos;

typedef struct data
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			width;
	int			height;
	char		**map;
	char		**map_copy;
	t_content	content;
	t_img		img;
	t_pos		pos;
	int			count;
}				t_data;

int		check_col(char *map_line, char wall, t_data *data);
int		check_line(char *map_line, char wall);
int		check_wrong_char(char *map_line, t_content *content);
void	check_count(t_data *data);
int		check_format(char **map);

int		key_press(int keycode, t_data *data);
int		move_check(t_data *data, char direction);
void	get_new_position(t_data *data, int *new_x, int *new_y, char direction);
void	win_game(t_data *data);
void	move_player(t_data *data, int new_x, int new_y);

void	*free_map(t_data *data);
char	*handle_read_error(char *buff);
char	*read_file_content(int fd, char *buff);
char	*get_map(int fd);
char	**map_checker(int i, t_data *data);
char	**create_map(int fd, t_data *data);
char	**open_map(char **str, t_data *data);
char	**check_map_content(t_data *data);

void	print_ground(t_data *data);
void	print_cpe(t_data *data);
int		print_all(t_data *data);
void	game_display(t_data *data);
void	print_img(t_data *data, void *img, int x, int y);

void	set_content(t_content *content);
void	set_img(t_data *data);
int		count_collect(t_data *data);
int		end(t_data *data);

int		is_solvable(t_data *data);
void	*free_map_copy(t_data *data);

#endif
