/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 12:48:15 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/02 16:03:03 by jiajchen      ########   odam.nl         */
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

t_map	*init_map()
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	map->map2d = ft_calloc(10, sizeof(char *));
	map->map2d[0] = ft_strdup("1111111111111111111111111"); //fill the map
	map->map2d[1] = ft_strdup("1000000000000000000100001");
	map->map2d[2] = ft_strdup("1001000000000P00000000001");
	map->map2d[3] = ft_strdup("1001000000000000001000001");
	map->map2d[4] = ft_strdup("1001000000000000001000001");
	map->map2d[5] = ft_strdup("1001000000100000001000001");
	map->map2d[6] = ft_strdup("1001000000000000001000001");
	map->map2d[7] = ft_strdup("1001000000001000001000001");
	map->map2d[8] = ft_strdup("1111111111111111111111111");
	map->map2d[9] = NULL;
	map->height = 9;
	map->width = 25;
	map->start_x = 2;
	map->start_y = 13;
	return (map);
}

void	init_textures(t_cub *cub)
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;

	no = mlx_load_png("./texture/eagle.png");
	so = mlx_load_png("./texture/redbrick.png");
	ea = mlx_load_png("./texture/bluestone.png");
	we = mlx_load_png("./texture/purplestone.png");
	cub->tex->no = mlx_texture_to_image(cub->mlx, no);
	cub->tex->so = mlx_texture_to_image(cub->mlx, so);
	cub->tex->ea = mlx_texture_to_image(cub->mlx, ea);
	cub->tex->we = mlx_texture_to_image(cub->mlx, we);
	mlx_delete_texture(no);
	mlx_delete_texture(so);
	mlx_delete_texture(ea);
	mlx_delete_texture(we);
	cub->tex->ceil = 0x3288bdff;
	cub->tex->floor = 0x5e4fa2ff;
}

void	init_player(t_cub *cub)
{
	cub->ply->ply_x = cub->map->start_x + 0.5;
	cub->ply->ply_y = cub->map->start_y + 0.5;
	cub->ply->dir_x = -1;
	cub->ply->dir_y = 0;
	cub->ply->plane_x = 0;
	cub->ply->plane_y = 0.66;
	cub->ply->speed_m = 0.8;
	cub->ply->speed_r = 0.1;
}

t_cub	*init_cub(char *file)
{
	static t_cub	cub;

	cub.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!cub.mlx)
		perror("Initialization failed");
	cub.map = init_map();
	cub.tex = ft_calloc(1, sizeof(t_texture));
	cub.ray = ft_calloc(1, sizeof(t_ray));
	cub.ply = ft_calloc(1, sizeof(t_player));
	init_textures(&cub);
	init_player(&cub);

	(void) file;
	return (&cub);
}

void	free_cub(t_cub *cub)
{
	free_arr(cub->map->map2d);
	free(cub->map);
	free(cub->ray);
	free(cub->ply);
	free(cub->tex);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_cub(argv[argc - 1]);
	mlx_loop_hook(cub->mlx, &game_loop, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	free_cub(cub);
	return (EXIT_SUCCESS);
}