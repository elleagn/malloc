/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:36:07 by gozon             #+#    #+#             */
/*   Updated: 2024/05/27 12:28:57 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		ft_lstlast(*lst)->next = new;
	}
}

/*
int	main(void)
{
	t_list	*lst;
	t_list	*new;

	lst = ft_lstnew("bwlbcdb");
	new = ft_lstnew("hbdccb");
	ft_lstadd_front(&lst, new);
	new = ft_lstnew("wvkcvk");
	ft_lstadd_back(&lst, new);
	ft_putstr_fd(ft_lstlast(lst)->content, 1);
	return (0);
}
*/
