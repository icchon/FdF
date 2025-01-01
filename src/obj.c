/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:34:56 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/01 19:44:45 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_obj	new_obj(t_vector3 iso, t_vector3 cur, int color)
{
	t_obj	obj;

	obj.iso = iso;
	obj.cur = cur;
	obj.color = color;
	return (obj);
}

void	free_objs(t_obj **objs)
{
	int	i;

	i = 0;
	while (objs[i])
	{
		free(objs[i]);
		i++;
	}
	free(objs);
	return ;
}