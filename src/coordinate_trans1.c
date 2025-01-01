/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_trans1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:32:45 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 19:23:36 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	adjust_iso_scale(t_map map)
{
	t_vector3	max;
	t_vector3	min;
	double		h;
	double		w;
	double		scale;

	max = isomax(map);
	min = isomin(map);
	w = fabs(max.x - min.x);
	h = fabs(max.y - min.y);
	scale = 1;
	if (w > 0 && h > 0)
	{
		if (WINDOW_WIDTH / w < WINDOW_HEIGHT / h)
		{
			scale = WINDOW_WIDTH / w;
		}
		else
		{
			scale = WINDOW_HEIGHT / h;
		}
	}
	upscale(map, scale, ISO);
}

void	rotate_coordinate(t_map map, double phase, t_vector3 shaft)
{
	t_vector3	x;
	int			i;
	int			j;

	i = 0;
	while (i < map.map_size.y)
	{
		j = 0;
		while (j < map.map_size.x)
		{
			x = map.objs[i][j].cur;
			map.objs[i][j].cur = ft_rotate_vec3(x, shaft, phase);
			j++;
		}
		i++;
	}
}

void	adjust_iso_position(t_map map)
{
	t_vector3	max;
	t_vector3	min;
	double		x_offset;
	double		y_offset;

	max = isomax(map);
	min = isomin(map);
	x_offset = (WINDOW_WIDTH - max.x - min.x) / 2;
	y_offset = (WINDOW_HEIGHT - max.y - min.y) / 2;
	translate(map, ft_new_vec3(x_offset, y_offset, 0), ISO);
}

void	adjust_map(t_map map)
{
	adjust_iso_scale(map);
	adjust_iso_position(map);
	fetch_coordinate(map, CAR);
	return ;
}

void	fetch_coordinate(t_map map, t_coordinate to_fetch)
{
	int			i;
	int			j;
	t_vector3	v;

	i = 0;
	while (i < map.map_size.y)
	{
		j = 0;
		while (j < map.map_size.x)
		{
			if (to_fetch == ISO)
			{
				v = isometoric_transform(map.objs[i][j].cur);
				map.objs[i][j].iso = v;
			}
			else if (to_fetch == CAR)
			{
				v = isometoric_rev_transform(map.objs[i][j].iso);
				map.objs[i][j].cur = v;
			}
			j++;
		}
		i++;
	}
}
