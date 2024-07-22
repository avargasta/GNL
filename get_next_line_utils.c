/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvargas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:48:41 by anvargas          #+#    #+#             */
/*   Updated: 2024/07/22 22:11:24 by anvargas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr_i_strl(char option, const char *s, int c)
{
	int		i;

	i = 0;
	if (option == 'c')
	{
		while (s[i] != '\0' && s[i] != (char)c)
			i++;
		if (s[i] == (char)c)
			return (i);
		return (-1);
	}
	if (option == 'l')
	{
		if (!s)
			return (0);
		while (s[i] != '\0')
		{
			if (s[i] == '\n')
				return (i + 1);
			i += 1;
		}
		return (i);
	}
	return (0);
}

t_dn_list	*ft_node(t_dn_list **lst, t_dn_list *new, int n_rd)
{
	t_dn_list	*temp;

	if (n_rd < 0)
	{
		free(new->content);
		free(new);
		return (NULL);
	}
	new->content[n_rd] = '\0';
	new->n_read = n_rd;
	new->nl_i = ft_strchr_i_strl('c', new->content, '\n');
	if (!*lst)
	{
		*lst = new;
		return (new);
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_l;
	int		s2_l;
	char	*str;
	int		i;

	s1_l = ft_strchr_i_strl('l', s1, '\0');
	s2_l = ft_strchr_i_strl('l', s2, '\0');
	str = (char *)malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < s1_l)
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	while (i < (s1_l + s2_l))
	{
		str[i] = s2[i - s1_l];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_lstclear(t_dn_list **lst, void (*del)(void *))
{
	t_dn_list	*current;
	t_dn_list	*next;

	if (!lst || !del || !(*lst))
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		(del)(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
	free(lst);
}

char	*gnl_aux(char opt, char *rst, int index, int rst_l)
{
	int		i;
	char	*new;

	i = 0;
	if (opt == 'r')
	{
		new = malloc(sizeof(char) * (rst_l - index));
		if (!new)
			return (NULL);
		while (rst[index + 1 + i] != '\0')
		{
			new[i] = rst[index + 1 + i];
			i++;
		}
		free(rst);
	}
	else
	{
		new = malloc(sizeof(char) * (index + 2));
		while (i <= index)
		{
			new[i] = rst[i];
			i++;
		}
	}
	new[i] = '\0';
	return (new);
}
