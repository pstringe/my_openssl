/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 07:11:57 by pstringe          #+#    #+#             */
/*   Updated: 2018/08/14 20:09:24 by pstringe         ###   ########.fr       */
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

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (++j < NO_OF_FUNCS && !args->cmd)
			if (!ft_strncmp(g_cmd[j].name, argv[i], ft_strlen(argv[i])) && i++)
				args->cmd = &g_cmd[j];
		while (i < argc && argv[i][0] == '-')
			if (get_ops(args, argv[i++]))
				break ;	
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
	else if ((fd = open(0, O_RDONLY)) >= 0)
	{
		get_next_line(fd, &line);
		args->msg = ft_strdup(line);
		free(line);
	}
	else if (idx < argc && argv[idx])
		args->msg = ft_strdup(argv[idx]);
	else
		ft_printf("no argument\n");
}

/*
**	split the message into 512bit (64 byte blocks) and pad up to 48bits
**	with the last 64 bits representing the length of the original message
*/

void	get_blocks(t_args *args)
{
	uint64_t 	len;
	size_t 		blocks;
	size_t 		remainder;
	char		block[64];
	int			i;
	int 		j;
	
	//establish length of original message
	len = ft_strlen(args->msg);

	//establish the expected number of complete blocks which do not require padding
	blocks = len / 64;

	//establish the remaining number of characters after the last complete block which must be padded into a complete block
	remainder = len % 64;
	i = 0;

	//this loop will execute, if and only if there are enough characters to form at least one complete block.
	while (--blocks)
	{
		//copy 64 bytes from the msg text to a block
		ft_memcpy(block, args->msg + i, 64);
		//enque a copy of this block 
		ft_enqueue(args->blocks, ft_strdup(block), 64 + 1);
		//increment the index by the number of copied bytes
		i += 64;
	}

	//copy the remaining number of bytes in the msg text over to bloc
	ft_memcpy(block, args->msg + i, len % 64);

	//increment i by the remaining number of bytes
	i += len % 64;

	//I append a bit to the end of the msg text by ORing it against that index
	block[i] |= (1 << 8);

	//I pad the block with null characters until the index is 64bits shy of a complete block
	while (++i < (blocks + 1) * 64 - 8)
		block[i] = '\0';

	//I use the last 64 bits to represent the original length of the msg
	ft_bzero(&block[i], 8);
	j = 8;
	while(i < 64 && j >= 0)
		block[i++] |= (0xff << j);
} 

int		main(int argc, char **argv)
{
	t_args	*args;	
	
	args = init_ssl();
	get_msg(args, parse(args, argc, argv), argv, argc);
	get_blocks(args);
	args->cmd->func(args);
}
