/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregate_sym.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:39:18 by ariard            #+#    #+#             */
/*   Updated: 2017/02/24 23:16:29 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_aggrematch		g_aggrematch[] =
{
	{TK_WORD, CMD_SUFFIX, CMD_SUFFIX, 0},
	{TK_WORD, TK_PIPE, PATTERN, 0},
	{TK_WORD, TK_IN, FOR_WORDLIST, TK_IN},
	{TK_WORD, FOR_WORDLIST, FOR_WORDLIST, FOR_WORDLIST},
	{TK_SEMI, FOR_WORDLIST, SEQUENTIAL_SEP, 0},	
	{TK_DSEMI, PIPE_SEMI_SEQUENCE, PIPE_SEQUENCE, PIPE_SEMI_SEQUENCE},
	{TK_PAREN_OPEN, TK_IN, PATTERN_CASE, 0},
	{TK_PAREN_OPEN, CASE_LIST_NS, PATTERN_CASE, 0},	
	{TK_PAREN_OPEN, CMD_SUPERIOR, FUNC_NAME, CMD_SUPERIOR},
	{TK_ASSIGNEMENT_WORD, CMD_PREFIX,CMD_PREFIX, 0},
	{TK_PIPE, CMD_SUPERIOR, SIMPLE_COMMAND, CMD_SUPERIOR},
	{TK_FI, ELSE_PART, IF_CLAUSE, TK_IF},
	{TK_FI, COMPOUND_LIST, IF_CLAUSE, COMPLETE_CONDITION},
	{TK_FI, COMPLETE_CONDITION, IF_CLAUSE, COMPLETE_CONDITION},
	{TK_FI, CONDITION, IF_CLAUSE, COMPLETE_CONDITION},
	{TK_THEN, CONDITION, COMPLETE_CONDITION, CONDITION}, 
	{TK_DONE, CMD_SUPERIOR, DO_GROUP, TK_DO},
	{TK_DONE, COMPOUND_LIST, DO_GROUP, TK_DO},
//Esac ?
	{TK_ESAC, TK_IN, CASE_CLAUSE, TK_CASE},	
	{TK_ESAC, CASE_LIST_NS, CASE_CLAUSE, TK_CASE},
	{TK_RBRACE, COMPOUND_LIST, BRACE_GROUP, TK_LBRACE},
	{TK_PAREN_CLOSE, COMPOUND_LIST, SUBSHELL, TK_PAREN_OPEN},	
	{TK_PAREN_CLOSE, CMD_SUPERIOR, SUBSHELL, TK_PAREN_OPEN},
	{TK_PAREN_CLOSE, PIPE_SEMI_SEQUENCE, SUBSHELL, TK_PAREN_OPEN},

	{TK_RBRACE, COMPOUND_LIST, BRACE_CLAUSE, TK_LBRACE},	
	{TK_RBRACE, CMD_SUPERIOR, BRACE_CLAUSE, TK_LBRACE},
	{TK_RBRACE, PIPE_SEMI_SEQUENCE, BRACE_CLAUSE, TK_LBRACE},
	{TK_AND_IF, CMD_SUPERIOR, AND_OR_MINOR, CMD_SUPERIOR},
	{TK_OR_IF, CMD_SUPERIOR, AND_OR_MINOR, CMD_SUPERIOR},
//watch this
	{SEPARATOR_OP, CMD_SUPERIOR, SEPARATOR, 0},
	{SEPARATOR_OP, COMPOUND_LIST, SEPARATOR, 0},
	{SEPARATOR_OP, CASE_LIST_NS, SEPARATOR, 0},
	{SEPARATOR_OP, PIPE_SEMI_SEQUENCE, SEPARATOR, 0},
	{SEPARATOR, CMD_SUPERIOR, END_COMMAND, CMD_SUPERIOR},
	{SEPARATOR, CASE_LIST_NS, CASE_LIST_NS, CASE_LIST_NS}, 
	{SEPARATOR, COMPOUND_LIST, COMPOUND_LIST, COMPOUND_LIST},
	{SEPARATOR, PIPE_SEMI_SEQUENCE, PIPE_SEQUENCE, PIPE_SEMI_SEQUENCE},
	{LINEBREAK, SEPARATOR_OP, SEPARATOR, SEPARATOR_OP},
	{LINEBREAK, TK_SEMI, SEQUENTIAL_SEP, TK_SEMI},

//to abstract TK_ESAC
	{LINEBREAK, TK_PAREN_CLOSE, FUNC, FNAME},
//paren open
	{LINEBREAK, TK_PIPE, PIPE_SEMI_SEQUENCE, PIPE_SEQUENCE},
	{LINEBREAK, COMPLETE_COMMANDS, PROGRAM, LINEBREAK}, 
	{LINEBREAK, CMD_SUPERIOR, SEPARATOR_OP, 0},
	{LINEBREAK, PIPE_SEMI_SEQUENCE, PIPE_SEQUENCE, PIPE_SEMI_SEQUENCE},
	{LINEBREAK, COMPOUND_LIST, COMPOUND_LIST, COMPOUND_LIST},
	{LINEBREAK, CASE_LIST_NS, CASE_LIST_NS, CASE_LIST_NS},
	{LINEBREAK, COMPLETE_COMMANDS, PROGRAM, LINEBREAK},
	{NEWLINE_LIST, CMD_NAME, CMD_SUPERIOR, CMD_NAME},
	{NEWLINE_LIST,  SEQUENTIAL_SEP, SEQUENTIAL_SEP, SEQUENTIAL_SEP},
	{NEWLINE_LIST, TK_DO, TK_DO, TK_DO},
	{NEWLINE_LIST, TK_PAREN_CLOSE, TK_PAREN_CLOSE, TK_PAREN_CLOSE},
	{NEWLINE_LIST, TK_IN, TK_IN, TK_IN},
	{NEWLINE_LIST, TK_THEN, TK_THEN, TK_THEN},
	{NEWLINE_LIST, TK_IF, TK_IF, TK_IF},
	{NEWLINE_LIST, TK_ELIF, TK_ELIF, TK_ELIF},
	{NEWLINE_LIST, TK_ELSE, TK_ELSE, TK_ELSE},
	{NEWLINE_LIST, TK_WHILE, TK_WHILE, TK_WHILE},
	{NEWLINE_LIST, TK_UNTIL, TK_UNTIL, TK_UNTIL},
	{NEWLINE_LIST, CASE_LIST_NS, CASE_LIST_NS, CASE_LIST_NS},
	{NEWLINE_LIST, NEWLINE_LIST, NEWLINE_LIST, NEWLINE},
	{NEWLINE_LIST, NAME, SEQUENTIAL_SEP, 0},
	{NEWLINE_LIST, IN, SEQUENTIAL_SEP, 0},
	{NEWLINE_LIST, TERM, SEPARATOR, 0},
	{NEWLINE_LIST, COMPOUND_LIST, SEPARATOR, 0},
	{NEWLINE_LIST, CASE_LIST_NS, SEPARATOR, 0},
	{NEWLINE_LIST, COMPLETE_CONDITION, COMPLETE_CONDITION, COMPLETE_CONDITION},
	{NEWLINE_LIST, CONDITION, CONDITION, CONDITION},
	{NEWLINE_LIST, COMPLETE_COMMANDS, LINEBREAK, 0},
	{NEWLINE_LIST, LINEBREAK, PROGRAM, LINEBREAK},
	{NEWLINE_LIST, FOR_WORDLIST, SEQUENTIAL_SEP, 0},

//to check
	{IO_HERE, TK_IO_NUMBER, IO_REDIRECT, TK_IO_NUMBER},
	{IO_HERE, ALL, IO_REDIRECT, 0},	
	{FILENAME, TK_LESS, IO_FILE, TK_LESS},
	{FILENAME, TK_LESSAND, IO_FILE, TK_LESSAND},
	{FILENAME, TK_GREAT, IO_FILE, TK_GREAT},
	{FILENAME, TK_GREATAND, IO_FILE, TK_GREATAND},
	{FILENAME, TK_DGREAT, IO_FILE, TK_DGREAT},
	{FILENAME, TK_LESSGREAT, IO_FILE, TK_LESSGREAT},
	{FILENAME, TK_CLOBBER, IO_FILE, TK_CLOBBER},

//to check
	{IO_FILE, TK_IO_NUMBER, IO_REDIRECT, TK_IO_NUMBER},
	{IO_FILE, ALL, IO_REDIRECT, 0},
	{IO_REDIRECT, CMD_SUPERIOR, CMD_SUPERIOR, CMD_SUPERIOR},
	{IO_REDIRECT, COMPOUND_COMMAND, REDIRECT_LIST, REDIRECT_LIST},

//to check 
	{IO_REDIRECT, CMD_SUFFIX, CMD_SUFFIX, CMD_SUFFIX},
	{IO_REDIRECT, CMD_NAME, CMD_SUFFIX, 0},
	{IO_REDIRECT, CMD_WORD, CMD_SUFFIX, 0},
	{IO_REDIRECT, CMD_PREFIX, CMD_PREFIX, CMD_PREFIX},
	{IO_REDIRECT, LINEBREAK, CMD_PREFIX, 0},
	{IO_REDIRECT, TK_PAREN_OPEN, CMD_PREFIX, 0},
	{IO_REDIRECT, TK_LBRACE, CMD_PREFIX, 0},
	{IO_REDIRECT, COMPLETE_COMMANDS, CMD_PREFIX, 0},
	{IO_REDIRECT, TK_BANG, CMD_PREFIX, 0},
	{IO_REDIRECT, SEPARATOR_OP, CMD_PREFIX, 0},
	{IO_REDIRECT, NEWLINE_LIST, CMD_PREFIX, 0},
	{REDIRECT_LIST, COMPOUND_COMMAND, COMPOUND_COMMAND, COMPOUND_COMMAND},
	{CMD_SUFFIX, CMD_WORD, SIMPLE_COMMAND, CMD_PREFIX},
	{CMD_SUFFIX, CMD_NAME, SIMPLE_COMMAND, CMD_NAME},
	{CMD_SUFFIX, CMD_SUPERIOR, SIMPLE_COMMAND, CMD_SUPERIOR},
//to abstract
	{CMD_PREFIX, LINEBREAK, SIMPLE_COMMAND, 0},
	{CMD_PREFIX, TK_PAREN_OPEN, SIMPLE_COMMAND, 0},
	{CMD_PREFIX, TK_LBRACE, SIMPLE_COMMAND, 0},
	{CMD_PREFIX, COMPLETE_COMMANDS, SIMPLE_COMMAND, 0},
	{CMD_PREFIX, TK_BANG, SIMPLE_COMMAND, 0},
	{CMD_PREFIX, SEPARATOR_OP, SIMPLE_COMMAND, 0},
	{CMD_PREFIX, NEWLINE_LIST, SIMPLE_COMMAND, 0},

	{CMD_WORD, CMD_PREFIX, SIMPLE_COMMAND, CMD_PREFIX},
//to check	
	{CMD_NAME, LINEBREAK, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_PAREN_OPEN, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_LBRACE, CMD_SUPERIOR, 0},
	{CMD_NAME, COMPLETE_COMMANDS, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_BANG, CMD_SUPERIOR, 0},
	{CMD_NAME, SEPARATOR_OP, CMD_SUPERIOR, 0},
	{CMD_NAME, NEWLINE_LIST, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_WHILE, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_UNTIL, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_DO, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_PAREN_CLOSE, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_IF, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_ELIF, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_ELSE, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_THEN, CMD_SUPERIOR, 0},
	{CMD_NAME, COMPOUND_LIST, CMD_SUPERIOR, 0},
	{CMD_NAME, CASE_LIST_NS, CMD_SUPERIOR, 0},
	{CMD_NAME, COMPLETE_CONDITION, CMD_SUPERIOR, 0},
	{CMD_NAME, TK_PIPE, CMD_SUPERIOR, 0},
	{CMD_NAME, PIPE_SEMI_SEQUENCE, CMD_SUPERIOR, 0},
	{CMD_NAME, AND_OR_MAJOR, CMD_SUPERIOR, 0},
	{SIMPLE_COMMAND, ALL, COMMAND, 0},
	{DO_GROUP, NAME, FOR_CLAUSE, TK_FOR},
	{DO_GROUP, IN, FOR_CLAUSE, TK_FOR},
	{DO_GROUP, SEQUENTIAL_SEP, FOR_CLAUSE, TK_FOR},
	{DO_GROUP, CMD_SUPERIOR, LOOP, CMD_SUPERIOR},
	{DO_GROUP, COMPOUND_LIST, LOOP, COMPOUND_LIST},
	{BRACE_GROUP, ALL, COMPOUND_COMMAND, 0},
	{FUNCTION_BODY, FUNC, FUNCTION_DEFINITION, 0},
	{FUNCTION_DEFINITION, ALL, COMMAND, 0},
	{LOOP, TK_WHILE, WHILE_CLAUSE, TK_WHILE},
	{LOOP, TK_UNTIL, UNTIL_CLAUSE, TK_UNTIL},
	{UNTIL_CLAUSE, ALL, COMPOUND_COMMAND, 0},
	{WHILE_CLAUSE, ALL, COMPOUND_COMMAND, 0},
//	{ELSE_PART, COMPOUND_LIST, ELSE_PART, TK_ELIF},
//	{ELSE_PART, COMPLETE_CONDITION, IF_CLAUSE, COMPLETE_CONDITION},
	{IF_CLAUSE, ALL, COMPOUND_COMMAND, 0},
	{CASE_LIST_NS, TK_IN, TK_IN, TK_IN},
	{CASE_CLAUSE, ALL, COMPOUND_COMMAND, 0},
	{FOR_CLAUSE, ALL, COMPOUND_COMMAND, 0},
//	{COMPOUND_LIST, TK_ELSE, ELSE_PART, TK_ELSE},
	{COMPOUND_LIST, TK_IF, CONDITION, TK_IF},
	{COMPOUND_LIST, TK_THEN, CONDITION, TK_THEN},
	{COMPOUND_LIST, TK_PAREN_CLOSE, CLOSE_LIST, TK_PAREN_CLOSE},
	{COMPOUND_LIST, COMPLETE_CONDITION, COMPLETE_CONDITION, COMPLETE_CONDITION},
//	{COMPOUND_LIST, TK_THEN, ELSE_PART, TK_ELIF},
	{COMPOUND_LIST, COMPOUND_LIST, COMPOUND_LIST, COMPOUND_LIST},
	{COMPOUND_LIST, CASE_LIST_NS, CASE_LIST_NS, CASE_LIST_NS},
	{CLOSE_LIST, PATTERN, CASE_LIST_NS, PATTERN_CASE},
	{CLOSE_LIST, FUNC_NAME, FUNCTION_DEFINITION, FUNC_NAME},
	{SUBSHELL, ALL, COMPOUND_COMMAND, 0},
	{BRACE_CLAUSE, ALL, COMPOUND_COMMAND,  0},
	{COMPOUND_COMMAND, ALL, COMMAND, 0},
	{AND_OR_MINOR, PIPE_SEMI_SEQUENCE, AND_OR_MAJOR, PIPE_SEMI_SEQUENCE},
	{AND_OR_MINOR, LINEBREAK, AND_OR_MAJOR, 0},
	{AND_OR_MINOR, TK_PAREN_OPEN, AND_OR_MAJOR, 0},
	{AND_OR_MINOR, TK_LBRACE, AND_OR_MAJOR, 0},
	{AND_OR_MINOR, COMPLETE_COMMANDS, AND_OR_MAJOR, 0},
	{AND_OR_MINOR, AND_OR_MAJOR, AND_OR_MAJOR, 0},
	{COMMAND, PIPE_SEMI_SEQUENCE, PIPE_SEMI_SEQUENCE, PIPE_SEMI_SEQUENCE},
	{COMMAND, COMPOUND_LIST, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, CASE_LIST_NS, PIPE_SEMI_SEQUENCE, 0}, 
	{COMMAND, TK_WHILE, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_UNTIL, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_DO, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_PAREN_CLOSE, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_IF, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_THEN, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_ELIF, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_ELSE, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_BANG, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, SEPARATOR_OP, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, NEWLINE_LIST, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, LINEBREAK, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_PAREN_OPEN, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, TK_LBRACE, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, COMPLETE_COMMANDS, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, AND_OR_MAJOR, PIPE_SEMI_SEQUENCE, 0},
	{COMMAND, COMPLETE_CONDITION, PIPE_SEMI_SEQUENCE, 0},
	{END_COMMAND, PIPE_SEMI_SEQUENCE, PIPE_SEQUENCE, PIPE_SEMI_SEQUENCE},
	{END_COMMAND, AND_OR_MAJOR, LIST, AND_OR_MAJOR},
	{END_COMMAND, TK_WHILE, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_WHILE, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_UNTIL, PIPE_SEQUENCE, 0},
	{END_COMMAND, LINEBREAK, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_PAREN_OPEN, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_LBRACE, PIPE_SEQUENCE, 0},
	{END_COMMAND, COMPLETE_COMMANDS, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_DO, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_PAREN_CLOSE, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_IF, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_ELIF, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_THEN, PIPE_SEQUENCE, 0},
	{END_COMMAND, TK_ELSE, PIPE_SEQUENCE, 0},
	{END_COMMAND, COMPLETE_CONDITION, PIPE_SEQUENCE, 0},
	{END_COMMAND, COMPOUND_LIST, COMPOUND_LIST, COMPOUND_LIST},
	{END_COMMAND, CASE_LIST_NS, CASE_LIST_NS, CASE_LIST_NS},
	{PIPE_SEQUENCE, TK_WHILE, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_UNTIL, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_BANG, PIPELINE, TK_BANG},
	{PIPE_SEQUENCE, SEPARATOR_OP, PIPELINE, 0},
	{PIPE_SEQUENCE, NEWLINE_LIST, PIPELINE, 0},
	{PIPE_SEQUENCE, LINEBREAK, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_PAREN_OPEN, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_LBRACE, PIPELINE, 0},
	{PIPE_SEQUENCE, COMPLETE_COMMANDS, PIPELINE, 0},
	{PIPE_SEQUENCE, AND_OR_MAJOR, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_DO, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_PAREN_CLOSE, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_IF, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_ELIF, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_THEN, PIPELINE, 0},
	{PIPE_SEQUENCE, TK_ELSE, PIPELINE, 0},
	{PIPE_SEQUENCE, COMPOUND_LIST, PIPELINE, 0},
	{PIPE_SEQUENCE, CASE_LIST_NS, PIPELINE, 0},
	{PIPE_SEQUENCE, COMPLETE_CONDITION, PIPELINE, 0},
	{PIPELINE, TK_WHILE, AND_OR, 0},
	{PIPELINE, TK_UNTIL, AND_OR, 0},
	{PIPELINE, TK_DO, AND_OR, 0},
	{PIPELINE, TK_PAREN_CLOSE, AND_OR, 0},
	{PIPELINE, TK_IF, AND_OR, 0},
	{PIPELINE, TK_IF, AND_OR, 0},
	{PIPELINE, TK_ELIF, AND_OR, 0},
	{PIPELINE, TK_THEN, AND_OR, 0},
	{PIPELINE, TK_ELSE, AND_OR, 0},
	{PIPELINE, COMPOUND_LIST, AND_OR, 0},
	{PIPELINE, CASE_LIST_NS, AND_OR, 0},
	{PIPELINE, LINEBREAK, AND_OR, 0},
	{PIPELINE, TK_PAREN_OPEN, AND_OR, 0},
	{PIPELINE, TK_LBRACE, AND_OR, 0},
	{PIPELINE, COMPLETE_COMMANDS, AND_OR, 0},
//	{PIPELINE, LINEBREAK, AND_OR, AND_OR},
	{PIPELINE, SEPARATOR_OP, AND_OR, 0},
	{PIPELINE, COMPLETE_CONDITION, AND_OR, 0},
	{PIPELINE, AND_OR_MAJOR, AND_OR, AND_OR_MAJOR},
	{AND_OR_MAJOR, AND_OR_MAJOR, AND_OR_MAJOR, AND_OR_MAJOR},
	{AND_OR, TK_DO, COMPOUND_LIST, 0},
	{AND_OR, TK_PAREN_CLOSE, COMPOUND_LIST, 0},
	{AND_OR, TK_WHILE, COMPOUND_LIST, 0},
	{AND_OR, TK_UNTIL, COMPOUND_LIST, 0},
	{AND_OR, TK_IF, COMPOUND_LIST, 0},
	{AND_OR, TK_ELIF, COMPOUND_LIST, 0},
	{AND_OR, TK_THEN, COMPOUND_LIST, 0},
	{AND_OR, TK_ELSE, COMPOUND_LIST, 0},
	{AND_OR, COMPOUND_LIST, COMPOUND_LIST, 0},
	{AND_OR, TK_PAREN_OPEN, COMPOUND_LIST, 0},
	{AND_OR, TK_LBRACE, COMPOUND_LIST, 0},
	{AND_OR, CASE_LIST_NS, CASE_LIST_NS, 0},
	{AND_OR, COMPLETE_CONDITION, COMPOUND_LIST, 0},
	{AND_OR, SEPARATOR_OP, LIST, LIST},
	{AND_OR, NEWLINE_LIST, LIST, 0},
	{AND_OR, LINEBREAK, LIST, 0},
	{AND_OR, TK_LBRACE, LIST, 0},
	{AND_OR, COMPLETE_COMMANDS, LIST, 0},
	{LIST, NEWLINE_LIST, COMPLETE_COMMAND, 0},
	{LIST, LINEBREAK, COMPLETE_COMMAND, 0},
	{LIST, COMPLETE_COMMANDS, COMPLETE_COMMAND, 0},
	{COMPLETE_COMMAND, NEWLINE_LIST, COMPLETE_COMMANDS,  COMPLETE_COMMANDS},
	{COMPLETE_COMMAND, LINEBREAK, COMPLETE_COMMANDS, 0},
	{COMPLETE_COMMAND, COMPLETE_COMMANDS, COMPLETE_COMMANDS, 0},
	{COMPLETE_COMMANDS, COMPLETE_COMMANDS, COMPLETE_COMMANDS, COMPLETE_COMMANDS},
	{0, 0, 0, 0},
};

int			aggregate_sym(t_sym **stack, t_sym *new_sym, t_parstate *state)
{
	int		i;

	i = 0;
	DG("aggregate head %s && sym %s",
	read_state(**stack), read_state(*new_sym));
	while (g_aggrematch[i].top)
	{
		if (*new_sym == g_aggrematch[i].top
			&& MATCH_STACK(**stack, g_aggrematch[i].under))
	
		{
			DG("MATCH : %s", read_state(g_aggrematch[i].new_sym));
			*new_sym = g_aggrematch[i].new_sym;
			if (g_aggrematch[i].erase_sym)
			{
				pop_stack(stack, g_aggrematch[i].erase_sym);
				DG("stack after pop: %s", read_state(**stack));
			}
			if (eval_sym(**stack, *new_sym))
				return ((*state = ERROR));
			aggregate_sym(stack, new_sym, state);
			return (0);
		}
		i++;
	}
	return (0);
}
