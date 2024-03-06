/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 15:28:53 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/06 15:19:58 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * @param tex_x position on the texture
*/
void	calculate_wall(t_cub *cub, t_ray *ray)
{
	double	wall_x;
	
	ray->line_h = (int)(HEIGHT / ray->wall_dist);	
	ray->draw_start = ft_max(0, HEIGHT / 2 - ray->line_h / 2);
	ray->draw_end = ft_min(HEIGHT - 1, HEIGHT / 2 + ray->line_h / 2);
	if (ray->side == 0 && ray->raydir_x > 0)
		ray->wall_tex = cub->tex->so;
	else if (ray->side == 0 && ray->raydir_x < 0)
		ray->wall_tex = cub->tex->no;
	else if (ray->side == 1 && ray->raydir_y > 0)
		ray->wall_tex = cub->tex->ea;
	else if (ray->side == 1 && ray->raydir_y < 0)
		ray->wall_tex = cub->tex->we;
	if (ray->side == 0)
		wall_x = cub->ply->ply_y + ray->wall_dist * ray->raydir_y;
	else
		wall_x = cub->ply->ply_x + ray->wall_dist * ray->raydir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)TILE);
}

uint32_t	get_color(t_ray *ray, int x, int y)
{
	int				r;
	int				g;
	int				b;
	mlx_texture_t	*t;
	
	t = ray->wall_tex;
	r = t->pixels[(y * t->width + x) * t->bytes_per_pixel];
	g = t->pixels[(y * t->width + x) * t->bytes_per_pixel + 1];
	b = t->pixels[(y * t->width + x) * t->bytes_per_pixel + 2];
	return ((uint32_t)(r << 24 | g << 16 | b << 8 | 255));
}

void	render_wall(t_cub *cub, t_ray *ray, int x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;

	y = -1;
	step = 1.0 * TILE / ray->line_h;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_h / 2) * step;
	while (++y < HEIGHT)
	{
		if (y < ray->draw_start)
			mlx_put_pixel(cub->img, x, y, cub->tex->color_c);
		else if (y > ray->draw_end)
			mlx_put_pixel(cub->img, x, y, cub->tex->color_f);
		else
		{
			tex_y = (int)tex_pos & (TILE - 1);
			tex_pos += step;
			mlx_put_pixel(cub->img, x, y, get_color(ray, ray->tex_x, tex_y));
		}
	}
}
