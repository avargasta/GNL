/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvargas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:31:01 by anvargas          #+#    #+#             */
/*   Updated: 2024/07/20 12:51:36 by anvargas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int fd;
	int i;
	char *line;

	i = 1;
	fd = open("prueba.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	printf("\n\n\n\n➿🌈➿🌈➿🌈➿🌈 Estamos en la iteración número 0 ➿🌈➿🌈➿🌈➿🌈\n");
	line = get_next_line(fd);
	printf("🖤🖤🖤🖤🖤🖤 EL OUTPUT FINAL DE LA ITERACIÓN ES:\n%s\n🖤🖤🖤🖤🖤🖤,", line);
	while (line)
	{
		// printf("\n\n\n🔵 El resultado de la iteración %i es %s", i, line);
		printf("\n\n\n\n➿🌈➿🌈➿🌈➿🌈 Estamos en la iteración número %d ➿🌈➿🌈➿🌈➿🌈\n",
			i);
		free(line);
		line = get_next_line(fd);
		i++;
		printf("🖤🖤🖤🖤🖤🖤 EL OUTPUT FINAL DE LA ITERACIÓN ES:\n%s\n🖤🖤🖤🖤🖤🖤,", line);
	}
	close(fd);
	return (0);
}