#include <stdarg.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)

/************************* PRINT UNSIGNED DECIMAL *************************/
int print_unsigned_decimal(va_list types) {
    unsigned int num = va_arg(types, unsigned int);
    return printf("%u", num);
}

/************************* PRINT OCTAL *************************/
int print_octal(va_list types) {
    unsigned int num = va_arg(types, unsigned int);
    return printf("%o", num);
}

/************************* PRINT LOWERCASE HEXADECIMAL *************************/
int print_hexadecimal_lower(va_list types) {
    unsigned int num = va_arg(types, unsigned int);
    return printf("%x", num);
}

/************************* PRINT UPPERCASE HEXADECIMAL *************************/
int print_hexadecimal_upper(va_list types) {
    unsigned int num = va_arg(types, unsigned int);
    return printf("%X", num);
}

/************************* PRINT POINTER *************************/
int print_pointer(va_list types) {
    void *ptr = va_arg(types, void *);
    return printf("%p", ptr);
}

/************************* MAIN FUNCTION *************************/
int main() {
    printf("Unsigned Decimal: %u\n", print_unsigned_decimal((va_list)5));
    printf("Octal: %o\n", print_octal((va_list)8));
    printf("Lowercase Hexadecimal: %x\n", print_hexadecimal_lower((va_list)15));
    printf("Uppercase Hexadecimal: %X\n", print_hexadecimal_upper((va_list)15));
    printf("Pointer: %p\n", print_pointer((va_list)NULL));

    return 0;
}
