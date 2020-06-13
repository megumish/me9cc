#include <stdio.h>
#include "test_driver.h"

int main(const int argc, const char *const *const argv)
{
    if (argc != 2)
    {
        puts("usage: equal_integer <EXPECTED_OUTPUT_FILE>");
        return -1;
    }

    FILE *const expected_output_file = fopen(argv[1], "r");
    if (!expected_output_file)
    {
        puts("can not open expected output file");
        return -1;
    }

    int expected;
    fscanf(expected_output_file, "%d", &expected);
    int actual = ret_int();
    if (actual == expected)
    {
        return 0;
    }
    else
    {
        printf("expected: %d\n", expected);
        printf("actual: %d\n", actual);
        return -1;
    }
}