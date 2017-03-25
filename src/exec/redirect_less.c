/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_less.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 22:09:53 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/25 01:52:33 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redirect_less(t_redir *redir)
{
	int		fdold;
	int		fdnew;

	fdnew = redir->n;
	if ((fdold = open_access(redir->word, W_OK,
					O_RDONLY, 0)) != 0)
		return (ft_perror(NULL));
	dup2(fdold, fdnew);
	return (0);
}
