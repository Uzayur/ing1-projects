    .globl	my_strcpy

    .text

my_strcpy:

    movzbl (%rsi), %edx
    movq %rdi, %r8
    testb %dl, %dl
    je .exit

    xorl %ecx, %ecx
    xorl %eax, %eax

.loop:
    addl $1, %ecx

    movb %dl, (%r8,%rax)
    movslq %ecx, %rax
    movzbl (%rsi,%rax), %edx
    testb %dl, %dl
    jne .loop
    addq %r8, %rax
    movb $0, (%rax)
    movq %r8, %rax
    ret

.exit:
    movq %rdi, %rax
    movb $0, (%rax)
    movq %r8, %rax
    ret
