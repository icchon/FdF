/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:19:26 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 19:52:06 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector2	get_map_size(char *path)
{
	char	*line;
	int		h;
	int		w;
	int		fd;

	h = 0;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		return (get_invalid_mapsize());
	}
	w = ft_count_words(line, ' ');
	while (line)
	{
		if (w != (int)ft_count_words(line, ' '))
			return (close(fd), get_invalid_mapsize());
		h++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (ft_new_vec2(w, h));
}

int	is_valid_block(char *str)
{
	char	**strs;

	strs = ft_split(str, ',');
	if (strs == NULL)
		return (0);
	if (ft_strslen((const char **)strs) < 1)
		return (free_strs(strs), 0);
	if (ft_strslen((const char **)strs) > 2)
		return (free_strs(strs), 0);
	if (!ft_isint(strs[0]))
		return (free_strs(strs), 0);
	return (1);
}

int	is_valid_line(int fd, int map_width)
{
	char	*line;
	char	**strs;
	int		i;

	i = 0;
	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	strs = ft_split(line, ' ');
	if (strs == NULL)
		return (free(line), 0);
	i = 0;
	while (i < map_width)
		if (!is_valid_block(strs[i++]))
			return (free_strs(strs), free(line), 0);
	return (free(line), free_strs(strs), 1);
}

int	is_valid_map(char *path)
{
	t_vector2	map_size;
	int			fd;
	int			i;

	i = 0;
	map_size = get_map_size(path);
	if (!is_invalid_mapsize(map_size))
		return (0);
	fd = open(path, O_RDONLY);
	while (i < map_size.y)
	{
		if (!is_valid_line(fd, map_size.x))
		{
			close(fd);
			return (0);
		}
		i++;
	}
	return (close(fd), 1);
}