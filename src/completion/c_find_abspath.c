/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_find_abspath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:54:59 by gwojda            #+#    #+#             */
/*   Updated: 2017/03/23 19:07:47 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

/*
** Process the absolute path for the completion.
*/

void		c_seek_abs_path(t_comp *c, char *current_word)
{
	char	*tmp;
	int		len;

	len = ft_strrchr(current_word, '/') - current_word + 1;
	if (len < 0)
		return ;
	if (c->cpath)
		ft_strdel(&c->cpath);
	c->cpath = ft_strndup(current_word, len);
	if (current_word[0] == '~')
	{
		tmp = c->cpath;
		c->cpath = ft_str3join(getenv("HOME"), "/", c->cpath + 2);
		free(tmp);
	}
	!c->match ? c->match = ft_strdupi_w(ft_strrchr(c->rcmd, '/') + 1) : 0;
	c_parser(c, c->cpath, c->match);
	if (c->lst == NULL || c->lst == c->lst->prev)
		c_exclusion_folder(c);
	c_lst_id(data_singleton()->comp);
}
