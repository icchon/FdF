/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_trans2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:04:43 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 19:09:39 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_map map, t_vector3 offset, t_coordinate type)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.map_size.y)
	{
		j = 0;
		while (j < map.map_size.x)
		{
			if (type == ISO)
				map.objs[i][j].iso = ft_add_vec3(map.objs[i][j].iso, offset);
			else
				map.objs[i][j].cur = ft_add_vec3(map.objs[i][j].cur, offset);
			j++;
		}
		i++;
	}
}

void	upscale(t_map map, double a, t_coordinate type)
{
	int			i;
	int			j;
	t_vector3	v;
	t_vector3	bias;

	v = ft_new_vec3(a, a, a);
	i = 0;
	while (i < map.map_size.y)
	{
		j = 0;
		while (j < map.map_size.x)
		{
			if (type == ISO)
				map.objs[i][j].iso = ft_mul_vec3(map.objs[i][j].iso, v);
			else
				map.objs[i][j].cur = ft_mul_vec3(map.objs[i][j].cur, v);
			j++;
		}
		i++;
	}
	bias = calc_center_window();
	bias = ft_mul_vec3(bias, ft_new_vec3(a - 1, a - 1, a - 1));
	translate(map, ft_mul_vec3(ft_new_vec3(-1, -1, -1), bias), ISO);
}

void	scale_height(t_map map, double a)
{
	int			i;
	int			j;
	t_vector3	v;

	v = ft_new_vec3(1, 1, a);
	i = 0;
	while (i < map.map_size.y)
	{
		j = 0;
		while (j < map.map_size.x)
		{
			map.objs[i][j].cur = ft_mul_vec3(map.objs[i][j].cur, v);
			map.objs[i][j].iso = isometoric_transform(map.objs[i][j].cur);
			j++;
		}
		i++;
	}
}
