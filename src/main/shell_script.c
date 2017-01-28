/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 23:06:34 by ariard            #+#    #+#             */
/*   Updated: 2017/01/28 23:38:10 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell_script()
{
	t_list	*token;
	t_btree	*ast;
	t_btree **ast2;
	t_list	*list_ast;
	t_list	*tmp2;

	token = NULL;
	ast = NULL;
	list_ast = NULL;
	if (ft_tokenize(&token, data_singleton()->script.buffer , DEFAULT))
		return (1);
	if (!token)
		return (0);
	if (ft_post_tokenize(&token, data_singleton()->script.buffer))
		return (1);
	DG("after post_tokenize");
	token_print(token);
	if (ft_parse(&list_ast, &ast, &token))
		return (1);
	tmp2 = list_ast;
	while (tmp2)
	{	
		ast2 = tmp2->content;
		btree_print(STDBUG, *ast2, &ft_putast);
		tmp2 = tmp2->next;
	}
	while (list_ast)
	{
		if (ft_exec((t_btree **)list_ast->content))
			return (1);
		list_ast = list_ast->next;
	}
	return (0);
}
