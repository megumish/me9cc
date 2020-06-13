#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char *const *const argv)
{
    if (argc != 4)
    {
        puts("usage: megcc <INPUT_FILE> <OUTPUT_FILE> <ENTRY_POINT>");
        return -1;
    }

    FILE *const input_file = fopen(argv[1], "r");
    if (!input_file)
    {
        puts("can not open input file");
        return -1;
    }
    FILE *const output_file = fopen(argv[2], "w");
    if (!output_file)
    {
        puts("can not open input file");
        return -1;
    }

    fprintf(output_file, ".intel_syntax noprefix\n");
    fprintf(output_file, ".global %s\n", argv[3]);
    fprintf(output_file, "%s:\n", argv[3]);
    {
        int input_int;
        fscanf(input_file, "%d", &input_int);
        fprintf(output_file, "  mov rax, %d\n", input_int);
    }

    char operator;
    while (fscanf(input_file, "%c", &operator) != -1)
    {
        if (operator== '+')
        {
            int input_int;
            fscanf(input_file, "%d", &input_int);
            fprintf(output_file, "  add rax, %d\n", input_int);
            continue;
        }

        if (operator== '-')
        {
            int input_int;
            fscanf(input_file, "%d", &input_int);
            fprintf(output_file, "  sub rax, %d\n", input_int);
            continue;
        }

        printf("invalid operator: %c", operator);
    }
    fprintf(output_file, "  ret\n");
    return 0;
}
