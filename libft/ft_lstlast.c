/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:17:11 by gozon             #+#    #+#             */
/*   Updated: 2024/05/27 11:26:30 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
	ft_lstadd_front(&lst, new);
	ft_putstr_fd(ft_lstlast(lst)->content, 1);
	return (0);
}
*/
