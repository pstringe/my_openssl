/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 07:11:57 by pstringe          #+#    #+#             */
/*   Updated: 2018/08/14 14:20:57 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	initialize argument struct
*/

t_args	*init_ssl()
{
	t_args	*args;

	args = ft_memalloc(sizeof(t_args));
	args->msg = NULL;
	args->cmd = NULL;
	args->ops = 0;
	return (args);
}

/*
**	retrieve options from cmd
*/

int 	get_ops(t_args *args, char *str)
{
	int i;
	
	i = 0;
	while (str[++i])
	{
		args->ops |= str[i] == 'p' ? OP_P : 0;
		args->ops |= str[i] == 'q' ? OP_Q : 0;
		args->ops |= str[i] == 'r' ? OP_R : 0;
		args->ops |= str[i] == 's' ? OP_S : 0;
	}
	return (args->ops ? args->ops : 0);
}

/*
**	parse program arguments
*/

int		parse(t_args *args, int argc, char **argv)
{
	int i;
	int j;

	i = -1;
	while (++i < argc)
	{
		j = -1;
		while (++j < NO_OF_FUNCS && !args->cmd)
			if (!ft_strncmp(g_cmd[j].name, argv[i], ft_strlen(argv[i])) && i++)
				args->cmd = &g_cmd[j];
		while (i < argc && argv[i][0] == '-' && !get_ops(args, argv[i]))
			i++;
	}
	return (--i);
}

/*
**	md5 hashing algorithm
*/

void	md5(t_args *args)
{
	ft_printf("md5 trigger: %s\nmessage: %s", args->cmd->name, args->msg);
}

/*
**	sha-256 hashing algorithm
*/

void	sha(t_args *args)
{
	ft_printf("sha-256 trigger: %s\nmessage: %s", args->cmd->name, args->msg);
}

/*
**	retrieve the plain-text input
*/

void	get_msg(t_args *args, int idx, char **argv, int argc)
{
	int 	fd;
	char 	*line;
	char	*tmp;

	fd = 0;
	if ((fd = open(argv[idx], O_RDONLY)) >= 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			tmp = args->msg ? ft_strdup(args->msg) : NULL;
			if (args->msg)
				free(args->msg);
			args->msg = ft_strjoin(tmp, line);
			if (line)
				free(line);
		}
	}
	else if (idx < argc && argv[idx])
		args->msg = ft_strdup(argv[idx]);
	else
		ft_printf("no argument\n");
}

int		main(int argc, char **argv)
{
	t_args	*args;	
	
	args = init_ssl();
	get_msg(args, parse(args, argc, argv), argv, argc);
	args->cmd->func(args);
}
