/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaxobe <kaaxobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:34:56 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/02 10:54:40 by kaaxobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_obj	new_obj(t_vector3 axo, t_vector3 car, int color)
{
	t_obj	obj;

	obj.axo = axo;
	obj.car = car;
	obj.color = color;
	return (obj);
}

void	free_objs(t_obj **objs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(objs[i]);
		i++;
	}
	free(objs);
	return ;
}
