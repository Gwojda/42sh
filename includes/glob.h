/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:31:18 by wescande          #+#    #+#             */
/*   Updated: 2017/02/01 19:50:07 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H

# include "minishell.h"

# define CH(x) ((char **)(x)->content)
# define UCH(x) ((unsigned char **)(x)->content)

typedef struct	s_ld
{
	void			*content;
	struct s_ld		*next;
	struct s_ld		*prev;
}				t_ld;

typedef struct	s_glob
{
	const char			*pat;
	const unsigned char	*esc;
	t_ld				*match;
	t_ld				*m_pat;
}				t_glob;

typedef struct	s_expand
{
	t_ld			**wk;
	char			*str;
	unsigned char	*esc;
	char			**split;
	unsigned char	**m_esc;
	char			*s1;
}				t_expand;

/*
** interface of glob.
*/
char			**glob(const char *str, const unsigned char *esc);

/*
** return TRUE if path file is a directory.
*/

int				is_directory(const char *path);
/*
** return TRUE if char at str_pos in ini_str is escape.
*/
int				is_char_esc(const unsigned char *esc,
							const char *ini_str, const char *str_pos);

/*
** Internal function.
*/
unsigned char	*ft_sub_esc(const unsigned char *esc, int start, int len);
unsigned char	*calc_expand_esc(const unsigned char *esc,
								int nb_start, int nb_middle, int *nb_end);
void			modify_esc_split(unsigned char *esc_dest,
								unsigned char *esc_src, int start, int len);
void			expand_brace(t_glob *tglob);
int				match_pattern(t_glob *tglob, char *str, char *full_word);
int				dir_research(t_glob *tglob, char *p, const char *pat, int rec);
char			**ft_strsplit_spe(const char *str,
								const unsigned char *esc, char c);
unsigned char	**ft_strsplit_esc(const char *str,
								const unsigned char *esc, char c);
/*
** LIST D:
*/
void			ft_ld_new(t_ld **alst, void *content);
t_ld			*ft_ld_front(t_ld	*ld);
void			ft_ld_pushfront(t_ld **alst, void *content);
void			ft_ld_pushback(t_ld **alst, void *content);
size_t			ft_ld_size(t_ld *ld);
void			ft_ld_del(t_ld **ld, void (*del)());
void			ft_ld_clear(t_ld **ld, void (*del)());
void			ft_ld_reverse(t_ld **lst);
t_ld			*ft_ld_back(t_ld *ld);
t_ld			*ft_ld_swap(t_ld *l_cur);
char			**ft_ld_to_tab(t_ld *ld);
t_ld			*ft_ld_order(t_ld *ld, int (*f)(), void (*del)());

/*
** str:
*/

char			*ft_strjoinf(char *str, char *str2, int mode);
void			ft_tabdel(char ***mytab);
int				ft_tablen(char **mytab);

#endif