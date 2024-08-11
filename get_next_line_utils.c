/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvargas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:48:41 by anvargas          #+#    #+#             */
/*   Updated: 2024/08/10 12:17:40 by anvargas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	strchri_strl(char option, char l_r, const char *s)
{
	int		i;

	i = 0;
	if (option == 'c')
	{
		while (s[i] != '\0' && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			return (i);
		return (-1);
	}
	if (option == 'l')
	{
		if (!s)
			return (0);
		while (s[i] != '\0')
		{
			if (s[i] == '\n' && l_r == 'l')
				return (i + 1);
			i += 1;
		}
		return (i);
	}
	return (0);
}

t_dn_list	*nodeinf(t_dn_list **lst, t_dn_list *new, int n_rd)
{
	t_dn_list	*temp;

	if (n_rd < 0)
	{
		return (free(new->content), free(new), NULL);
	}
	new->content[n_rd] = '\0';
	new->n_read = n_rd;
	new->nl_i = strchri_strl('c', 0, new->content);
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

	s1_l = strchri_strl('l', 'l', s1);
	s2_l = strchri_strl('l', 'l', s2);
	str = (char *)malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!str)
		return (free(s1), NULL);
	i = -1;
	while (++i < s1_l)
		str[i] = s1[i];
	free(s1);
	i = i - 1;
	while (++i < (s1_l + s2_l))
		str[i] = s2[i - s1_l];
	str[i] = '\0';
	return (str);
}

void	ft_lstclear(t_dn_list **lst, void (*del)(void *))
{
	t_dn_list	*current;
	t_dn_list	*next;

	if (!(*lst))
	{
		free(lst);
		return ;
	}
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

//printf("Voy a modificar el rest: %s\n", rst);
//printf("Calculo strchri_strl: %d\n", strchri_strl('l', 'r', rst));
//printf("Calculo index: %d\n", index);
char	*gnl_aux(char opt, char *rst)
{
	int		i;
	char	*new;
	int		index;

	i = -1;
	index = strchri_strl('c', 0, rst);
	if (opt == 'r')
	{
		new = malloc(sizeof(char) * (strchri_strl('l', 'r', rst) - index));
		if (!new)
			return (NULL);
		while (rst[index + 1 + ++i] != '\0')
			new[i] = rst[index + 1 + i];
		free(rst);
		new[i] = '\0';
		return (new);
	}
	new = malloc(sizeof(char) * (index + 2));
	if (!new)
		return (NULL);
	while (++i <= index)
		new[i] = rst[i];
	new[i] = '\0';
	return (new);
}
