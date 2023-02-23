/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfprova.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgolino <lgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:03:54 by lgolino           #+#    #+#             */
/*   Updated: 2023/02/23 10:52:48 by lgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int p)
{
	return (write(1, &p, 1));
}

int ft_putstr(char*x)
{
    int	i;

	i = 0;
	while (x[i] != '\0')
	{
		ft_putchar(x[i]);
		i++;
	}
	return (i);
}

int ft_pointervoid(int a)
{
	if (a < 16)
		ft_putchar("0123456789abcdef"[a]);
	else
	{
		ft_pointervoid(a / 16);
		ft_putchar("0123456789abcdef"[a % 16]);
	}
	return (0);
}

int ft_putuint(unsigned int a)
{
	if (a < 10)
	{
		a += 48;
		ft_putchar(*a);
	}
	else
	{
		ft_putuint(a / 10);
		a = a%10;
		a += 48;
		write(1, &a, 1);
	}
	return (0);
}

int ft_putnbr(int a)
{
	int c;

	c = 0;
    if (a < 0)
	{
		c += ft_putchar('-');
		a = -a;
	}
	if (a < 10)
	{
		a += 48;
		c += ft_putchar(a);
	}
	else
	{
		c += ft_putnbr(a / 10);
		c += ft_putchar(a % 10);
	}
	return (c);
}

int ft_putnbr16(uintptr_t l)
{
	char s[16] = "0123456789abcdef";
	if (l < 16)
	{
		ft_putstr("0x");
		write(1, &(s[l % 16]), 1);
	}
	else
	{
		ft_putnbr16(l / 16);
		write(1, &(s[l % 16]), 1);
	}
	return (0);
}

int ft_putnbrbig(unsigned int l)
{
	char s[16] = "0123456789ABCDEF";
	if (l < 16)
	{
		l += 48;
		ft_putstr("0x");
		write(1, &(s[l % 16]), 1);
	}
	else
	{
		ft_putnbrbig(l / 16);
		write(1, &(s[l % 16]), 1);
	}
	return (0);
}

int ft_printf(const char *s, ...)
{
    int i;
    int q;
    va_list d; // listare argomenti
    va_start(d,s);
    i = 0;
    q = 0;
    

    while (s[i])
    {
        if (s[i] == '%')
        {
            if (s[i + 1] == 'c')
                q += ft_putchar(va_arg(d, int));
            else if (s[i + 1] == 's')
                q += ft_putstr(va_arg(d, char*));
            else if (s[i + 1] == 'p')
			{
				q += write(1, "0x", 2);
                q += ft_pointervoid(va_arg(d, uintptr_t));
			}
            else if (s[i + 1] == 'd' || s[i + 1] == 'i')
                q += ft_putnbr(va_arg(d, int));
            else if (s[i + 1] == '%')
                q += ft_putchar('%');
            else if (s[i + 1] == 'u')
				q += ft_putuint(va_arg(d, unsigned int));
			else if (s[i + 1] == 'x')
				q += ft_putnbr16(va_arg(d, uintptr_t ));
			else if (s[i + 1] == 'X')
				q += ft_putnbrbig (va_arg(d, unsigned int));
			i++;
        }
		else 
			q += write (1, &s[i], 1);
		i++;
    }
	return(q);
}

 //int main()
 //{
     //ft_printf("ciao questo è il mio nome: %c %s %d %x", 'f', "ciao", 5, 15);
   //  return 0;
 //}
