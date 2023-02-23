/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgolino <lgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:22:12 by lgolino           #+#    #+#             */
/*   Updated: 2023/02/20 13:04:36 by lgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

int	ft_putchar(int p)
{
	return (write(1, &p, 1));
}

int ft_putnbr(int a)
{
	if (a < 0)
	{
		write(1, "-", 1);
		a = -a;
	}
	if (a < 10)
		write(1, &"0123456789"[a], 1);
	else
	{
		ft_putnbr(a / 10);
		write(1, &"0123456789"[a % 10], 1);
	}
}

int ft_putuint(unsigned int a)
{
	if (a < 10)
		write(1, &"0123456789"[a], 1);
	else
	{
		ft_putuint(a / 10);
		write(1, &"0123456789"[a % 10], 1);
	}
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int ft_putnbr16(uintptr_t l)
{
	if (l < 16)
	{
		ft_putstr("0x");
		write(1, &"0123456789abcdef"[l % 16], 1);
	}
	else
	{
		ft_putnbr16(l / 16);
		write(1, &"0123456789abcdef"[l % 16], 1);
	}
}

int ft_putbigorlittle16(unsigned int l, int x)
{
	char *dig;

	dig = "0123456789abcdef";
	if (x == 'X')
		dig = "0123456789ABCDEF";
	if (l < 16)
	{
		write(1, &dig[l % 16], 1);
	}
	else
	{
		ft_putbigorlittle16(l / 16, x);
		write(1, &dig[l % 16], 1);
	}
}

int	ft_printf(const char *s, ...)
{
	va_list	d;
	int		i;

	i = 0;
	va_start(d, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (s[i + 1] == 'c')
				ft_putchar(va_arg(d, int));
			else if (s[i + 1] == 's')
				ft_putstr(va_arg(d, char *));
			else if (s[i + 1] == 'd' || s[i + 1] == 'i')
				ft_putnbr(va_arg(d, int));
			else if (s[i + 1] == 'p')
				ft_putnbr16(va_arg(d, uintptr_t));
			else if (s[i + 1] == 'p')
				ft_putuint(va_arg(d, unsigned int));
			else if (s[i + 1] == '%')
				ft_putchar('%');
			else if (s[i + 1] == 'x' || s[i + 1] == 'X')
				ft_putbigorlittle16(va_arg(d, unsigned int), s[i + 1]);
			i++;
		}
		else
			write(1, &s[i], 1);
		i++;
	}
	va_end(d);
	return (0);
}

int	main(int argc, char const *argv[])
{
	int r = 65;
	int *p = &r;
	ft_printf("%c %s %i %p %X\n", 'g', "bro", 78, p, 15);
	return (0);
}
