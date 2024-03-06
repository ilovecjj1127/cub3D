/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 12:48:15 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/04 18:10:26 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_cub(argv[argc - 1]);
	mlx_loop_hook(cub->mlx, &game_loop, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	free_cub(cub, 0, NULL);
	return (EXIT_SUCCESS);
}