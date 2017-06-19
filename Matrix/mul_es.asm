global mul_es		;Nombre que tendrá la funcion
					;tambien en C++

bits 64				;64 bits
section .text		

mul_es:
    push rbp		;FIFO
    mov rbp, rsp	;Para usar parametros por la pila
    push rbx		;FIFO
    push rcx		;FIFO
    push rdx		;FIFO
    push rdi		;FIFO

    mov rbx,rax		;Registros a usar
    mov rdi,rdx
					;loop principal
lp:
    mov eax,[rdi]	;Corrida del puntero, para conseguir el dato 
					;con el cual se trabajará
    mul ebx			;Realizo la multiplicacion
    mov [rdi],eax	;Muevo el resultado de la multiplicacion
					;al espacio de memoria inicial de rdi
    add rdi,4 		;le agrego al rdi el size de un int

    loop lp			;Condicion del loop

    pop rdi			;FIFO
    pop rdx			;FIFO
    pop rcx			;FIFO
    pop rbx			;FIFO	
    pop rbp			;FIFO
    ret				;Regreso donde fue llamada la funcion mul_es.asm
