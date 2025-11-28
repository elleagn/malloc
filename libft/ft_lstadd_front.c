/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:28:14 by gozon             #+#    #+#             */
/*   Updated: 2024/05/27 09:39:06 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*
int	main(void)
{
	t_list	*lst;
	t_list	*new;

	lst = ft_lstnew("bwlbcdb");
	new = ft_lstnew("hbdccb");
	ft_lstadd_front(&lst, new);
	ft_putendl_fd(lst->content, 1);
	ft_putendl_fd(lst->next->content, 1);
	return (0);
}
*/
