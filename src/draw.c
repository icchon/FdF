/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaxobe <kaaxobe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:30:30 by kaaxobe           #+#    #+#             */
/*   Updated: 2025/01/15 12:44:44 by kaaxobe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_axo(t_vars *vars)
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

static int	can_skip(t_obj start, t_obj end, double dx, double dy)
{
	int		cnt;
	double	x;
	double	y;

	x = start.axo.x;
	y = start.axo.y;
	cnt = 0;
	if ((fabs(end.axo.x - start.axo.x) < STEP) && (fabs(end.axo.y
				- start.axo.y) < STEP))
		return (1);
	if ((start.axo.x < 0 && end.axo.x < 0) || (start.axo.y < 0
			&& end.axo.y < 0))
		return (1);
	if ((start.axo.x >= WINDOW_WIDTH && end.axo.x >= WINDOW_WIDTH)
		|| (start.axo.y >= WINDOW_HEIGHT && end.axo.y >= WINDOW_HEIGHT))
		return (1);
	while (!(x > 0 && x < WINDOW_WIDTH) || !(y > 0 && y < WINDOW_HEIGHT))
	{
		x += dx;
		y += dy;
		if (++cnt > fmaxf(fabs(end.axo.x - start.axo.x), fabs(end.axo.y
					- start.axo.y)))
			return (1);
	}
	return (0);
}

void	draw_line(t_obj start, t_obj end, t_vars *vars)
{
	double	x;
	double	y;
	double	dx;
	double	dy;

	set_dxdy(&dx, &dy, end.axo.x - start.axo.x, end.axo.y - start.axo.y);
	if (can_skip(start, end, dx, dy))
		return ;
	x = start.axo.x;
	y = start.axo.y;
	while (!(x > 0 && x < WINDOW_WIDTH) || !(y > 0 && y < WINDOW_HEIGHT))
	{
		x += dx;
		y += dy;
	}
	while (((start.axo.x <= x && x <= end.axo.x) || (end.axo.x <= x
				&& x <= start.axo.x)) && ((start.axo.y <= y && y <= end.axo.y)
			|| (end.axo.y <= y && y <= start.axo.y)))
	{
		x += dx;
		y += dy;
		if ((x < 0 || x >= WINDOW_WIDTH) || (y < 0 || y >= WINDOW_HEIGHT))
			break ;
		put_pixel(vars, x, y, start.color);
	}
}

void	put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
