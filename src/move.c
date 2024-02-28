/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 12:12:11 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/02/28 15:09:56 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
	controle_angle(data);
	controle_player(data);
	draw_ceil_floor(data);
	draw_map(data, 0);
	draw_view_angle(data);
	draw_player(data);
*/

int	check_wall(char **map, t_player *ply)
{
	if (map[(int)ply->ply_x][(int)])
}

void	move(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		cub->ply->ply_x += 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		cub->cam->x_offset += 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		cub->cam->y_offset -= 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		cub->cam->y_offset += 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		init_camera(cub);
		cub->cam->iso = 0;
	}
}