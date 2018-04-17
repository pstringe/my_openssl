/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:17:01 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/16 21:02:31 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

typedef struct	s_prog
{
	t_queue		*instr;
	t_stck		*a;
	t_strck		*b;
}				t_prog;

t_queue	*get_instructions()
{
	t_queue	*instr;
	int		 err;

	stck = ft_queuenw(NULL);
	while (get_next_line(0, &buf) > 0)
		ft_enqueue(instr, (err = vaidate_instruction(buf)), sizeof(char*));
	if (err)
		ft_queuedstry(&instr);
	return ((err) ? NULL : instr);
}

int		execute_instructions(t_prog *prog)
{
	char	*cur;

	while ((cur = ft_dequeue(prog->instr, sizeof(char*))
		execute(cur, a, b);
	if (ft_stcksrtd(a, b))
		return (1);
	else
		return (0);
}

int		main(int argc, char **argv)
{
	int		i;
	char	*buf;
	t_prog	*prog;

	a = get_a(argv);
	b = ft_stcknw(NULL);
	if(!(prog->instr = get_instructions()))
	{
		write(2, "Err\n", 4);
		return ;
	}
	if(!(execute_instructions(prog)))
		ft_putendl("KO");
	else
		ft_putendl("KO");
}
