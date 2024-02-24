/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 12:43:13 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/02/24 16:00:25 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

		// start_ray(x, game, &calc);
		// init_dda(game, &calc);
		// perform_dda(game, &calc);
		// init_wall_texture(game, &calc);
		// input_wall_texture(x, game, &calc);

/**
 * check if a wall is hit 
 * @param side which side of the wall is hit
 * 0 is W/E (x-dir) wall; 1 is N/S(y-dirc)
*/
void	perform_dda(t_cub *cub, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedt_x < ray->sidedt_y)
		{
			ray->sidedt_x += ray->deltadt_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedt_y += ray->deltadt_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map->map2d[ray->map_x][ray->map_y] > '0')
			hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = ray->sidedt_x - ray->deltadt_x;
	else
		ray->wall_dist = ray->sidedt_y - ray->deltadt_y;	
}

void	init_step(t_ray *ray, t_player *ply)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedt_x = (ply->ply_x - ray->map_x) * ray->deltadt_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedt_x = (ray->map_x + 1.0 - ply->ply_x) * ray->deltadt_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedt_y = (ply->ply_y - ray->map_y) * ray->deltadt_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedt_y = (ray->map_y + 1.0 - ply->ply_y) * ray->deltadt_y;
	}
}

void	init_ray(t_ray *ray, t_player *ply, int x)
{
	ray->cam_x = 2 * x / (double)WIDTH - 1;
	ray->raydir_x = ply->dir_x + ply->plane_x * ray->cam_x;
	ray->raydir_y = ply->dir_y + ply->plane_y * ray->cam_x;
	ray->map_x = (int)ply->ply_x;
	ray->map_y = (int)ply->ply_y;
	ray->deltadt_x = fabs(1 / ray->raydir_x);
	ray->deltadt_y = fabs(1 / ray->raydir_y);
}

void	cast_ray(t_cub *cub)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(cub->ray, cub->ply, x);
		init_step(cub->ray, cub->ply);
		perform_dda(cub, cub->ray);
		calculate_wall(cub->ray, cub->ply);
		render_wall(cub, x);
	}
}