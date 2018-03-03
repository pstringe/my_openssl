/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:52:32 by pstringe          #+#    #+#             */
/*   Updated: 2018/03/03 11:12:17 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "libft.h"

int main(int argc, char const **argv)
{
	int 				port;
	int					sock;
	int					ret;
	struct sockaddr_in 	serv_addr;
	//struct sockaddr_in 	addr;
	char const			*msg;
	char				buf[1024];

	if (argc != 2)
	{
		ft_putendl("please enter the poert of the server you wish to message, and then the message.");
		return (-1);
	}
	msg = argv[1];
	port = ft_atoi(argv[2]);
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) < 0))
	{
		ft_putendl("socket error");
		return (-1);
	}
	ft_memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
	{
		ft_putendl("invalid address");
		return (-1);
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		ft_putendl("failed to connect");
		return (-1);
	}
	send(sock, msg, ft_strlen(msg), 0);
	ft_putendl("message sent");
	ret = read(sock, buf, 1024);
	buf[ret] = '\0';
	ft_putendl(buf);
	close(sock);
}
