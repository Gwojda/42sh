/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:11:48 by jhalford          #+#    #+#             */
/*   Updated: 2017/02/21 16:15:41 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_data			t_data;

typedef long long				t_type;
typedef long long				t_flag;
typedef struct s_line			t_line;
typedef struct s_comp			t_comp;
typedef struct s_exec			t_exec;
typedef struct s_jobc			t_jobc;
typedef enum e_mode				t_mode;

typedef struct s_lexer			t_lexer;
typedef enum e_lexstate			t_lexstate;
typedef struct s_token			t_token;

typedef struct s_ld				t_ld;
typedef struct s_astnode		t_astnode;
typedef struct s_redir			t_redir;
typedef union u_astdata			t_astdata;
typedef union u_word			t_word;
typedef long long				t_type;

typedef struct s_job			t_job;
typedef struct s_execmap		t_execmap;
typedef struct s_redirmap		t_redirmap;
typedef struct s_process		t_process;
typedef int		(t_execf)(const char *path, char *const argv[], char *const envp[]);

typedef int						t_sym;
typedef struct s_parser			t_parser;
typedef enum e_parstate			t_parstate;
typedef struct s_aggrematch		t_aggrematch;
typedef struct s_prodmatch		t_prodmatch;
typedef struct s_stackmatch		t_stackmatch;
typedef struct s_errormatch		t_errormatch;
typedef struct s_treematch		t_treematch;

t_data		*data_singleton();

#endif
