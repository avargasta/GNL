/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvargas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:54:47 by anvargas          #+#    #+#             */
/*   Updated: 2024/08/01 19:46:10 by anvargas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_dn_list	**get_line_list(int fd, t_dn_list **line_list)
{
	t_dn_list	*new_node;
	int			n_read;

	printf("🔴 Estoy en get_line_list\n");
	*line_list = NULL;
	n_read = BUFFER_SIZE;
	while (n_read == BUFFER_SIZE)
	{
		new_node = malloc(sizeof(t_dn_list));
		if (!new_node)
			break ;
		new_node->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		new_node->next = NULL;
		if (!new_node->content)
		{
			free(new_node);
			break ;
		}
		n_read = read(fd, new_node->content, BUFFER_SIZE);
		new_node = nodeinf(line_list, new_node, n_read);
		if (!new_node || new_node->nl_i != -1)
			break ;
	}
	return (line_list);
}

char	*get_the_rest(t_dn_list *last)
{
	char	*rest;
	int		i;
	
	printf("🟡 Estoy en get_the_rest\n");
	while (last->next)
		last = last->next;
	if (last->nl_i == -1)
	{
		rest = malloc(sizeof(char));
		if (!rest)
			return (NULL);
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
			+ strchri_strl('l', last->content, '\0')];
		i++;
	}
	printf("El output de get_the _rest es:\n--%s--\n", rest);
	return (rest);
}

char	*get_the_line(t_dn_list *line_to_list, char *rest)
{
	char	*line;

	if (line_to_list->content[0] == '\0' && rest && rest[0] == '\0')
		return (free(rest), NULL);
	line = rest;
	printf("La línea es:\n %s\n", line);
	while (line_to_list->next)
	{
		line = ft_strjoin(line, line_to_list->content);
		if (!line)
			return (NULL);
		line_to_list = line_to_list->next;
		printf("La línea es:\n %s\n", line);
	}
	if (line_to_list->nl_i == -1 && line_to_list->n_read == BUFFER_SIZE)
		return (free(line), NULL);
	line = ft_strjoin(line, line_to_list->content);
	if (!line)
		return (NULL);
	printf("El output de get_the_line es:\n %s\n", line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*rest;
	t_dn_list		**line_to_list;
	char			*line;

	if (rest && strchri_strl('c', rest, '\n') != -1)
	{
		printf("🌟🌟🌟El rest original es:\n %s\n", rest);
		line = gnl_aux('l', rest);
		rest = gnl_aux('r', rest);
		printf("🌟🌟🌟El output de get_the_rest es:\n %s\n", rest);
	}
	else
	{
		line_to_list = (t_dn_list **)malloc(sizeof(t_dn_list *));
		if (!line_to_list)
			return (NULL);
		line_to_list = get_line_list(fd, line_to_list);
		if (!*line_to_list)
			return (free(rest), ft_lstclear(line_to_list, free), NULL);
		line = get_the_line(*line_to_list, rest);
		rest = get_the_rest(*line_to_list);
		ft_lstclear(line_to_list, free);
	}
	if (!rest || !line)
		return (free(line), free(rest), NULL);
	return (line);
}


