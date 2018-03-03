/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:52:32 by pstringe          #+#    #+#             */
/*   Updated: 2018/03/03 11:36:18 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "libft.h"

int main(int argc, char const **argv)
{
	int					con;
	int					port;
	int					sock;
	char				resp[256];
	struct sockaddr_in 	serv_addr;

	if (argc < 2)
	{
		ft_putendl("Please specify port");
		return (-1);
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	port = ft_atoi(argv[1]);
	serv_addr.sin_port = htons(port);
	//I can connect to any port on my local machine using 0.0.0.0 (INADDR_ANY)
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (-1 == (con = (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))))
	{
		ft_putendl("Connection error");
		return (-1);
	}
	recv(sock, &resp, sizeof(resp), 0);
	ft_putendl("server response:");
	ft_putendl(resp);
	close(sock);
	return (0);
}
