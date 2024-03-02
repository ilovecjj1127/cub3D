/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/02 12:50:07 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/02 12:50:29 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_left(t_player *ply)
{
	double	old_dirx;
	double	old_plnx;
	double	rot;

	old_dirx = ply->dir_x;
	old_plnx = ply->plane_x;
	rot = ply->speed_r;
	ply->dir_x = ply->dir_x * cos(-rot) - ply->dir_y * sin(-rot);
	ply->dir_x = old_dirx * sin(-rot) + ply->dir_y * cos(-rot);
	ply->plane_x = ply->plane_x * cos(-rot) - ply->plane_y * sin(-rot);
	ply->plane_y = old_plnx * sin(-rot) + ply->plane_y * cos(-rot);
}

void	rotate_right(t_player *ply)
{
	double	old_dirx;
	double	old_plnx;
	double	rot;

	old_dirx = ply->dir_x;
	old_plnx = ply->plane_x;
	rot = ply->speed_r;
	ply->dir_x = ply->dir_x * cos(rot) - ply->dir_y * sin(rot);
	ply->dir_x = old_dirx * sin(rot) + ply->dir_y * cos(rot);
	ply->plane_x = ply->plane_x * cos(rot) - ply->plane_y * sin(rot);
	ply->plane_y = old_plnx * sin(rot) + ply->plane_y * cos(rot);
}