/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:07:59 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/02 19:40:55 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(void)
{
	t_map	map_data;
	int			fd;
	char		*file;

	file = "test_map.txt";
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCould not open file '%s'\n", file);
		return (0);
	}
	int valid = parse_map(fd, file, &map_data);
	if (!valid)
		printf("Error: Invalid\n");
	close(fd);
	return (0);
}