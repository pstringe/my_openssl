/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 07:11:57 by pstringe          #+#    #+#             */
/*   Updated: 2018/08/13 07:22:04 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define 2 OP_P
# define 4 OP_Q
# define 8 0P_R
# define 16 OP_S

typedef struct	s_args
{
	char	*arg;
	char	*cmd;
	int		ops;
}				t_args;

t_args	*init()
{
	args = ft_memalloc(sizeof(t_args))
	args->arg = NULL;
	args->cmd = NULL;
	args->op = 0;
}

int	main(int argc, char **argv)
{
	t_args *args;

	args = init();
	parse(args, argc, argv);
}
