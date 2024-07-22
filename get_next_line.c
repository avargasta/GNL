/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvargas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:54:47 by anvargas          #+#    #+#             */
/*   Updated: 2024/07/22 22:07:53 by anvargas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_dn_list	**get_line_list(int fd, t_dn_list **line_list)
{
	t_dn_list	*new_node;
	int			n_read;

	n_read = BUFFER_SIZE;
	while (n_read == BUFFER_SIZE)
	{
		new_node = malloc(sizeof(t_dn_list));
		if (!new_node)
			break ;
		new_node->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!new_node->content)
		{
			free(new_node);
			break ;
		}
		n_read = read(fd, new_node->content, BUFFER_SIZE);
		new_node = ft_node(line_list, new_node, n_read);
		if (!new_node || new_node->nl_i != -1)
			break ;
	}
	return (line_list);
}

char	*get_the_rest(t_dn_list *last)
{
	char	*rest;
	int		i;

	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	if (last->nl_i == -1)
	{
		rest = malloc(sizeof(char));
		rest[0] = '\0';
		return (rest);
	}
	rest = malloc(sizeof(char) * (last->n_read - last->nl_i));
	if (!rest)
		return (NULL);
	i = 0;
	while (i < last->n_read - last->nl_i)
	{
		((unsigned char *)rest)[i] = ((unsigned char *)last->content)[i
			+ ft_strchr_i_strl('l', last->content, '\0') + 1];
		i++;
	}
	return (rest);
}

char	*get_the_line(t_dn_list *line_to_list, char *rest)
{
	char	*line;

	if (!line_to_list)
		return (NULL);
	if (line_to_list->content[0] == '\0' && rest[0] == '\0')
		return (NULL);
	line = rest;
	while (line_to_list->next)
	{
		line = ft_strjoin(line, line_to_list->content);
		if (!line)
			return (NULL);
		line_to_list = line_to_list->next;
	}
	if (line_to_list->nl_i == -1 && line_to_list->n_read == BUFFER_SIZE)
	{
		free(line);
		return (NULL);
	}
	line = ft_strjoin(line, line_to_list->content);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*rest;
	int				index;
	int				rest_len;
	t_dn_list		**line_to_list;
	char			*line;

	if (rest && ft_strchr_i_strl('c', rest, '\n') != -1)
	{
		index = ft_strchr_i_strl('c', rest, '\n');
		rest_len = ft_strchr_i_strl('l', rest, '\0');
		line = gnl_aux('l', rest, index, rest_len);
		rest = gnl_aux('r', rest, index, rest_len);
		return (line);
	}
	line_to_list = (t_dn_list **)malloc(sizeof(t_dn_list *));
	if (!line_to_list)
		return (NULL);
	*line_to_list = NULL;
	line_to_list = get_line_list(fd, line_to_list);
	line = get_the_line(*line_to_list, rest);
	rest = get_the_rest(*line_to_list);
	ft_lstclear(line_to_list, free);
	if (!rest)
		return (free(line), NULL);
	return (line);
}
