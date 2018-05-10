/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 01:51:51 by pstringe          #+#    #+#             */
/*   Updated: 2018/05/10 03:02:14 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display(t_ops *ops)
{
	int 	i;
	t_elem	*cur;

	cur = (ops->head) ? *ops->head : NULL;
	i = 0;
	while (++i < ops->len)
		ft_putendl(cur->txt);
}

void	parse_args(t_select *s, int argc, char **argv)
{
	t_ops	*ops;
	int		i;

	ops = init_ops(NULL);
	i = 0;
	while (++i < argc)
		elemadd(ops, elemnw(argv[i]));
	s->options = ops;
}

void	init_select(t_select **select, int argc, char **argv)
{
	t_select	*s;
	
	s = (t_select*)ft_memalloc(sizeof(t_select));
	init_terminal_data(s);
	parse_args(s, argc, argv);
	*select = s;
}

int			main(int argc, char **argv)
{
	t_select	*select;

	if (argc < 2)
		return (0);
	init_select(&select, argc, argv);
	display(select->options);	
	return (0);
}
