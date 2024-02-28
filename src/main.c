/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 12:48:15 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/02/28 12:13:54 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>



void	game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_delete_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT / 2);
	cast_ray(cub);
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
	map->start_x = 14;
	map->start_y = 3;
	return (map);
}

t_cub	*init_cub(char *file)
{
	static t_cub	cub;

	cub.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!cub.mlx)
		perror("Initialization failed");
	cub.map = init_map();
	cub.ray = ft_calloc(1, sizeof(t_ray));
	cub.ply = ft_calloc(1, sizeof(t_player));
	// cub.ply->p_x = cub.map->start_x * TILE + TILE / 2;
	// cub.ply->p_y = cub.map->start_y * TILE + TILE / 2;
	// cub.ply->fov = 60 / 180 * 3.1415926535;

	(void) file;
	return (&cub);
}

void	free_cub(t_cub *cub)
{
	free_arr(cub->map->map2d);
	free(cub->map);
	free(cub->ray);
	free(cub->ply);
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