/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvargas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:48:41 by anvargas          #+#    #+#             */
/*   Updated: 2024/07/21 12:35:16 by anvargas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr_i_strlen(char option, const char *s, int c)
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
			i += 1;
		return (i);
	}
	return (0);
}

void	ft_lstadd_back(t_dn_list **lst, t_dn_list *new)
{
	t_dn_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_l;
	int		s2_l;
	char	*str;
	int		i;

	s1_l = ft_strchr_i_strlen('l', s1, '\0');
	s2_l = ft_strchr_i_strlen('l', s2, '\0');
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

char	*get_next_line_aux(char option, char *rest, int index, int rest_len)
{
	int		i;
	char	*new;

	i = 0;
	if (option == 'r')
	{
		new = malloc(sizeof(char) * (rest_len - index));
		while (rest[index + 1 + i] != '\0')
		{
			new[i] = rest[index + 1 + i];
			i++;
		}
		free(rest);
	}
	else
	{
		new = malloc(sizeof(char) * (index + 2));
		while (i <= index)
		{
			new[i] = rest[i];
			i++;
		}
	}
	new[i] = '\0';
	return (new);
}
