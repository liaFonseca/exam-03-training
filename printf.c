#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int ft_print(char c, va_list args)
{
	int n_letters;

	n_letters = 0;
	if (c == 'c')
		n_letters += ft_putchar(va_arg(args, int));
	if (c == '%')
		n_letters += ft_putchar(c);
	else if (c == 's')
		n_letters += ft_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		n_letters += ft_putdigit(va_arg(args, int), 10, c);
	else if (c == 'u')
		n_letters += ft_putdigit(va_arg(args, unsigned int), 10, c);
	else if (c == 'x' || c == 'X')
		n_letters += ft_putdigit(va_arg(args, unsigned int), 16, c);
	else if (c == 'p')
		n_letters += ft_putptr(va_arg(args, void *), 16);
	return (n_letters);
}



int ft_putp(unsigned long num, unsigned long base)
{
	char *symbol;
	int n_letters;
	int last_digit;

	n_letters = 0;
	symbol = "0123456789abcdef";
	if (num < base)
		n_letters += ft_putchar(symbol[num]);
	else
	{
		last_digit = num % base;
		n_letters += ft_putp(num/base, base);
		n_letters += ft_putchar(symbol[last_digit]);
	}
	return (n_letters);
}

int ft_putptr(void *ptr, unsigned long base)
{
	int n_letters;

	n_letters = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	n_letters += ft_putstr("0x");
	return (n_letters + ft_putp((unsigned long) ptr, base));
}

int ft_putdigit(long num, long base, char option)
{
	char *symbol;
	int n_letters;
	int last_digit;

	n_letters = 0;
	symbol = "0123456789abcdef";
	if (option == 'X')
		symbol = "0123456789ABCDEF";
	if (num < 0)
	{
		n_letters += ft_putchar('-');
		num *= -1;
	}
	if (num < base)
		n_letters += ft_putchar(symbol[num]);
	else
	{
		last_digit = num % base;
		n_letters += ft_putdigit(num/base, base, option);
		n_letters += ft_putchar(symbol[last_digit]);
	}
	return (n_letters);
}

int	ft_putchar(int c)
{
	return write(1, c, 1);
}

int	ft_putstr (char *str)
{
	if (!str)
		return (write(1, "(null)", strlen("(null)")));
	return (write(1, str, strlen(str)));
}



int	printf(char *format, ...)
{
	va_list args;
	int n_letters;

	va_start(args, format);
	n_letters = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			n_letters +=ft_print(*format, &args);
		}
		else
		{
			n_letters += ft_putchar(*format);
		}
		format++;
	}
	va_end(args);
	return(n_letters);
}