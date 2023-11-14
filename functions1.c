#include <stdarg.h>
#include <stdio.h>

/************************* COMMON FUNCTION DECLARATIONS *************************/
int print_unsigned(unsigned long int num, char buffer[], int flags, int width);
int print_octal(unsigned long int num, char buffer[], int flags, int width);
int print_hexadecimal(unsigned long int num, char map_to[], char buffer[], int flags, char flag_ch, int width);

/************************* PRINT UNSIGNED NUMBER *************************/
int print_unsigned(unsigned long int num, char buffer[], int flags, int width) {
    int i = BUFF_SIZE - 2;

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    while (num > 0) {
        buffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (write_unsgnd(0, i, buffer, flags, width, -1, -1));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
int print_octal(unsigned long int num, char buffer[], int flags, int width) {
    int i = BUFF_SIZE - 2;

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    while (num > 0) {
        buffer[i--] = (num % 8) + '0';
        num /= 8;
    }

    if (flags & F_HASH)
        buffer[i--] = '0';

    i++;

    return (write_unsgnd(0, i, buffer, flags, width, -1, -1));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
int print_hexadecimal(unsigned long int num, char map_to[], char buffer[], int flags, char flag_ch, int width) {
    int i = BUFF_SIZE - 2;

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    while (num > 0) {
        buffer[i--] = map_to[num % 16];
        num /= 16;
    }

    if (flags & F_HASH) {
        buffer[i--] = flag_ch;
        buffer[i--] = '0';
    }

    i++;

    return (write_unsgnd(0, i, buffer, flags, width, -1, -1));
}

/************************* PRINT UNSIGNED NUMBER *************************/
int print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size) {
    unsigned long int num = va_arg(types, unsigned long int);
    return print_unsigned(num, buffer, flags, width);
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size) {
    unsigned long int num = va_arg(types, unsigned long int);
    return print_octal(num, buffer, flags, width);
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
int print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size) {
    unsigned long int num = va_arg(types, unsigned long int);
    return print_hexadecimal(num, "0123456789abcdef", buffer, flags, 'x', width);
}

