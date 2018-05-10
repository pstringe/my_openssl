/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 00:24:10 by pstringe          #+#    #+#             */
/*   Updated: 2018/05/10 02:52:13 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include <curses.h>
# include <libft.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>

/*
**	each option in the list will be represented by an element
*/

typedef struct	s_elem
{
	char			*txt;
	int				selected;
	struct s_elem	*prev;
	struct s_elem	*next;
}				t_elem;

/*
**	this structure contains a circular, doubly-linked list of options
*/

typedef struct	s_ops
{
	struct s_elem	**head;
	struct s_elem	**cur_elem;
	struct s_elem	**lst_elem;
	int				len;
}				t_ops;

/*
**	contains variables uses in conjunction with tercaps functions
*/

typedef struct	s_extern
{
	char PC;
	char *UP;
	char *BC;
	short ospeed;
}				t_extern;

/*
** contains everything needed for ft_select to function.
*/

typedef struct	s_select
{
	struct termios	*term;
	struct s_extern	ext;
	struct s_ops 	*options;
}				t_select;

/*
**	circular list functions
*/

t_elem			*elemnw(char *str);
t_ops			*init_ops(t_elem *elem);
void			elemadd(t_ops *ops, t_elem *elem);
void			elemdstry(t_ops *ops, t_elem *elem);

/*
**	terminal functions
*/

void	init_terminal_data(t_select *select);

/*
**	output
*/


/*
**	utility funtions
*/

void	fatal(char *msg);
#endif

