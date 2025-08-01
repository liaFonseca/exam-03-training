#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c = fgetc(f);
	if (c == EOF || ferror(f))
		return -1;
	while (isspace(c))
		c = fgetc(f);
	if (ferror(f))
		return -1;
	ungetc(c, f);
    return (0);
}

int match_char(FILE *f, char c)
{
    int cf = fgetc(f);
	if (cf == c)
		return 1;
	ungetc(cf, f);
    return (-1);
}

int scan_char(FILE *f, va_list ap)
{
	char *ptr = va_arg(ap, char *);
	int cf = fgetc(f);
	if (cf == EOF || ferror(f))
		return -1;
    *ptr = cf;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int sign = 1;
	int num = 0;
	int *ptr = va_arg(ap, int *);
	int read_any = 0;
	int c = fgetc(f);
	if(c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while(c >= '0'&& c <= '9')
	{
		read_any = 1;
		num = num * 10 + (c - '0');
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	if (!read_any)
		return 0;
	*ptr = num * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	int i = 0;
	char *ptr = va_arg(ap, char *);
	int c = fgetc(f);
	while (!isspace(c) && c != EOF)
	{
		ptr[i] = c;
		i++;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	ptr[i] = '\0';
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	// ...
	int ret = ft_vfscanf(stdin, format, ap);
	// ...
	va_end(ap);
	return ret;
}
int	main()
{
	char str[100] = {0};
	int i;
	char c;
	ft_scanf("%d %s %c \n", &i, str, &c);
	printf("%d %s %c \n", i, str, c);
}