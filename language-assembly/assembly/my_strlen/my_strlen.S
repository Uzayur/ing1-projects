    .global my_strlen
    .text

my_strlen:
    xorl %eax, %eax
    cmpb $0, (%rdi)
    je .jump4

.jump3:
    addq $1, %rax
    cmpb $0, (%rdi,%rax)
    jne .jump3
    ret

.jump4:
    ret
