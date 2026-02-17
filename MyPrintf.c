#include <stdarg.h>  //variadic arguments
#include <unistd.h>  //system calls

//write(1=STDOUT, &c = pointer to the value to print, 1 = number of bytes (1 char))
void my_putc(char c) { write(1, &c, 1); }

void my_putstr(const char *str) {
    if (!str) str = "(null)"; 
    while (*str) {
        my_putc(*str);
        str++;
    }
}

void my_putint(int num) {
    long n = num;  //long to ensure there is no MIN_INT overflow

    if (n < 0) {
        my_putc('-');
        n *= -1;  //converting to positive
    }

    if (n >= 10) {
        my_putint(n / 10);  //recursive step to print digits in right order
    }
    my_putc((n % 10) + '0');  //getting each digit, and also converting to char
}

void my_putf(float n) {
    int precision = 6;  //number of digits after '.'

    if (n < 0) {
        my_putc('-');
        n *= -1;
    }

    //separating before and after comma
    int intpart = (int)n;
    float floatpart = n - intpart;

    my_putint(intpart);  
    my_putc('.');

    //loop to print each digit after comma
    for (int i = 0; i < precision; i++) {
        floatpart *= 10;
        my_putint((int)floatpart);
        floatpart = floatpart - (int)floatpart;
    }
}

void my_printf(const char *format, ...) {
    va_list ap;  //object to hold the information needed to retrieve additional arguments
    va_start(ap, format);  //initializes 'ap' to point to the first argument after 'format'

    while (*format) {
        if (*format == '%') {
            format++;  //looking at the character after '%'

            if (!*format) {
                break;
            }

            switch (*format) {
            case 'c': {
                char c = va_arg(ap, int);  //fetch an int from arguments
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
                // %% should print %
                my_putc('%');
                break;
            }
            default: {
                //for example: %j should print exactly %j, not just j
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

    va_end(ap);  //cleans up the variadic argument list before the function returns
}

int main() {
    my_printf("%c, %s, int = %d, float = %f\n", 'g', "Hello", 8, 0.0007);
    char *str = "testing printf";
    my_printf("%s, %%, %v", str);
}
