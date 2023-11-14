#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>

#define BUFF_SIZE 1024
#define UNUSED(x) (void)(x)

int write_pointer(char buffer[], int start, int length, int width, int flags, char padd, char extra_c, int padd_start);

/************************* PRINT POINTER *************************/
int print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char extra_c = 0, padd = ' ';
    int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
    unsigned long num_addrs;
    char map_to[] = "0123456789abcdef";
    void *addrs = va_arg(types, void *);

    UNUSED(width);
    UNUSED(size);

    if (addrs == NULL)
        return sprintf(buffer, "(nil)");

    buffer[BUFF_SIZE - 1] = '\0';
    UNUSED(precision);

    num_addrs = (unsigned long)addrs;

    while (num_addrs > 0) {
        buffer[ind--] = map_to[num_addrs % 16];
        num_addrs /= 16;
        length++;
    }

    if ((flags & 1) && !(flags & 2))
        padd = '0';
    if (flags & 4)
        extra_c = '+', length++;
    else if (flags & 8)
        extra_c = ' ', length++;

    ind++;

    return write_pointer(buffer, ind, length, width, flags, padd, extra_c, padd_start);
}

/************************* PRINT NON PRINTABLE *************************/
int print_non_printable(va_list types, char buffer[], int flags, int width, int precision, int size) {
    int i = 0, offset = 0;
    char *str = va_arg(types, char *);

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        return sprintf(buffer, "(null)");

    while (str[i] != '\0') {
        if (str[i] >= 32 && str[i] < 127)
            buffer[i + offset] = str[i];
        else
            offset += sprintf(buffer + i + offset, "\\x%02x", (unsigned char)str[i]);

        i++;
    }

    buffer[i + offset] = '\0';

    return sprintf(buffer, "%s", buffer);
}

/************************* PRINT REVERSE *************************/
int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char *str;
    int i, count = 0;

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(size);

    str = va_arg(types, char *);

    if (str == NULL) {
        UNUSED(precision);
        str = ")Null(";
    }

    for (i = 0; str[i]; i++)
        ;

    for (i = i - 1; i >= 0; i--) {
        buffer[count++] = str[i];
    }
    buffer[count] = '\0';

    return sprintf(buffer, "%s", buffer);
}

/************************* PRINT A STRING IN ROT13 *************************/
int print_rot13string(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char x;
    char *str;
    unsigned int i, j;
    int count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    str = va_arg(types, char *);

    if (str == NULL)
        str = "(AHYY)";

    for (i = 0; str[i]; i++) {
        for (j = 0; in[j]; j++) {
            if (in[j] == str[i]) {
                x = out[j];
                buffer[count++] = x;
                break;
            }
        }
        if (!in[j]) {
            x = str[i];
            buffer[count++] = x;
        }
    }
    buffer[count] = '\0';

    return sprintf(buffer, "%s", buffer);
}

int write_pointer(char buffer[], int start, int length, int width, int flags, char padd, char extra_c, int padd_start) {
    int count = 0, i;

    if (padd_start)
        for (i = 0; i < width - length; i++)
            buffer[count++] = padd;

    if (flags & 4 || flags & 8)
        buffer[count++] = extra_c;

    for (i = start; i < BUFF_SIZE - 1; i++)
        buffer[count++] = buffer[i];

    return sprintf(buffer, "%s", buffer);
}
