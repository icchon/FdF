/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:07:46 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/31 07:40:10 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
		return (0);
	vars.map_path = argv[1];
	ft_printf("start validating map\n");
	if (!is_valid_map(vars.map_path))
	{
		ft_printf("\ninvalid map\n");
		return (0);
	}
	vars.on_mouse = 0;
	vars.on_shift = 0;
	vars.can_change_height = 1;
	ft_printf("\nstart reading map\n");
	vars.map = create_map(vars.map_path);
	adjust_map(vars.map);
	ft_printf(CONTROL_MANUAL);
	init(&vars);
	return (1);
}
