/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongyle <jeongyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:55:03 by jeongyle          #+#    #+#             */
/*   Updated: 2023/01/03 16:30:31 by jeongyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(int fd)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->fd = fd;
	node->str = NULL;
	node->next = NULL;
	return (node);
}

t_list	*ft_findlst(t_list **lst, int fd)
{
	t_list	*find;
	t_list	*ini;

	ini = *lst;
	if (!*lst)
	{
		*lst = ft_lstnew(fd);
		if (!*lst)
			return (0);
		return (*lst);
	}
	while ((*lst)->next && (*lst)->fd != fd)
		*lst = (*lst)->next;
	if ((*lst)->fd == fd)
		find = *lst;
	else
	{
		find = ft_lstnew(fd);
		(*lst)->next = find;
	}
	*lst = ini;
	return (find);
}

void	ft_delnode(t_list **lst, t_list *node)
{
	t_list	*prev;
	t_list	*item;

	prev = *lst;
	while (prev)
	{
		if (prev->fd == node->fd)
			break ;
		prev = prev->next;
	}
	item = prev->next;
	if (prev == *lst)
	{
		*lst = prev->next;
		free(prev);
	}
	else if (item->next == NULL)
		prev->next = NULL;
	else
		prev->next = item->next;
	free(item);
}

char	*get_next_line(int fd)
{
	int				byte;
	char			buff[BUFFER_SIZE + 1];
	t_list			*node;
	static t_list	*lst = NULL;

	byte = 1;
	node = ft_findlst(&lst, fd);
	buff[BUFFER_SIZE] = '\0';
	while (byte > 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte <= 0)
			break ;
		if (ft_strnode(node, buff, byte) >= 0)
			break ;
	}
	if (node->str && byte >= 0)
		return (ft_newline(node));
	free(node->str);
	ft_delnode(&lst, node);
	return (NULL);
}
