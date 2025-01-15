/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisobe <kaisobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:30:30 by kaisobe           #+#    #+#             */
/*   Updated: 2025/01/15 12:44:44 by kaisobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_iso(t_vars *vars)
{
	int		i;
	int		j;
	t_obj	**objs;

	objs = vars->map.objs;
	i = 0;
	while (i < vars->map.map_size.y - 1)
	{
		j = 0;
		while (j < vars->map.map_size.x - 1)
		{
			draw_line(objs[i][j], objs[i][j + 1], vars);
			draw_line(objs[i][j], objs[i + 1][j], vars);
			draw_line(objs[i + 1][j], objs[i + 1][j + 1], vars);
			draw_line(objs[i][j + 1], objs[i + 1][j + 1], vars);
			j++;
		}
		i++;
	}
}

void	set_dxdy(double *dx, double *dy, double w, double h)
{
	if (fabs(w) < STEP)
	{
		*dy = (h / fabs(h)) * STEP;
		*dx = 0;
	}
	else if (fabs(h) < STEP)
	{
		*dx = (w / fabs(w)) * STEP;
		*dy = 0;
	}
	else
	{
		if (fabs(w) >= fabs(h))
		{
			*dx = (w / fabs(w)) * STEP;
			*dy = (h / w) * (*dx);
		}
		else
		{
			*dy = (h / fabs(h)) * STEP;
			*dx = (w / h) * (*dy);
		}
	}
}

void	draw_line(t_obj start, t_obj end, t_vars *vars)
{
	double	x;
	double	y;
	double	dx;
	double	dy;

	if ((fabs(end.iso.x - start.iso.x) < STEP) && (fabs(end.iso.y
				- start.iso.y) < STEP))
		return ;
	set_dxdy(&dx, &dy, end.iso.x - start.iso.x, end.iso.y - start.iso.y);
	x = start.iso.x;
	y = start.iso.y;
	while (((start.iso.x <= x && x <= end.iso.x) || (end.iso.x <= x
				&& x <= start.iso.x)) && ((start.iso.y <= y && y <= end.iso.y)
			|| (end.iso.y <= y && y <= start.iso.y)))
	{
		x += dx;
		y += dy;
		if (x < 0 || x >= WINDOW_WIDTH)
			break ;
		if (y < 0 || y >= WINDOW_HEIGHT)
			break ;
		put_pixel(vars, x, y, start.color);
	}
	return ;
}

void	put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
