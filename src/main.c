/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 12:48:15 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/07 13:17:54 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	minimap(t_cub *cub)
{
	int	i = -1;
	int	j;
	while (++i < 100)
	{
		j  = -1;
		while (++j < 100)
		{
			mlx_put_pixel(cub->img, 5 + j, 5 + i, 0x00000000);
		}
	}
}

void	game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_delete_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cast_ray(cub);
	move(cub);
	minimap(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		return (printf("Error\nincorrect arguments.\n"), 1);
	cub = init_cub(argv[argc - 1]);
	mlx_loop_hook(cub->mlx, &game_loop, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	free_cub(cub, 0, NULL);
	return (EXIT_SUCCESS);
}
