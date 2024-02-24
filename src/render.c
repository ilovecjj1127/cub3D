/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 15:28:53 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/02/24 16:43:59 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calculate_wall(t_ray *ray, t_player *ply)
{
}

int	get_color(t_cub *cub, t_ray *ray)
{
	mlx_texture_t	*texture;

	texture = get_texture(cub, cub->ray);
}

void	render_wall(t_cub *cub, int x)
{
	int	y;
	int	line_h = (int)(HEIGHT / cub->ray->wall_dist);
	int	draw_start = ft_max(0, HEIGHT / 2 - line_h / 2);
	int	draw_end = ft_min(HEIGHT - 1, HEIGHT / 2 + line_h / 2);

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < draw_start)
			mlx_put_pixel(cub->img, x, y, cub->tex->ceil);
		else if (y > draw_end)
			mlx_put_pixel(cub->img, x, y, cub->tex->floor);
		else
			mlx_put_pixel(cub->img, x, y, get_color(cub, cub->ray));
	}
}
