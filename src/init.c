/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 17:00:50 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/06 15:23:58 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_delete_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cast_ray(cub);
	move(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

uint32_t	convert_color(char *str)
{
	int		r;
	int		g;
	int		b;
	
	r = ft_atoi(str);
	b = ft_atoi(ft_strchr(str, ',') + 1);
	g = ft_atoi(ft_strchr(ft_strchr(str, ',') + 1, ',') + 1);
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	load_textures(t_cub *cub)
{
	cub->tex->no = mlx_load_png(cub->tex->north);
	cub->tex->so = mlx_load_png(cub->tex->south);
	cub->tex->ea = mlx_load_png(cub->tex->east);
	cub->tex->we = mlx_load_png(cub->tex->west);
	if (!cub->tex->no || !cub->tex->so || !cub->tex->ea || !cub->tex->we)
		free_cub(cub, 1, "Error\npng open fails");
	cub->tex->color_c = convert_color(cub->tex->ceiling);
	cub->tex->color_f = convert_color(cub->tex->floor);
}

void	init_player(t_cub *cub)
{
	cub->ply->ply_x = cub->map->start_y + 0.5;
	cub->ply->ply_y = cub->map->start_x + 0.5;
	cub->ply->dir_x = 0;
	cub->ply->dir_y = 0;
	if (cub->map->direction == 'N')
		cub->ply->dir_x = -1;
	if (cub->map->direction == 'S')
		cub->ply->dir_x = 1;
	if (cub->map->direction == 'W')
		cub->ply->dir_y = -1;
	if (cub->map->direction == 'E')
		cub->ply->dir_y = 1;
	cub->ply->plane_x = 0;
	cub->ply->plane_y = 0.66;
	cub->ply->speed_m = 0.5;
	cub->ply->speed_r = 0.05;
}

t_cub	*init_cub(char *file)
{
	static t_cub	cub;

	cub.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	cub.map = ft_calloc(1, sizeof(t_map));
	cub.tex = ft_calloc(1, sizeof(t_textures));
	cub.ray = ft_calloc(1, sizeof(t_ray));
	cub.ply = ft_calloc(1, sizeof(t_player));
	if (!cub.mlx || !cub.map || !cub.tex || !cub.ply || !cub.ray)
		free_cub(&cub, 1, "init failed");
	if (parse_file(file, cub.map, cub.tex) == 0)
		free_cub(&cub, 1, NULL);
	load_textures(&cub);
	init_player(&cub);
	return (&cub);
}

void	free_cub(t_cub *cub, int ex, char *msg)
{
	if (msg)
		printf("%s\n", msg);
	if (cub->map)
	{
		free_arr(cub->map->map);
		free(cub->map);
	}
	if (cub->ply)
		free(cub->ply);
	if (cub->ray)
		free(cub->ray);
	if (cub->tex)
	{
		free_texture(cub->tex);
		free(cub->tex);
	}
	if (ex)
		exit(EXIT_FAILURE);
}