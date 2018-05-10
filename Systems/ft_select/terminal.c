/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 01:41:55 by pstringe          #+#    #+#             */
/*   Updated: 2018/05/10 02:36:47 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	fatal(char *msg)
{
	ft_putendl(msg);
	exit(-1);
}

/*
**	an application that needs to use termcaps must first retrieve a description
**	of the terminal. this is done using the function, tgetent()
*/

void	init_terminal_data(t_select *select)
{
	char			*termtype;
	int				success;

	if (!(termtype = getenv("TERM")))
		fatal("specify terminal type with export `TERM=<termtype>'");
	if ((success = tgetent(NULL, termtype) < 0))
		fatal("Could not access termcap database.");
	else if (tcgetattr(0, select->term) == -1) 
		fatal("Unable to get terminos struct");
}
