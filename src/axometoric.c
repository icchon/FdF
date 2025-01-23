/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axometoric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaxobe <kaaxobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:30:59 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/21 08:52:09 by kaaxobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	axomax(t_map map)
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
			if (map.objs[i][j].axo.x > ans.x)
				ans.x = map.objs[i][j].axo.x;
			if (map.objs[i][j].axo.y > ans.y)
				ans.y = map.objs[i][j].axo.y;
			if (map.objs[i][j].axo.z > ans.z)
				ans.z = map.objs[i][j].axo.z;
			j++;
		}
	}
	return (ans);
}

t_vector3	axomin(t_map map)
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
			if (map.objs[i][j].axo.x < ans.x)
				ans.x = map.objs[i][j].axo.x;
			if (map.objs[i][j].axo.y < ans.y)
				ans.y = map.objs[i][j].axo.y;
			if (map.objs[i][j].axo.z < ans.z)
				ans.z = map.objs[i][j].axo.z;
			j++;
		}
	}
	return (ans);
}

t_vector3	axometoric_transform(t_vector3 pos, t_phases phases)
{
	t_vector3	after;
	double		alpha;
	double		beta;
	double		gammma;

	alpha = phases.alpha;
	beta = phases.beta;
	gammma = phases.gammma;
	after.x = -1 * (pos.x * cos(alpha) - pos.y * cos(beta));
	after.y = (pos.x * sin(alpha) + pos.y * sin(beta) - pos.z * sin(gammma));
	after.z = pos.z;
	return (after);
}

t_vector3	axometoric_rev_transform(t_vector3 pos, t_phases phases)
{
	t_vector3	after;
	double		alpha;
	double		beta;
	double		gammma;

	alpha = phases.alpha;
	beta = phases.beta;
	gammma = phases.gammma;
	after.x = pos.x * (-1 / (cos(alpha) + (sin(alpha) / tan(beta)))) + pos.y
		* (1 / (sin(alpha) + (cos(alpha) * tan(beta)))) + pos.z * (sin(gammma)
			/ (sin(alpha) + (cos(alpha) * tan(beta))));
	after.y = pos.x * (sin(alpha) / sin(alpha + beta)) + pos.y * (cos(alpha)
			/ sin(alpha + beta)) + pos.z * ((sin(gammma) * cos(alpha))
			/ sin(alpha + beta));
	after.z = pos.z;
	return (after);
}
