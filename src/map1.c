/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaxobe <kaaxobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:30:20 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/02 14:11:25 by kaaxobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_obj(t_obj *obj, char *block, t_vector2 xy, t_phases phases)
{
	int			color;
	int			nbr;
	t_vector3	car;

	color = 0XFFFFFF;
	set_point_info(block, &nbr, &color);
	car = ft_new_vec3(xy.x, xy.y, nbr);
	obj->car = car;
	obj->axo = axometoric_transform(car, phases);
	obj->color = color;
	return (1);
}

int	set_objs(t_obj **objs, int fd, t_vector2 map_size, t_phases phases)
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
			set_obj(&obj, strs[j], (t_vector2){i, j}, phases);
			objs[i][j++] = obj;
		}
		free_strs(strs);
		free((ft_printf("."), line));
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
			return (free_objs(objs, map_size.y), NULL);
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
	if (!set_objs(objs, fd, map_size, (t_phases){M_PI / 6, M_PI / 6, M_PI / 2}))
		return (free_objs(objs, map_size.y), close(fd), get_invalid_map());
	map = new_map(objs, map_size, (t_phases){M_PI / 6, M_PI / 6, M_PI / 2});
	return (map);
}

void	free_map(t_map map)
{
	t_obj	**objs;

	objs = map.objs;
	free_objs(objs, map.map_size.y);
	return ;
}
