/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:07:46 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/02 14:05:04 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
	{
		return (0);
	}
	vars.map_path = argv[1];
	ft_printf("start validating map\n");
	if (!is_valid_map(vars.map_path))
	{
		ft_printf("\ninvalid map\n");
		return (0);
	}
	ft_printf("\nend validating map\n");
	vars.on_mouse = 0;
	ft_printf("\nstart reading map\n");
	vars.map = create_map(vars.map_path);
	ft_printf("\nend reading map\n");
	adjust_map(vars.map);
	init(&vars);
	return (1);
}
