global mul_es

bits 64
section .text

mul_es:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    push rdi
    ;codigo
    ;carga de datos
    ;Ecx contiene size
    ;eax contiene el 5

    mov rbx,rax
    mov rdi,rdx


;loop
lp:

    mov eax,[rdi]
    ;realizo multiplicacion
    mul ebx
    mov [rdi],eax
    add rdi,4 ;le agrego al rdi el size de un int

    loop lp


    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rbp
    ret
