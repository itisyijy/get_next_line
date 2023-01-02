/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongyle <jeongyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:54:59 by jeongyle          #+#    #+#             */
/*   Updated: 2023/01/02 19:23:20 by jeongyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list {
	int				fd;
	char			*str;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(int fd);
t_list	*ft_findlst(t_list **lst, int fd);
void	ft_delnode(t_list **lst, t_list *node);
char	*get_next_line(int fd);

int		ft_findlen(char *str, int nl, int end);
int		ft_strnode(t_list *node, char *buff, int byte);
char	*ft_substr(char *str, int start, int len);
char	*ft_newline(t_list *node);

#endif