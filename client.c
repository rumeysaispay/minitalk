/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rispay-s <rispay-s@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:48:01 by rispay-s          #+#    #+#             */
/*   Updated: 2025/01/31 18:34:24 by rispay-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10;
			res = res + str[i] - 48;
		}
		i++;
	}
	return (res);
}

void	ft_send_bit(int pid, char c)
{
	int	bit;	

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		bit--;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	if (ac == 3)
	{
		i = 0;
		pid = ft_atoi(av[1]);
		if (pid <= 0)
		{
			write(1, "PID ERROR!", 10);
			return (-1);
		}
		while (av[2][i])
		{
			ft_send_bit(pid, av[2][i]);
			i++;
		}
		ft_send_bit(pid, 0);
	}
	else
		write(1, "WRONG ARGUMENT", 13);
	return (0);
}
