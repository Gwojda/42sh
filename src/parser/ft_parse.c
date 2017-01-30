/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:14:58 by jhalford          #+#    #+#             */
/*   Updated: 2017/01/30 17:14:19 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	g_parser[] =
{
	{TK_NEWLINE, &parse_newline},
	{TK_SEMI, &parse_separator},
	{TK_AND_IF | TK_OR_IF, &parse_separator},
	{TK_AMP, &parse_separator},
	{TK_PIPE, &parse_separator},
	{TK_LESS, &parse_less},
	{TK_GREAT, &parse_great},
	{TK_DLESS, &parse_dless},
	{TK_DGREAT, &parse_dgreat},
	{TK_LESSAND, &parse_lessand},
	{TK_GREATAND, &parse_greatand},
	{TK_SUBSHELL, &parse_subshell},
	{TK_WHILE, &parse_while},
	{TK_DO, &parse_do},
	{TK_DONE, &parse_done},
	{TK_LIST, &parse_list},
	{TK_WORD, &parse_word},
	{0, 0},
};

int		ft_parse(t_list **list_ast, t_btree **ast, t_list **start)
{
	t_list		*lst;
	t_astnode	item;
	int			i;

	i = 0;
	if (!*start)
		return (0);
	if (!*ast)
	{
		*ast = btree_create_node(&item, sizeof(item));
		((t_astnode *)(*ast)->item)->data.sstr = NULL;
	}
	if (!*list_ast)
		*list_ast = ft_lstnew(ast, sizeof(t_btree *));
	while (g_parser[i].type)
	{
		if ((lst = ft_lst_find(*start, &g_parser[i].type, &token_cmp_type)))
		{
			if (g_parser[i].f)
				(*g_parser[i].f)(list_ast, ast, start, &lst);
			return (0);
		}
		i++;
	}
	return (0);
}
