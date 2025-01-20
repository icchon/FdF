/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometoric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:30:59 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/21 08:52:09 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	isomax(t_map map)
{
	int			h;
	int			w;
	t_vector3	ans;
	int			i;
	int			j;

	h = map.map_size.y;
	w = map.map_size.x;
	ans = ft_new_vec3((double)INT_MIN, (double)INT_MIN, (double)INT_MIN);
	i = -1;
	while (++i < h)
	{
		j = 0;
		while (j < w)
		{
			if (map.objs[i][j].iso.x > ans.x)
				ans.x = map.objs[i][j].iso.x;
			if (map.objs[i][j].iso.y > ans.y)
				ans.y = map.objs[i][j].iso.y;
			if (map.objs[i][j].iso.z > ans.z)
				ans.z = map.objs[i][j].iso.z;
			j++;
		}
	}
	return (ans);
}

t_vector3	isomin(t_map map)
{
	int			h;
	int			w;
	t_vector3	ans;
	int			i;
	int			j;

	h = map.map_size.y;
	w = map.map_size.x;
	ans = ft_new_vec3((double)INT_MAX, (double)INT_MAX, (double)INT_MAX);
	i = -1;
	while (++i < h)
	{
		j = 0;
		while (j < w)
		{
			if (map.objs[i][j].iso.x < ans.x)
				ans.x = map.objs[i][j].iso.x;
			if (map.objs[i][j].iso.y < ans.y)
				ans.y = map.objs[i][j].iso.y;
			if (map.objs[i][j].iso.z < ans.z)
				ans.z = map.objs[i][j].iso.z;
			j++;
		}
	}
	return (ans);
}

t_vector3	isometoric_transform(t_vector3 pos)
{
	t_vector3		after;
	const double	phase = M_PI / 6;

	after.x = -1 * (pos.x * cos(phase) - pos.y * cos(phase));
	after.y = (pos.x * sin(phase) + pos.y * sin(phase) - pos.z);
	after.z = pos.z;
	return (after);
}

t_vector3	isometoric_rev_transform(t_vector3 pos)
{
	t_vector3		after;
	const double	phase = M_PI / 6;

	after.x = pos.x / (2 * cos(phase)) + pos.y / (2 * sin(phase)) + pos.z / (2
			* sin(phase));
	after.y = -1 * pos.x / (2 * cos(phase)) + pos.y / (2 * sin(phase)) + pos.z
		/ (2 * sin(phase));
	after.z = pos.z;
	return (after);
}
