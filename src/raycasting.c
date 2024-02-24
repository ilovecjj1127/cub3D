/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 12:43:13 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/02/24 11:17:56 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

		// start_ray(x, game, &calc);
		// init_dda(game, &calc);
		// perform_dda(game, &calc);
		// init_wall_texture(game, &calc);
		// input_wall_texture(x, game, &calc);

void	init_ray(t_ray *ray, t_player *ply, int x)
{
	ray->cam_x = 2 * x / (double)WIDTH - 1;
	ray->raydir_x = ply->dir_x + ply->plane_x * ray->cam_x;
	ray->raydir_y = ply->dir_y + ply->plane_y * ray->cam_x;
	ray->map_x = (int)ply->ply_x;
	ray->map_y = (int)ply->ply_y;
	ray->deltadt_x = sqrt(1 + pow(ray->raydir_x, 2))
	ray->deltady_y = 
	ray->hit = 0
}

void	cast_ray(t_cub *cub)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(cub->ray, cub->ply, x);
		render_ray(cub, x);
	}
	(void) cub;
}