/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaxobe <kaaxobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:41:43 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/01 17:19:04 by kaaxobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_point_info(char *str, int *nbr, int *color)
{
	char		**strs;
	const char	*prefix = "0x";
	char		*color_str;

	strs = ft_split(str, ',');
	if (strs == NULL)
	{
		free_strs(strs);
		return ;
	}
	*nbr = ft_atoi(strs[0]);
	if (strs[1] != NULL)
	{
		color_str = &strs[1][ft_strlen(prefix)];
		*color = ft_atoi_base(color_str, "0123456789ABCDEF");
	}
	free_strs(strs);
	return ;
}
