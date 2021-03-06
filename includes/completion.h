/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alao <alao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 11:13:04 by alao              #+#    #+#             */
/*   Updated: 2017/03/28 08:13:56 by alao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

# include "minishell.h"

# define KP_U		4283163
# define KP_D		4348699
# define KP_L		4479771
# define KP_R		4414235
# define KP_T		9
# define KP_TS		5921563

/*
** Autocompletion list for the valid candidates from the parser.
**       id : ID of the item.
**     name : Name of the item.
**     type : Type of the item.
**      len : Length of the name.
**   cursor : Boolean to know which item is currently selected.
**     next : Pointer to the next item of the list.
**     prev : Pointer to the previous item of the list.
*/

typedef struct		s_clst
{
	int				id;
	char			*name;
	int				type;
	int				len;
	int				cursor;
	struct s_clst	*next;
	struct s_clst	*prev;
}					t_clst;

/*
** Autocompletion structure composed as follow:
**     rcmd : The raw command from the begining to the cursor position.
**    ircmd : Cursor position.
**    cpath : Placeholder for the solved path. Later used for the parser.
**    match : Part of the command to match when searching.
**     home : Path to home for the ~ solving.
**      pwd : Current folder to solve local path.
**    start : See below.
**  between : See below.
**    trail : See below.
** cutpoint : See below.
**   prompt : Size of the prompt.
**     c_sx : Size of the longest word from the list.
**     c_sy : Size of the list in number of item.
**  c_pline : Number of item per line when printing.
**   c_line : Number of line required to move to terminal up.
**    win_x : Size of the window in length.
**    win_y : Size of the window in height.
**   m_size : Max size of the list in pagination.
**    pos_x : Position of the element relative to the terminal in list mode (X).
**    pos_y : Position of the element relative to the terminal in list mode (Y).
**      key : The keypressed lastly.
** isfolder : If the match is a folder. boolean.
**      lst : List of the item corresponding to the completion.
**
** The complete command is cutted as follow using the command as exemple:
**
**          Exemple: [ ls / ; cd (tab) ; pwd ]
**
**                                               (int)cutpoint
**                                                     |
**                                                     |
**  Become:  [ls / ;]         [ ]         [cd ]         [ ; pwd]
**            |                |           |              |
**            |                |           |              |
**     (char *)start   (char *)between   (char *)rcmd   (char *)trail
*/

typedef struct		s_comp
{
	char			*rcmd;
	int				ircmd;
	char			*cpath;
	char			*match;
	char			*home;
	char			*pwd;
	char			*start;
	char			*between;
	char			*trail;
	int				cutpoint;
	int				prompt;
	int				c_sx;
	int				c_sy;
	int				c_pline;
	int				c_line;
	int				win_x;
	int				win_y;
	int				m_size;
	int				pos_x;
	int				pos_y;
	int				key;
	int				isfolder;
	int				isrematch;
	t_clst			*lst;
}					t_comp;

/*
** Main autocompletion engine:
**        completion : Main function.
**            c_init : Initialization.
**        c_matching : Dispatcher for binary or local files.
**         c_rematch : Restart on keypress.
**   c_glob_matching : Call for globbing completion.
**     c_seek_binary : Search binary using env PATH.
**      c_seek_files : Solve path and search.
**        c_seek_env : Search in env for $(var)
**   c_seek_abs_path : Determiner for absolute path
**          c_parser : Parser.
**      c_add_to_lst : Add new node to the list.
**          c_sizing : Determine the size of the column/line.
*/

int					completion(long int key);
void				c_init(t_data *s, long int input);
int					c_matching(t_data *s, t_comp *c);
int					c_rematch(t_comp *c, long int keypress);
int					c_glob_matching(void);
int					c_seek_binary(t_data *s, t_comp *c);
int					c_seek_files(t_data *s, t_comp *c, char *current_word);
int					c_seek_env(t_comp *c, char *current_word);
void				c_seek_abs_path(t_comp *c, char *current_word);
int					c_parser(t_comp *c, char *path, char *name);
void				c_add_to_lst(t_comp *c, t_clst *node);
int					c_sizing(t_comp *c);

/*
** Output functions:
**
**      c_dispatcher : Choose between clear, print or update from to the list
**         c_updater : Output the result to struct data.
**        c_keypress : Keypress handling.
**           c_arrow : Arrow support.
*/

int					c_dispatcher(t_data *s);
int					c_updater(t_comp *c, char *select);
int					c_keypress(t_comp *c, long int key);
void				c_arrow(t_comp *c, long int keypress);

/*
** Terminal functions:
**
**    c_term_mv_down : Make space for the list.
**    c_term_mv_back : Reset the cursor position.
**      c_term_clear : Delete the list from the terminal.
**     c_term_resize : Refresh win_x and win_y.
**         c_printer : Printer of the list.
*/

void				c_term_mv_down(t_comp *c);
void				c_term_mv_back(t_comp *c);
void				c_term_clear(t_comp *c);
int					c_term_resize(t_comp *c);
void				c_printer(t_comp *c);

/*
** Support functions:
**
**           c_clear : Memory clearing.
**       c_clear_lst : List clearing.
**       path_solver : Solve abstract path to absolute.
** c_exclusion_foldr : Check for match folder.
**        ft_sstrlen : Return size of char **.
**      ft_sstrtostr : Create char * from char ** with char *sep between.
**     ft_add_escape : Add escape char to str.
**          c_lst_id : Repair ID list.
**        c_is_delim : Check char for specific one.
**         c_strdupi : Dupe
*/

int					c_clear(t_data *s);
int					c_clear_lst(t_comp *c);
char				*path_solver(t_comp *c, char *cmd, char *cwd);
int					c_exclusion_folder(t_comp *c);
int					ft_sstrlen(char **s);
char				*ft_sstrtostr(char **s, char *sep);
char				*ft_add_escape(char *str, char to_escape);
void				c_lst_id(t_comp *c);
int					c_is_delim(char c);
char				*c_strdupi(char *s, int (*f)(char));

#endif
