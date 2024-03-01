/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessie <jessie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:12:11 by jiajchen          #+#    #+#             */
/*   Updated: 2024/02/29 17:56:09 by jessie           ###   ########.fr       */
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

int	check_wall(t_cub *cub, char dir)
{
	char		**map;
	t_player	*ply;

	map = cub->map->map2d;
	ply = cub->ply;
	if (dir == 'W' && map[(int)ply->ply_x + ply->dir_x * ply->speed][(int)ply->ply_y] == '1')
		return (0);
}

void	move(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		move_up;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		cub->ply->ply_x -= cub->ply->plane_x * cub->ply->speed;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		cub->ply->ply_y += cub->ply->plane_y * cub->ply->speed;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		cub->ply->ply_y += cub->ply->plane_y * cub->ply->speed;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		
}