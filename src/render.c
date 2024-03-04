/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 15:28:53 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/02 17:18:00 by jiajchen      ########   odam.nl         */
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
		ray->wall_tex = cub->tex->no;
	else if (ray->side == 0 && ray->raydir_x < 0)
		ray->wall_tex = cub->tex->so;
	else if (ray->side == 1 && ray->raydir_y > 0)
		ray->wall_tex = cub->tex->ea;
	else if (ray->side == 1 && ray->raydir_y < 0)
		ray->wall_tex = cub->tex->we;
	if (ray->side == 0)
		wall_x = cub->ply->ply_y + ray->wall_dist * ray->raydir_y;
	else
		wall_x = cub->ply->ply_x + ray->wall_dist * ray->raydir_x;
	ray->tex_x = (int)(wall_x - floor(wall_x) * (double)TILE); //??????
	// ray->tex_x = TILE - ray->tex_x - 1;
}

/* https://github.com/codam-coding-college/MLX42/blob/200a9e8535644bb23f0c798bd2c6d5869934f92d/src/mlx_put_pixel.c#L15 */
uint32_t	get_color(t_ray *ray, int y)
{
	mlx_image_t	*tex;
	uint8_t		*pixel;
	int			x;
	// int			r;
	// int			g;
	// int			b;
	// int			a;
	
	x = ray->tex_x;
	tex = ray->wall_tex;
	pixel = &tex->pixels[(y * tex->width + x) * sizeof(int32_t)];
	// r = pixel[0];
	// g = pixel[1];
	// b = pixel[2];
	// a = pixel[3];
	printf("%u %u %u %u\n", pixel[0], pixel[1], pixel[2], pixel[3]);
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
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
			mlx_put_pixel(cub->img, x, y, cub->tex->ceil);
		else if (y > ray->draw_end)
			mlx_put_pixel(cub->img, x, y, cub->tex->floor);
		else
		{
			tex_y = (int)tex_pos & (TILE - 1);
			tex_pos += step;
			mlx_put_pixel(cub->img, x, y, get_color(ray, tex_y));
		}
	}
}
