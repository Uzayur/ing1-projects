    .text

    .globl my_strchr

my_strchr:
    pushq %rbp

    movq %rsp, %rbp
    movq %rdi, -24(%rbp)

    movl %esi, -28(%rbp)
    movb $0, -1(%rbp)

    jmp .jump1

.loop:
    movsbq -1(%rbp), %rdx
    movq -24(%rbp), %rax

    addq %rdx, %rax
    movzbl (%rax), %eax
    movsbl %al, %eax

    cmpl %eax, -28(%rbp)
    jne .jump2
    movsbq -1(%rbp), %rdx
    movq -24(%rbp), %rax

    addq %rdx, %rax
    jmp .exit

.jump2:
    movzbl -1(%rbp), %eax
    addl $1, %eax
    movb %al, -1(%rbp)

.jump1:
    movsbq -1(%rbp), %rdx
    movq -24(%rbp), %rax

    addq %rdx, %rax
    movzbl (%rax), %eax

    testb %al, %al
    jne .loop

    movl $0, %eax

.exit:
    popq %rbp
    ret
