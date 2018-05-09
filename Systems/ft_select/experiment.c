/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experiment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:37:21 by pstringe          #+#    #+#             */
/*   Updated: 2018/05/09 14:48:48 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <libft.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

extern char PC;
extern char *UP;
extern char *BC;
extern short ospeed;

void	fatal(char *msg)
{
	ft_putendl(msg);
	exit(-1);
}

/*
**	an application that needs to use termcaps must first retrieve a description
**	of the terminal. this is done using the function, tgetent()
*/

void	init_terminal_data(struct termios *term)
{
	char			*termtype;
	int				success;

	if (!(termtype = getenv("TERM")))
		fatal("specify terminal type with export `TERM=<termtype>'");
	ft_putendl(termtype);
	if ((success = tgetent(NULL, termtype) < 0))
		fatal("Could not access termcap database.");
	else if (tcgetattr(0, term) == -1) 
		fatal("Unable to get terminos struct");
}	

/*
**	Each piece of information recorded in the terminal description is refered to 
**	as a "capability".
**	Each "capability" is represented by a two-letter code.
**	Once the program has a rettrieved a terminal description, it must interrogate
**	the description for capabilities.
**	The values of capabilities will be either numeric, boolean, or string type.
**	tgetnum(), tgetflag and tgetstr() may be used to retrieve the values of
**	capabilities depending on their type.
**	Each of these functions take the capability's two-letter code as the first
**	argument. Only tgetstr() takes a second argument, which is the address of a
**	buffer to be populated with a capability's value.
**	It is important to initialize the terminal description using tgetent(),
**	as these functions all make use of the description retrieved in it's most
**	recent call.
*/

void	interrogate_terminal()
{
	char	*tmp;
	char	*cl_string;
	char	*cm_string;
	int		height;
	int		width;
	int		auto_wrap;
	
	//information for application
	cl_string = tgetstr("cl", NULL);
	cm_string = tgetstr("cm", NULL);
	auto_wrap = tgetflag("am");
	height = tgetnum("co");
	width = tgetnum("co");

	//information for termcap functions
	tmp = tgetstr("pc", NULL);
	PC = tmp ? *tmp : 0;
	BC = tgetstr("le", NULL);
	UP = tgetstr("up", NULL);

	ft_putendl(cl_string);
	ft_putendl(cm_string);
	ft_putendl(auto_wrap ? "true" : "false");
	ft_putnbr(height);
	ft_putnbr(width);

}

/*
**	modifications of this struct are done by using syscalls encoded as
**	integers, I glanced over this while reading the bsd icotl source but
**	it may be worth looking into since this seems to be a significant part
**	of what it takes to get things done using this library.
*/

void	modify_terminal(struct termios *term)
{
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		fatal("unable to set modified attributes in terminos struct");
}

/*
**	It's essential to restore default behavior of the shell after any 
**	modification of the termios struct. (Remember the time you fucked up
**	your shell while experimenting)
*/

void	restore_default_behavior(struct termios *term)
{
	if (tcgetattr(0, term) == -1)
		fatal("unable to set attributes while restoring defaults");
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, term) == -1)
		fatal("unable to set attributes while restoring defaults");
}

void	identify_key()
{
	char buf[4];

	while (1)
	{
		read(0, buf, 3);
		buf[3] = '\0';
		ft_putendl(buf);
		if (buf[0] == 4)
			break;
	}
}

int		ft_pc(int c)
{
	write(0, &c, 1);
	return (0);
}

void	c_s()
{
	char *str;

	if (!(str = tgetstr("cl", NULL)))
		fatal("failed to interrogate terminal");
	ft_putendl(str);
	tputs(str, 0, ft_pc);
}

/*
**	Now, in order to use tputs() to specify padding, I'll need
**	to have, (1) the command string (in which the padding spec is contained),
**	(2) the number of lines affected by the command, (3) a function to output
**	characters one by one and return an int.
**	I'll need to make use of the global variables, PC, and ospeed. PC, being the
**	padding character (most likley null), ospeed, being the output speed of the
**	terminal.
*/
int		main(void)
{
	struct termios term;

	init_terminal_data(&term);
	///interrogate_terminal();
	modify_terminal(&term);
	identify_key();
	c_s();
	restore_default_behavior(&term);
	return (0);
}
