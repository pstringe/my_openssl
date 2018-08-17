/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 07:11:57 by pstringe          #+#    #+#             */
/*   Updated: 2018/08/16 18:27:38 by pstringe         ###   ########.fr       */
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

void	print_block(char block[64])
{
	int i;
	int j;
	int k;
	
	i = 0;
	while (++i <= 4)
	{
		j = 0;
		while (++j <= 4)
		{
			k = 0;
			while (++k <= 4)
				ft_putchar(block[(i % j) * (j % k)]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

t_queue		*ft_queuenw(void *n, size_t size)
{
	t_queue	*q;
	t_list	*tmp;

	q = (t_queue*)ft_memalloc(sizeof(t_queue));
	tmp = ft_lstnew(n, size);
	q->tail = tmp;
	q->head = tmp;
	return (q);
}

void		*ft_dequeue(struct s_queue *q)
{
	t_list		*tmp;
	void		*t;

	if (!q->head)
		return (NULL);
	tmp = q->head;
	q->head = tmp->next;
	t = ft_memalloc(tmp->content_size);
	ft_memcpy(t, tmp->content, tmp->content_size);
	ft_memdel((void**)&(tmp->content));
	ft_memdel((void**)&tmp);
	if (!q->head)
		q->tail = NULL;
	return (t);
}
/*
**	split the message into 512bit (64 byte blocks) and pad up to 48bits
**	with the last 64 bits representing the length of the original message
*/

void	get_blocks(t_args *args)
{
	uint64_t	len;
	int 		blocks;
	int	 		remainder;
	char		block[64];
	int			i; //position in the original message
	int 		j; //position in padding block
	int			k; //bit mask
	int			l; //shift the result of the bit mask to least significant place-value

	//establish length of original message
	len = ft_strlen(args->msg);

	//establish the expected number of complete blocks which do not require padding
	blocks = len / 64;

	//establish the remaining number of characters after the last complete block which must be padded into a complete block
	remainder = len % 64;
	i = 0;

	//this loop will execute, if and only if there are enough characters to form at least one complete block.
	while (blocks-- > 0)
	{
		//copy 64 bytes from the msg text to a block
		ft_memcpy(block, args->msg + i, 64);
		//enque a copy of this block
		if (!args->blocks)
			args->blocks = ft_queuenw(ft_strdup(block), 64);
		else
			ft_enqueue(args->blocks, ft_strdup(block), 64);
		//increment the index by the number of copied bytes
		i += 64;
	}
	//copy the remaining number of bytes in the msg text over to bloc
	ft_memcpy(block, args->msg + i, len % 64);
	

	//increment i by the remaining number of bytes
	i += len % 64;

	//set j to the remaining no of bytes
	j = len % 64;

	//I append a bit to the end of the msg text by ORing it against that index
	block[j] |= (1 << 7);

	//I pad the block with null characters until the index is 64bits shy of a complete block
	while (++j < 64 - 8)
		block[j] = '\0';

	//I use the last 64 bits to represent the original length of the msg
	ft_bzero(&block[j], 8);
	
	k = 8; //bit mask shift
	l = 8; //shift on the resulting bit mask to the least significant place value
	
	//for each of the remaining 8 bytes, on the block,
	while(j < 64 && k >= 0)
		/* 
		 * isolate the appropriate bits from the total length starting with the most significant,
		 * shift them to the least significant place value, and OR them against the current byte
		 *  in the block
		 */
		block[j++] |= (((0xff << --k) & len) >> --l);
	
	//initialize the queue in the event there was <= 1 blocks worth of text
	if (!args->blocks)
		args->blocks = ft_queuenw(ft_strdup(block), 64 + 1);
	else
		ft_enqueue(args->blocks, ft_strdup(block), 64);
} 

int		main(int argc, char **argv)
{
	t_args	*args;	
	
	args = init_ssl();
	get_msg(args, parse(args, argc, argv), argv, argc);
	get_blocks(args);
	/*test*/
	int 	i = -1;
	char 	*block;
	while ((block = (char*)ft_dequeue(args->blocks)))
	{
		ft_printf("block %d:\n", ++i);
		int j = -1;
		while (++j < 65)
			ft_putchar(block[j] < 41 ? '.' : block[j]);
		ft_putchar('\n');
	}
	/*end test*/
	args->cmd->func(args);
}
