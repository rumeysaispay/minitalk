/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rispay-s <rispay-s@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:48:08 by rispay-s          #+#    #+#             */
/*   Updated: 2025/01/31 18:40:53 by rispay-s         ###   ########.fr       */
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

void	ft_handle_bit(int sig)
{
	static int	bit = 128;
	static int	res = 0;

	if (sig == SIGUSR1)
		res += bit;
	bit /= 2;
	if (bit == 0)
	{
		if (res == 0)
			write(1, "\n", 1);
		write(1, &res, 1);
		bit = 128;
		res = 0;
	}
}

int	main(void)
{
	write (1, "PID : ", 6);
	ft_putnbr (getpid());
	write (1, "\n", 1);
	signal (SIGUSR1, ft_handle_bit);
	signal (SIGUSR2, ft_handle_bit);
	while (1)
	{
		usleep(10);
		pause();
	}
}
