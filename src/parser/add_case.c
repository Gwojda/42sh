#include "parser.h"

int		iscase(t_btree **ast, t_list **lst)
{
	t_astnode	*node;
	t_token		*token;

	node = NULL;
	token = (*lst)->content;
	if (*ast)
	{
		node = (*ast)->item;
		if ((node->type == TK_CASE || node->type == TK_PAREN_OPEN)
			&& token->type == TK_WORD && node->pattern == 0)
			return (1);
		if ((node->type == TK_PAREN_OPEN || node->type == TK_CASE)
			&& node->nest == 0 && token->type == TK_PAREN_OPEN)
			return (3);
		if (node->type == TK_CASE || node->type == TK_PAREN_OPEN)
			return (2);
	}
	return (0);
}

int		add_case_cmd(t_btree **ast, t_list **lst)
{
	t_astnode	*node;
	t_token		*token;

	token = (*lst)->content;
	node = (*ast)->item;
	if (token->type == TK_CASE && (node->type == TK_PAREN_OPEN
		|| node->type == TK_CASE))
		node->nest++;
	if (token->type == TK_ESAC && (node->type == TK_PAREN_OPEN
		|| node->type == TK_CASE) && node->nest > 0)
		return ((node->nest--));
	else if (token->type == TK_DSEMI && node->type == TK_PAREN_OPEN 
		&& node->nest == 0)
		return ((node->full = 1));
	else if (token->type == TK_ESAC)
		return (0);
	return (add_cmd(&(*ast)->right, lst));
}	

int		add_case_sep(t_btree **ast, t_list **lst)
{
	return (add_sep(&(*ast)->right, lst));
}

int		add_pattern(t_btree **ast, t_list **lst)
{
	t_astnode	*node;
	t_token		*token;
	
	token = (*lst)->content;
	node = (*ast)->item;
	node->data.redir.word.word = ft_strdup(token->data);
	node->pattern = 1;
	return (0);
}
