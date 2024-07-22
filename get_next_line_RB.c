/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvargas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:54:47 by anvargas          #+#    #+#             */
/*   Updated: 2024/07/21 12:36:15 by anvargas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_dn_list	**get_line_list(int fd, t_dn_list **line_list)
{
	t_dn_list	*new_node;
	int			n_read;

	//printf("\n\n\n🔴 Estoy en get_line_list\n");
	n_read = BUFFER_SIZE;
	while (n_read == BUFFER_SIZE)
	{
		new_node = malloc(sizeof(t_dn_list));
		new_node->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!new_node || !new_node->content)
			break ;
		n_read = read(fd, new_node->content, BUFFER_SIZE);
		if (n_read < 0)
		{
			free(new_node->content);
			free(new_node);
			break ;
		}
		new_node->content[n_read] = '\0';
		new_node->n_read = n_read;
		new_node->nl_i = ft_strchr_i_strlen('c', new_node->content, '\n');
		ft_lstadd_back(line_list, new_node);
		if (new_node->nl_i != -1)
			break ;
	}
	return (line_list);
}

char	*get_the_rest(t_dn_list *last)
{
	char	*rest;
	int		i;
	int		j;

	//printf("\n\n\n🟡 Estoy en get_the_rest\n");
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	if (last->nl_i == -1)
		return (NULL);
	rest = malloc(sizeof(char) * (last->n_read - last->nl_i));
	if (!rest)
		return (NULL);
	i = 0;
	while (last->content[i] != '\n')
		i++;
	j = 0;
	while (j < last->n_read - last->nl_i)
	{
		((unsigned char *)rest)[j] = ((unsigned char *)last->content)[j + i
			+ 1];
		j++;
	}
	//printf("El output de get_the _rest es: %s\n", rest);
	return (rest);
}

char	*get_the_line(t_dn_list *line_to_list, char *rest)
{
	char	*line;

	//printf("\n\n\n🟠 Estoy en get_the_line\n");
	if (line_to_list->content[0] == '\0' && !rest)
		return (NULL);
	line = rest;
	//printf("La línea es %s\n", line);
	while (line_to_list->next)
	{
		line = ft_strjoin(line, line_to_list->content);
		if (!line)
			return (NULL);
		line_to_list = line_to_list->next;
		//printf("La línea es %s\n", line);
	}
	if (line_to_list->nl_i == -1 && line_to_list->n_read == BUFFER_SIZE)
	{
		free(line);
		return (NULL);
	}
	line = ft_strjoin(line, line_to_list->content);
	//printf("El output de get_the_line es: %s\n", line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*rest;
	int				index;
	int				rest_len;
	t_dn_list		**line_to_list;
	char			*line;

	if (rest != NULL && ft_strchr_i_strlen('c', rest, '\n') != -1)
	{
		//printf("🌟🌟🌟El rest original es: %s\n", rest);
		index = ft_strchr_i_strlen('c', rest, '\n');
		rest_len = ft_strchr_i_strlen('l', rest, '\0');
		line = get_next_line_aux('l', rest, index, rest_len);
		rest = get_next_line_aux('r', rest, index, rest_len);
		//printf("🌟🌟🌟El output de get_the_rest es: %s\n", rest);
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
	return (line);
}