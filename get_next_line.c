/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongyle <jeongyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:55:03 by jeongyle          #+#    #+#             */
/*   Updated: 2022/12/31 19:10:46 by jeongyle         ###   ########.fr       */
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

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
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
		if (ft_strjoin(node, buff, byte) < 0)
			break ;
	}
	if (byte <= 0 && !ft_findlst(&lst, fd)->str)
	{
		ft_lstclear(&lst);
		return (NULL);
	}
	return (ft_newline(node));
}
