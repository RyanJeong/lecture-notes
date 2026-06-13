void foo(void)
{
    auto int x = 1;     /* same as: int x = 1; */
    register int y = 2; /* can be stored in a register for faster access, but
                           this is just a hint to the compiler */
}

static int global_var =
    0; /* This variable is only visible within this translation unit (file) */