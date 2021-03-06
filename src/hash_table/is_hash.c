/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 11:08:40 by gwojda            #+#    #+#             */
/*   Updated: 2017/03/29 15:25:58 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*h_free_one(t_list **head, t_list *list, t_list *ref)
{
	if (!((*head)->next))
		ft_lstdelone(head, &ft_hash_free);
	else
	{
		ref->next = list->next;
		ft_lstdelone(&list, &ft_hash_free);
	}
	return (NULL);
}

char		*ft_is_hash(char *cmd)
{
	t_list	*list;
	t_list	*ref;
	int		id;

	id = ft_hash_str(cmd);
	list = g_hash[id];
	ref = list;
	while (list)
	{
		if (!ft_strcmp(((t_hash *)list->content)->key, cmd))
		{
			if (access(((t_hash *)list->content)->path,
							X_OK | F_OK) < 0)
				return (h_free_one(&g_hash[id], list, ref));
			return (ft_strdup(((t_hash *)list->content)->path));
		}
		ref = list;
		list = list->next;
	}
	return (NULL);
}
