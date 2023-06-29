    .global my_pow
    .string "%d\n"
    .text

my_pow:
    leal    1(%rdi), %ecx
    mov    $1, %ebx

    push    %rax
    push    %rbx
    push    %rcx

    lea    message(%rip), %rdi
    mov    %ebx, %esi
    mov    $0, %rax
    call    printf

    pop    %rc
    pop    %rbx
    pop    %rax

    jmp    boucle

boucle:
    decl    %ecx
    je     exit
    add    %ebx, %ebx

    push    %rax
    push    %rbx
    push    %rcx

    lea	    message(%rip), %rdi
    mov	    %ebx, %esi
    mov	    $0, %rax
    call    printf

    pop	    %rcx
    pop	    %rbx
    pop	    %rax

    jmp	    boucle

message: .asciz "%d\n"

exit:
    ret


