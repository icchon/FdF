/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_trans2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:04:43 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/31 07:44:12 by kaisobe          ###   ########.fr       */
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
			if (type == AXO)
				map.objs[i][j].axo = ft_add_vec3(map.objs[i][j].axo, offset);
			else
				map.objs[i][j].car = ft_add_vec3(map.objs[i][j].car, offset);
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
	double		norm;

	v = ft_new_vec3(a, a, a);
	i = -1;
	norm = ft_norm_vec3(carmax(map));
	if (norm > INT_MAX || norm < 10)
		return ;
	while (++i < map.map_size.y)
	{
		j = -1;
		while (++j < map.map_size.x)
		{
			if (type == AXO)
				map.objs[i][j].axo = ft_mul_vec3(map.objs[i][j].axo, v);
			else
				map.objs[i][j].car = ft_mul_vec3(map.objs[i][j].car, v);
		}
	}
	bias = ft_mul_vec3(calc_center_window(), ft_new_vec3(a - 1, a - 1, a - 1));
	translate(map, ft_mul_vec3(ft_new_vec3(-1, -1, -1), bias), AXO);
}

t_vector3	carmax(t_map map)
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
			if (map.objs[i][j].car.x > ans.x)
				ans.x = map.objs[i][j].car.x;
			if (map.objs[i][j].car.y > ans.y)
				ans.y = map.objs[i][j].car.y;
			if (map.objs[i][j].car.z > ans.z)
				ans.z = map.objs[i][j].car.z;
			j++;
		}
	}
	return (ans);
}

void	scale_height(t_map map, double a)
{
	int			i;
	int			j;
	t_vector3	v;

	v = ft_new_vec3(1, 1, a);
	i = 0;
	if (fabs(carmax(map).z) > INT_MAX)
		return ;
	while (i < map.map_size.y)
	{
		j = 0;
		while (j < map.map_size.x)
		{
			map.objs[i][j].car = ft_mul_vec3(map.objs[i][j].car, v);
			map.objs[i][j].axo = axometoric_transform(map.objs[i][j].car,
					map.phases);
			j++;
		}
		i++;
	}
}
