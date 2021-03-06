/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:22:51 by ariard            #+#    #+#             */
/*   Updated: 2017/03/29 17:01:08 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** Parse POSIX grammar
*/

enum	e_parstate
{
	ERROR = 0,
	UNDEFINED,
	SUCCESS,
};

# define MATCH_STACK(x, y)		(x == y || y == ALL)

struct	s_parser
{
	t_parstate	state;
	t_list		*stack;
	t_sym		*new_sym;
	t_list		*heredoc_queue;
	int			cache;
};

struct	s_aggrematch
{
	t_sym	top;
	t_sym	under;
	t_sym	new_sym;
	int		erase_sym;
};

struct	s_prodmatch
{
	t_type	token;
	t_sym	stack;
	t_sym	new_sym;
};

struct	s_stackmatch
{
	t_sym top;
	t_sym under;
};

struct	s_errormatch
{
	t_type	token;
	char	*error;
};

int		do_parser_routine(t_list **token, t_btree **ast);
void	parser_init(t_parser *parser);
void	parser_destroy(t_parser *parser);
int		stack_init(t_parser *parser);
int		redir_init(t_type type, t_redir *redir);
int		ft_parse(t_btree **ast, t_list **token, t_parser *parser);

int		produce_sym(t_list **stack, t_sym *new_sym, t_list **lst);
int		eval_sym(t_list **stack, t_sym new_sym);
int		aggregate_sym(t_list **stack, t_sym *new_sym, t_parstate *state);

int		push_stack(t_list **stack, t_sym new_sym);
int		pop_stack(t_list **stack, t_sym erase_sym);

int		pop_heredoc(t_list **lst);

int		error_syntax(t_list **token);
int		error_eof(void);

int		ft_read_stack(t_sym *stack);
char	*read_state(t_sym current);

struct	s_treematch
{
	t_type	type;
	int		(*add)(t_btree **ast, t_list **lst);
};

int		build_tree(t_btree **ast, t_list **lst, t_parser *parser);

int		add_sep(t_btree **ast, t_list **lst);
int		add_cmd(t_btree **ast, t_list **lst);

int		add_file(t_btree **ast, t_list **lst);
int		add_loop_cmd(t_btree **ast, t_list **lst);
int		add_loop_sep(t_btree **ast, t_list **lst);
int		add_condition_cmd(t_btree **ast, t_list **lst);
int		add_condition_sep(t_btree **ast, t_list **lst);
int		add_branch(t_btree **ast, t_list **lst);
int		add_redir_word(t_btree **ast, t_list **lst);
int		add_redir_type(t_btree **ast, t_list **lst);
int		redir_init(t_type type, t_redir *redir);
int		add_case_cmd(t_btree **ast, t_list **lst);
int		add_case_sep(t_btree **ast, t_list **lst);
int		add_pattern(t_btree **ast, t_list **lst);
int		add_subshell_cmd(t_btree **ast, t_list **lst);
int		add_subshell_sep(t_btree **ast, t_list **lst);
int		add_func_cmd(t_btree **ast, t_list **lst);
int		add_one_func(t_btree **ast, t_list **lst);
int		add_pipe(t_btree **ast, t_list **lst);
int		add_null(t_btree **ast, t_list **lst);
int		add_ionumber(t_btree **ast, t_list **lst);
int		add_bang(t_btree **ast, t_list **lst);
int		add_bang_sep(t_btree **ast, t_list **lst);
int		add_if(t_btree **ast, t_list **lst);

int		isloop(t_btree **ast, t_list **lst);
int		iscase(t_btree **ast, t_list **lst);
int		iscase_pattern(t_btree **ast, t_list **lst);
int		iscase_branch(t_btree **ast, t_list **lst);
int		iscondition(t_btree **ast, t_list **lst);
int		iscondition_branch(t_btree **ast, t_list **lst);
int		issubshell(t_btree **ast, t_list **lst);
int		isfunc(t_btree **ast, t_list **lst);
int		isfunc_name(t_btree **ast, t_list **lst);
int		isdir(t_btree **ast);
int		iscondition(t_btree **ast, t_list **list);
int		isdir_sep(t_btree **ast, t_list **list);
int		isdir_word(t_btree **ast, t_list **list);
int		isnull(t_btree **ast, t_list **list);
int		isionumber(t_btree **ast, t_list **lst);
int		isbang(t_btree **ast, t_list **lst);
int		isbang_sep(t_btree **ast, t_list **lst);

int		join_ast(t_btree **ast, t_btree **new_node);
int		gen_node(t_btree **ast);
int		superflous_token(t_btree **ast, t_list **list);
void	sym_free(void *data, size_t size);
void	tree_func_free(void *data, size_t content_size);

char	*read_state(t_sym current);

struct	s_distrostree
{
	int	(*test)(t_btree **ast, t_list **lst);
	int	(*add)(t_btree **ast, t_list **lst);
};

struct	s_redir
{
	t_type	type;
	int		n;
	char	*word;
	char	*heredoc_data;
};

struct	s_cmd
{
	t_list	*redir;
	t_ld	*token;
};

union	u_astdata
{
	t_cmd	cmd;
};

struct	s_astnode
{
	int			pattern;
	int			nest;
	int			full;
	int			cache;
	t_type		type;
	t_astdata	data;
};

#endif
