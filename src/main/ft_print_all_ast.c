/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_all_ast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 19:23:49 by ariard            #+#    #+#             */
/*   Updated: 2017/01/31 22:52:06 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_all_ast(t_list *lst_ast)
{
	t_list	*tmp;
	t_btree	**ast;

	tmp = lst_ast;
	while (tmp)
	{
		if (tmp->content)
		{
			ast = tmp->content;
			btree_print(STDBUG, *ast, &ft_putast);
		}
		tmp = tmp->next;
	}
}
