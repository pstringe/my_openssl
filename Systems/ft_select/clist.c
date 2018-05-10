/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 00:53:20 by pstringe          #+#    #+#             */
/*   Updated: 2018/05/10 02:53:54 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	initialize an element of the options list with a string value
*/

t_elem	*elemnw(char *str)
{
	t_elem *elem;

	elem = (t_elem*)ft_memalloc(sizeof(t_elem));
	elem->txt = str;
	elem->selected = 0;
	elem->prev = elem;
	elem->next = elem;
	return (elem);
}

/*
**	initialize the options list with an element
*/

t_ops	*init_ops(t_elem *elem)
{
	t_ops	*ops;

	ops = (t_ops*)ft_memalloc(sizeof(t_ops));
	ops->head = (elem) ? &elem : NULL;
	ops->cur_elem = ops->head;
	ops->lst_elem = ops->head;
	ops->len += elem ? 1 : 0;
	return (ops);
}

/*
**	add an element to the list of options
*/

void	elemadd(t_ops *ops, t_elem *elem)
{
	t_elem *r;
	t_elem *l;

	if (!elem || !ops)
		return ;
	r = ops->lst_elem ? (*(ops->lst_elem))->next : NULL;
	l = ops->lst_elem ? *ops->lst_elem : NULL;
	elem->prev = r ? r : elem;
	elem->next = l ? l : elem;
	if (l)
		l->prev = elem;
	if (r)
		r->next = elem;
	ops->lst_elem = &elem;
	ops->len += elem ? 1 : 0;
}

/*
**	destroy an element from the list
*/

void	elemdstry(t_ops *ops, t_elem *elem)
{
	t_elem *l;
	t_elem *r;

	if (!elem || !ops)
		return ;
	if (&elem == ops->head)
		ops->head = (elem) ? &(elem->next) : NULL; 
	if (&elem == ops->cur_elem)
		ops->cur_elem = (elem) ? &(elem->next) : NULL;
	if (&elem == ops->lst_elem)
		ops->lst_elem = (elem) ? &(elem->next) : NULL;
	l = elem->prev;
	r = elem->next;
	r->prev = (r->prev != elem) ? l : NULL;
	l->next = (l->next != elem) ? r : NULL;
	ft_memdel((void**)&elem->txt);
	ft_memdel((void**)&elem);
	ops->len--;
}
