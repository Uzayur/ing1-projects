    .text
    .global reverse_print

reverse_print:
    pushq %rbp
    pushq %rbx

    movq %rdi, %rbx
    subq $8, %rsp

    call strlen
    subl $1, %eax
    js .exit

    movslq %eax, %rdi
    addq %rdi, %rbx
    subl %ebx, %eax
    movl %eax, %ebp

.loop:
    movsbl (%rbx), %edi
    subq $1, %rbx
    call putchar
    movl %ebp, %eax
    addl %ebx, %eax
    jns .loop

.exit:
    addq $8, %rsp

    popq %rbx
    popq %rbp

    ret
