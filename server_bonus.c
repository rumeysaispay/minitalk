/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rispay-s <rispay-s@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:09:18 by rispay-s          #+#    #+#             */
/*   Updated: 2025/01/31 18:37:28 by rispay-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

int	ft_write_message(int client_signal)
{
	static int	bit_message = 1;
	static int	message = 0;

	if (client_signal == SIGUSR1)
		message += bit_message;
	bit_message *= 2;
	if (bit_message == 256)
	{
		write(1, &message, 1);
		bit_message = 1;
		if (message == 0)
			return (write(1, "\n", 1), 1);
		message = 0;
	}
	return (0);
}

void	ft_handle(int client_signal)
{
	static int	bit_pid = 0;
	static int	client_pid = 0;
	int			control;

	control = 0;
	if (bit_pid < 32)
	{
		if (client_signal == SIGUSR1)
			client_pid += 1 << bit_pid;
		bit_pid++;
	}
	else
	{
		control = ft_write_message(client_signal);
		if (control)
		{
			kill(client_pid, SIGUSR1);
			bit_pid = 0;
			client_pid = 0;
		}
	}
}

int	main(void)
{
	write(1, "PID : ", 6);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, ft_handle);
	signal(SIGUSR2, ft_handle);
	while (1)
	{
		usleep(10);
		pause();
	}
	return (0);
}
