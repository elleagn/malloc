/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:08:52 by gozon             #+#    #+#             */
/*   Updated: 2024/09/05 09:24:43 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			read_size;
	int			eol;

	eol = 0;
	line = ft_init_line(buf, fd, &read_size);
	if (!line)
		return (NULL);
	while (!eol)
	{
		line = ft_strjoin_line(&line, buf, &eol, read_size);
		if (!line)
			return (NULL);
		if (!eol)
		{
			read_size = read(fd, buf, BUFFER_SIZE);
			if (read_size == -1)
				return (free(line), NULL);
			if (read_size == 0)
				eol = 1;
		}
	}
	ft_trimbuf(buf, read_size);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("get_next_line.h", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
*/
