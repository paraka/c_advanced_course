/**
 * @file function_pointers.c: This file shows a sample of
 * how to use function pointers trying to make them to do
 * something *useful*. Here we are supposing here that we
 * have different stages where we need to execute some stuff
 * in each one as follows:
 *  - setup the stage
 *  - run whatever in the stage
 *  - teardown the stage
 *
 * For the purpose of the sample we will use 3 stages.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

enum
{
    STAGE_0      = 0,
    STAGE_1,
    STAGE_2,
    __MAX_FN, /* always the last */
};

enum
{
    SETUP       = 0,
    RUN,
    TEARDOWN,
};

static void setup(uint8_t val) 
{
    printf("\t* %s%u\n", __func__, val);
}

static void run(uint8_t val) 
{
    printf("\t* %s%u\n", __func__, val);
}

static void teardown(uint8_t val)
{
    printf("\t* %s%u\n", __func__, val);
}

#define FN_ADD(_idx, _fn0, _fn1, _fn2)  \
    [_idx] = {                          \
            [SETUP]     = _fn0,         \
            [RUN]       = _fn1,         \
            [TEARDOWN]  = _fn2,         \
    }                                   \

/**
 * @brief do_sample
 *
 * We are using a type definition to make a little
 * easier the function pointer definition. We are
 * defining and array of __MAX_FN of const pointers
 * to functions which return nothing and expect an
 * uint8_t parameter (each element of the array will be
 * an stage). Then we expect to have three functions for
 * each stage so we use dummy functions to complete the
 * static initialization using the provided helper macro
 * FN_ADD.
 *
 * We only make a dummy for loop showing the executed stuff.
 *
 * To note here:
 *  - The usage of an internal const static "jump table" for the
 *    stages and its functions.
 *  - The usage of a read only pointer to functions in the type
 *    definition.
 */
static void do_sample(void)
{
    uint8_t stage, fn;

    typedef void (* const fn_t[__MAX_FN])(uint8_t val);

    static const fn_t array[] = {
        FN_ADD(STAGE_0, setup, run, teardown),
        FN_ADD(STAGE_1, setup, run, teardown),
        FN_ADD(STAGE_2, setup, run, teardown)
    };

    for (stage = STAGE_0; stage < __MAX_FN; stage++) {
        printf("Executing stage %u fn's...\n", stage);
        for (fn = 0; fn < ARRAY_SIZE(array[stage]); fn++)
            (*array[stage][fn])(stage);
    }
}

int main(void)
{
    do_sample();
    
    return 0;
}
