/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:07:23 by gozon             #+#    #+#             */
/*   Updated: 2024/09/05 09:26:29 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*ft_strjoin_line(char **line, char *buf, int *eol, int read_size);
void	ft_trimbuf(char *buf, int read_size);
char	*ft_init_line(char *buf, int fd, int *read_size);

#endif
