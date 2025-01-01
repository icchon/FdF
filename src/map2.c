/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:21:56 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 17:22:09 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	new_map(t_obj **objs, t_vector2 map_size)
{
	t_map	map;

	map.objs = objs;
	map.map_size = map_size;
	return (map);
}

t_map	get_invalid_map(void)
{
	t_map	map;

	map.map_size = ft_new_vec2(-1, -1);
	return (map);
}

t_vector2	get_invalid_mapsize(void)
{
	return (get_invalid_map().map_size);
}

int	is_invalid_mapsize(t_vector2 map_size)
{
	return (map_size.x < 0 || map_size.y < 0);
}

int	is_invalid_map(t_map map)
{
	return (is_invalid_mapsize(map.map_size));
}
