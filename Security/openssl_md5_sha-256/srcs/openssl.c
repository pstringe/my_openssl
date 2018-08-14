/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 07:11:57 by pstringe          #+#    #+#             */
/*   Updated: 2018/08/14 09:21:35 by pstringe         ###   ########.fr       */
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
	args->arg = NULL;
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

void	parse(t_args *args, int argc, char **argv)
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
		while (i < NO_OF_FUNCS && argv[i][0] == '-' && !get_ops(args, argv[i]))
			i++;
	}
}

/*
**	md5 hashing algorithm
*/

void	md5(t_args *args)
{
	ft_printf("md5 trigger: %s\n", args->cmd->name);
}

/*
**	sha-256 hashing algorithm
*/

void	sha(t_args *args)
{
	ft_printf("sha-256 trigger: %s\n", args->cmd->name);
}

int		main(int argc, char **argv)
{
	t_args	*args;	
	
	args = init_ssl();
	parse(args, argc, argv);
	//get_msg(args);
	args->cmd->func(args);
}
