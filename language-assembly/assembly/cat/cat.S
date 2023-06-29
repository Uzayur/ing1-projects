    .global main

    .text
main:
    cmp $2, %rdi
    jne bad_args

    #open
    mov 8(%rsi), %rdi
    mov $0, %rsi
    xor %rdx, %rdx
    mov $0, %rdx
    call open

    #the file doesn't exist
    cmp $63, %rax
    jg no_file

    #to save the file descriptor
    mov %rax, %r8

    jmp loop

loop:
    #read
    mov %r8, %rdi
    mov $buff, %rsi
    mov $32, %rdx
    call read

    #write
    mov $1, %rdi
    mov $buff, %rsi
    mov %rax, %rdx
    call write

    cmp $32, %rax
    je loop


nice_finish:
    mov %r8, %rdi
    call close

    mov $0, %rax
    ret

bad_args:
    mov $1, %rax
    ret

no_file:
    mov $2, %rax
    ret


    .comm buff, 32, 0
