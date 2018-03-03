/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hydra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:52:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/03/02 18:39:07 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/socket.h>
#include <netinet/in.h>

int		main(int argc, char **argv)
{
	int					port;
	int 				server_fd;
	int 				new_socket;
	int 				ret;
	int					opt;
	int					addrlen;
	char				buf[1024];
	char 				*pong;
	struct sockaddr_in 	address;

	if (argc < 2)
	{
		ft_putendl("Please specify port to listen on!");
		return (-1);
	}
	port = ft_atoi(argv[1]);
	opt = 1;
	addrlen = sizeof(address);
	pong = "pong";
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		ft_putendl("failed to create socket");
		exit(EXIT_FAILURE);
	}
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		ft_putendl("error attatching socket to port");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		ft_putendl("failed to bind");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		ft_putendl("I'm not listening!");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)(&address), (socklen_t*)(&addrlen))) < 0)
	{
		ft_putendl("I do not accept.");
		exit(EXIT_FAILURE);
	}
	ret = read(new_socket, buf, 1024);
	buf[ret] = '\0';
	ft_putendl(buf);
	send(new_socket, pong, ft_strlen(pong), 0);
	ft_putendl("pong sent");
}
