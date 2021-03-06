/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_toolz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 11:37:47 by gwojda            #+#    #+#             */
/*   Updated: 2017/03/21 18:12:27 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_history_list(t_list_history *head)
{
	t_list_history	*prev;

	if (!SH_IS_INTERACTIVE(data_singleton()->opts))
		return ;
	if (head && head->next)
		free(head->next);
	while (head)
	{
		ft_strdel(&head->str);
		prev = head;
		head = head->prev;
		free(prev);
	}
}

t_list_history	*ft_create_history_list(char *str)
{
	t_list_history	*list;

	list = (t_list_history *)ft_malloc(sizeof(t_list_history));
	if (!list)
		return (NULL);
	if (!str)
		list->str = NULL;
	else
		list->str = ft_strdup(str);
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

void			ft_push_back_history(t_list_history **head, t_list_history *new)
{
	++(data_singleton()->line.list_size);
	if (!*head)
	{
		*head = new;
		(*head)->prev = ft_create_history_list(NULL);
		(*head)->prev->next = (*head);
		(*head)->next = ft_create_history_list(NULL);
		(*head)->next->prev = (*head);
		(*head) = (*head)->next;
		(data_singleton())->line.list_end = new;
		return ;
	}
	while ((*head)->next)
		(*head) = (*head)->next;
	new->prev = (*head)->prev;
	(*head)->prev->next = new;
	new->next = (*head);
	(*head)->prev = new;
}

size_t			ft_hist_len(void)
{
	size_t			len;
	t_list_history	*list;

	len = 0;
	list = data_singleton()->line.list_beg;
	while (list)
	{
		++len;
		list = list->prev;
	}
	return (len);
}
