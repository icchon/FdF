/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:30:20 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 19:58:06 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_obj(t_obj *obj, char *block, int i, int j)
{
	int			color;
	int			nbr;
	t_vector3	cur;

	color = 0XFFFFFF;
	set_point_info(block, &nbr, &color);
	cur = ft_new_vec3(i, j, nbr);
	obj->cur = cur;
	obj->iso = isometoric_transform(cur);
	obj->color = color;
	return (1);
}

int	set_objs(t_obj **objs, int fd, t_vector2 map_size)
{
	int		i;
	int		j;
	char	*line;
	char	**strs;
	t_obj	obj;

	i = -1;
	while (++i < map_size.y)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (0);
		strs = ft_split(line, ' ');
		if (strs == NULL)
			return (free(line), 0);
		j = 0;
		while (j < map_size.x)
		{
			set_obj(&obj, strs[i], i, j);
			objs[i][j++] = obj;
		}
		free(line);
		free_strs(strs);
	}
	return (1);
}

t_obj	**create_objs(t_vector2 map_size)
{
	t_obj	**objs;
	int		i;

	objs = (t_obj **)malloc(sizeof(t_obj *) * map_size.y);
	if (objs == NULL)
		return (NULL);
	i = 0;
	while (i < map_size.y)
	{
		objs[i] = (t_obj *)malloc(sizeof(t_obj) * map_size.x);
		if (objs[i++] == NULL)
			return (free_objs(objs), NULL);
	}
	return (objs);
}

t_map	create_map(char *path)
{
	t_obj		**objs;
	t_map		map;
	int			fd;
	t_vector2	map_size;

	map_size = get_map_size(path);
	objs = create_objs(map_size);
	if (objs == NULL)
		return (get_invalid_map());
	fd = open(path, O_RDONLY);
	if (!set_objs(objs, fd, map_size))
		return (free_objs(objs), close(fd), get_invalid_map());
	map = new_map(objs, map_size);
	return (map);
}
