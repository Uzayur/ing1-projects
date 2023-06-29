    .glovl my_add
    .type my_add, @function

my_add:
    leal    (%rdi, %rsi), %eax
    ret
