/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 00:02:58 by ariard            #+#    #+#             */
/*   Updated: 2017/03/08 11:53:26 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			*redir_copy(void *data)
{
	t_redir		*old;
	t_redir		*new;

	if (!data)
		return (NULL);
	old = data;
	new = (t_redir *)ft_memalloc(sizeof(t_redir));
	new->type = old->type;
	new->n = old->n;
	new->word = ft_strdup(old->word);
	return (new);
}
