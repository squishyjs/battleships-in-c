#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;
typedef uint64_t u64;

void fizzbuzz_1(int n) {
    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0) {
            printf("Fizz\n");
        }
        if (i % 5 == 0) {
            printf("Buzz\n");
        }
        if (i % 15 == 0) {
            printf("FizzBuzz\n");
        }
    }
}

// optimal level
void fizzbuzz_2(int n) {
    typedef struct {
        int divisor;
        const char *word;
    } Rule;

    Rule rules[] = {
        // format: {divisor, word}
        {3, "Fizz"},
        {5, "Buzz"},
        {7, "Pop"}
    };

    int rule_count = sizeof(rules) / sizeof(rules[0]);

    for (int i = 1; i <= n; ++i) {
        int printed = 0;

        for (int r = 0; r < rule_count; ++r) {
            if (i % rules[r].divisor == 0) {
                printf("%s", rules[r].word);
                printed = 1;
            }
        }

        if (!printed) { printf("%d", i); }

        printf("\n");
    }
}

int fizz(int n) { return n % 3 == 0; }
int buzz(int n) { return n % 5 == 0; }

// function pointer rules (ent-level)
void fizzbuzz_3(int n) {
    typedef int (*RuleFn)(int);

    typedef struct {
        RuleFn fn;
        const char *word;
    } Rule;

    Rule rules[] = {
        {fizz, "Fizz"},
        {buzz, "Buzz"}
    };

    int rule_count = sizeof(rules) / sizeof(rules[0]);

    for (int i = 1; i <= n; ++i) {
        int printed = 0;
        for (int r = 0; r < rule_count; r++) {
            if (rules[r].fn(i)) {
                printf("%s", rules[r].word);
                printed = 1;
            }
        }

        if (!printed) { printf("%d", i); }

        printf("\n");
    }
}

int main(void) {
    /*
    Given an integer n, output all the integers divisible by 3
    as "Fizz", 5 as "Buzz", and "FizzBuzz" if both 3 and 5 up
    to n
    */
    int n;
    scanf("%d", &n);

    // -----------
    printf("Executing Fizz Buzz Func 1\n");
    fizzbuzz_1(n);
    // -----------
    printf("Executing Fizz Buzz Func 2\n");
    fizzbuzz_2(n);
    // -----------
    printf("Executing Fizz Buzz Func 3\n");
    fizzbuzz_3(n);
    // -----------

    return EXIT_SUCCESS;
}
