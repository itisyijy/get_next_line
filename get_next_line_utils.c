/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongyle <jeongyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:55:01 by jeongyle          #+#    #+#             */
/*   Updated: 2022/12/31 19:15:56 by jeongyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_findnewline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	ft_strjoin(t_list *node, char *buff, int byte)
{
	int		i;
	int		j;
	int		len;
	char	*line;

	len = 0;
	if (!(node->str))
		node->str = buff;
	else
		while ((node->str)[len])
			len++;
	line = (char *)malloc(len + byte + 1);
	if (!line)
		return (0);
	i = -1;
	while (++i < len)
		line[i] = (node->str)[i];
	j = -1;
	while (++j < byte)
		line[i + j] = buff[j];
	line[i + j] = '\0';
	node->str = line;
	if (ft_findnewline(node->str))
		return (-1);
	return (len + byte);
}

char	*ft_strdup(char *str, int len)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_newline(t_list *node)
{
	int		i;
	int		j;
	char	*before;
	char	*after;

	if (!node->str)
		return (NULL);
	i = 0;
	while ((node->str)[i] != '\n' && (node->str)[i] != '\0')
		i++;
	if ((node->str)[i] == '\n')
		i++;
	before = ft_strdup((node->str), i);
	if (!before)
		return (0);
	j = 0;
	while ((node->str)[i + j] != '\0')
		j++;
	after = ft_strdup(&((node->str)[i]), j);
	if (!after)
		return (0);
	node->str = after;
	return (before);
}
