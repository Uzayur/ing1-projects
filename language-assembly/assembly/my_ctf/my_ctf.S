    .text

    .global extract

extract:
    mov     %rbp, %rsi
    sub     $8, %rsi
    sub     %rax, %rax
    movq    $1, %rax
    movq    $1, %rdi
    movq    $8, %rdx

    syscall
    ret
