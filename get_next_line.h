/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvargas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:26:13 by anvargas          #+#    #+#             */
/*   Updated: 2024/07/22 21:10:07 by anvargas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h> // OPEN
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> // CLOSE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_datanode_list
{
	char					*content;
	struct s_datanode_list	*next;
	int						n_read;
	int						nl_i;
}							t_dn_list;

int							ft_strchr_index(const char *s, int c);
t_dn_list					*ft_node(t_dn_list **lst, t_dn_list *new, int n_rd);
int							ft_strchr_i_strl(char option, const char *s, int c);
char						*ft_strjoin(char *s1, char *s2);
void						ft_lstclear(t_dn_list **lst, void (*del)(void *));
t_dn_list					**get_line_list(int fd, t_dn_list **line_list);
char						*get_the_rest(t_dn_list *last);
char						*get_the_line(t_dn_list *line_to_list, char *rest);
char						*get_next_line(int fd);
char						*gnl_aux(char opt, char *rst, int index, int rst_l);

#endif // GET_NEXT_LINE_H
