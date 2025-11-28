/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:33:47 by gozon             #+#    #+#             */
/*   Updated: 2024/05/27 08:39:38 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(char **tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

unsigned int	ft_count_words(char const *s, char c)
{
	int	count;
	int	in_word;
	int	i;

	in_word = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c && in_word)
		{
			in_word = 0;
		}
		i++;
	}
	return (count);
}

size_t	ft_wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	unsigned int	i;
	unsigned int	k;

	res = ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (k < ft_count_words(s, c))
	{
		while (s[i] == c)
			i++;
		res[k] = ft_substr(s, i, ft_wordlen(&s[i], c));
		if (res[k] == NULL)
		{
			ft_freetab(res, ft_count_words(s, c) + 1);
			return (NULL);
		}
		i += ft_wordlen(&s[i], c);
		k++;
	}
	res[k] = NULL;
	return (res);
}
