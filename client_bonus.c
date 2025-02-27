/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rispay-s <rispay-s@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:08:44 by rispay-s          #+#    #+#             */
/*   Updated: 2025/01/31 18:36:32 by rispay-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
}

void	ft_send_client_pid(int server_pid, int client_pid)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (client_pid >> i & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i++;
		usleep(800);
	}
}

void	ft_send_bit(int server_pid, unsigned char send)
{
	int	bit;

	bit = 0 ;
	while (bit < 8)
	{
		if ((send >> bit) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		bit++;
		usleep(800);
	}
}

void	ft_handler(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Mesajlar başarı ile yazıldı!", 33);
}

int	main(int ac, char **av)
{
	int	i;
	int	server_pid;
	int	client_pid;

	i = 0;
	if (ac == 3)
	{
		signal (SIGUSR1, ft_handler);
		client_pid = getpid();
		server_pid = ft_atoi(av[1]);
		if (server_pid <= 0)
			return (write(1, "Please enter correct PID!", 25), 0);
		ft_send_client_pid(server_pid, client_pid);
		while (av[2][i])
		{
			ft_send_bit(server_pid, av[2][i]);
			i++;
		}
		ft_send_bit(server_pid, '\0');
	}
}
