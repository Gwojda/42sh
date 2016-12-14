/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <sbenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 01:45:09 by sbenning          #+#    #+#             */
/*   Updated: 2016/12/12 12:20:55 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_set_prompt(t_line *line)
{
	if (RL_IS(line->bitset, RL_ESC))
		line->prompt = RL_PROMPT_ESC;
	else if (RL_IS(line->bitset, RL_QUOTE))
		line->prompt = RL_PROMPT_QUOTE;
	else if (RL_IS(line->bitset, RL_DQUOTE))
		line->prompt = RL_PROMPT_DQUOTE;
	else
		line->prompt = RL_PROMPT_DEFAULT;
}

void		rl_put_prompt(t_line *line)
{
	curs_write(&line->curs, line->prompt, ft_strlen(line->prompt));
}