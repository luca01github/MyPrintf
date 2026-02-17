#include <stdarg.h>
#include <unistd.h>

void my_putc(char c) { write(1, &c, 1); }

void my_putstr(const char *str) {
    if (!*str) {
        return;
    }
    while (*str) {
        my_putc(*str);
        str++;
    }
}

void my_putint(int num) {
    long n = num;

    if (n < 0) {
        my_putc('-');
        n *= -1;
    }

    if (n >= 10) {
        my_putint(n / 10);
    }
    my_putc((n % 10) + '0');
}

void my_putf(float n) {
    int precision = 6;

    if (n < 0) {
        my_putc('-');
        n *= -1;
    }

    int intpart = (int)n;
    float floatpart = n - intpart;

    my_putint(intpart);
    my_putc('.');

    for (int i = 0; i < precision; i++) {
        floatpart *= 10;
        my_putint((int)floatpart);
        floatpart = floatpart - (int)floatpart;
    }
}

void my_printf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);

    while (*format) {
        if (*format == '%') {
            format++;

            if (!*format) {
                break;
            }

            switch (*format) {
            case 'c': {
                char c = va_arg(ap, int);
                my_putc(c);
                break;
            }
            case 's': {
                char *str = va_arg(ap, char *);
                my_putstr(str);
                break;
            }
            case 'd': {
                int n = va_arg(ap, int);
                my_putint(n);
                break;
            }
            case 'f': {
                float n = va_arg(ap, double);
                my_putf(n);
                break;
            }
            case '%': {
                my_putc('%');
                break;
            }
            default: {
                my_putc('%');
                my_putc(*format);
                break;
            }
            }

        } else {
            my_putc(*format);
        }

        format++;
    }

    va_end(ap);
}

int main() {
    my_printf("%c, %s, int = %d, float = %f\n", 'g', "Hello", 8, 0.0007);
    char *str = "testing printf";
    my_printf("%s, %%, %v", str);
}
