/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:29:51 by kaisobe           #+#    #+#             */
/*   Updated: 2024/12/29 19:40:00 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_count_words(char const *s, char c)
{
	int	cnt;
	int	is_head;
	int	i;

	cnt = 0;
	is_head = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			is_head = 1;
		}
		else
		{
			if (is_head)
			{
				cnt++;
			}
			is_head = 0;
		}
		i++;
	}
	return (cnt);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}
