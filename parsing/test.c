/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:07:59 by jcaro             #+#    #+#             */
/*   Updated: 2024/02/24 18:34:13 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(void)
{
	t_textures	textures;

	int valid = read_textures("test_textures.txt", &textures);
	if (!valid)
		printf("Error\n");
	else
	{
		printf("%s\n", textures.north);
		printf("%s\n", textures.south);
		printf("%s\n", textures.west);
		printf("%s\n", textures.east);
		printf("%s\n", textures.floor);
		printf("%s\n", textures.ceiling);
		free_texture(&textures);
	}
	return (0);
}