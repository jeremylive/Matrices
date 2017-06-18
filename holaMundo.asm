;nasm -f elf holaMundo.asm
;ld -m elf_i386 holaMundo.o io.o -o run && ./run
%include "io.mac"

section .data
    name: db "0.m",0	     ;prueba
    len: dq 100		      	 ;largo de bytes a leer
    x: dq 0			     	 ;m
	y: dq 0			     	 ;n
	largo_celda: dq 0	 	 ;largo de la celda
	largo: dq 0			  	 ;largo del fichero .txt 
	escalar: dq 2		   	 ;escalar
	direccion_celda: dq 0 	 ;N_celda * T_celda + 9 = direccion_celda 
	numero_celda: dq 0	 	 ;numera de celda por el que se va corriendo
	resultado: dq 0	     	 ;memoria donde se almacena la matriz resultante
    buffer: times 1024 db 0  ;Fichero con el que se trabaja
    result: dq 0
    
section .bss
	;buffer:	resb 1024
section .text
	global _start            ; global entry point export for ld

_start:
	;Abro el fichero
    mov eax, 5        ; sys_write syscall
    mov ebx, name     ; stdout
    mov ecx, 0102o    ; message address
    mov edx, 0606o    ; message string length
    int 80h

	;intruccion que cargar del archivo al buffer
	mov eax, 3
	mov ebx, eax
	mov ecx, buffer ;memoria donde se dejaran los caracteres obtenidos
	mov edx, len	;# maximo de caracteres a leer
	int 80h 

	;Agarro los primeros 9 bits de entra-------------------------------
	;primeros 4 son (x) 
	xor eax, eax			;clean register
	xor ecx, ecx
	xor ebx, ebx
	xor edx, edx
	
	mov ebx, 256			;Numero para poderme desplazar
	mov cl, [buffer]		
	add eax, ecx
	mul ebx
	
	mov cl, [buffer + 1]
	add eax, ecx
	mul ebx

	mov cl,[buffer + 2]
	add eax, ecx
	mul ebx

	mov cl,[buffer + 3]
	add eax, ecx

	mov [x], eax
	PutLInt eax
	
	xor eax, eax			;clean register
	xor ecx, ecx
	xor ebx, ebx
	xor edx, edx
	
	;siguientes 4 son (y)
	mov ebx, 256			;Numero para poderme desplazar
	mov cl, [buffer + 4]
	add eax, ecx
	mul ebx
	
	mov cl, [buffer + 5]
	add eax, ecx
	mul ebx

	mov cl,[buffer + 6]
	add eax, ecx
	mul ebx

	mov cl,[buffer + 7]
	add eax, ecx

	mov [y], eax
	PutLInt eax
	
	;ultimos 4 bits(primera linea), largo de celda
	xor ecx, ecx
	xor ebx, ebx
	
	mov ebx, 256
	mov cl, [buffer + 8]

	mov [largo_celda],cl
	PutLInt ecx					
	nwln
	
	;Obtengo el largo total del fichero---------------------------------
	xor eax, eax			;clean register
	xor ecx, ecx
	xor ebx, ebx
	xor edx, edx
	
	mov eax, [x]			
	mov ebx, [y]			
	mul ebx 
	mov [largo], eax
	
	;recorro la matriz--------------------------------------------------
	mov ecx, [largo]		;inicializo contador igual al largo del fichero, loop principal
	
corrida_matriz:
	mov ebx,ecx      				;actualizo numero de celda
	mov [numero_celda], ebx 		;inicializo el numero de celda 
	call matriz 					;llamo al proc, numero de celda, tamño de celda, escalar
	loop corrida_matriz				;LOOP principal
	
	;cierro fichero
	mov eax, 6
	int 80h
	
	;cierro programa
    mov eax, 1        ; sys_exit syscall
    mov ebx, 0        ; return 0 (success)
    int 80h


;Proc, Algoritmo de escalar por una matriz
matriz:
	push eax
	push ebx
	push ecx
	push edx

	xor eax, eax		;clean register
	xor ecx, ecx
	xor ebx, ebx
	xor edx, edx

	;Datos a usar
	mov eax, [numero_celda] ;numero de celda
	mov ecx, [largo_celda]  ;tamaño de celda
	dec eax					;configuro para q este en el lugar correcto
	;Calculo de la variable direccion celda. N_celda*T_celda+9
	mul ecx						
	add eax, 9
	mov [direccion_celda], eax
	
	push ecx		;guardo contador, largo de la celda
	
	;----leo el fichero------------------
	mov eax, 19					;sys_lseek
	mov ebx, 1					;unsigned int
	mov ecx, [direccion_celda]	;off_t
	mov edx, 0					;unsigned int
	int 80h						;call kernel
	
	mov eax, 3					;READ, intruccion que cargar del archivo al buffer
	mov ebx, eax				    ;0:read, 1:write,2:R/W
	mov ecx, buffer 			;memoria donde se dejaran los caracteres obtenidos
	mov edx, [largo_celda]		;# maximo de caracteres a leer
	int 80h 					;call kernel

	xor eax, eax				;clean register
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	
								
matriz_result:		
	;EJM: 34bytes
	;mov edx, [numero_celda]		;25-0
	;mov ebx, [direccion_celda]		;33-9
	
	mov cl, [buffer]		
	
	push ecx
	PutLInt edx
	PutCh " "
	pop ecx
	
	add eax, ecx			;Obtengo value

	pop ecx					;recupero contador
	mov ebx, 1				;condicion de parada
	cmp ebx, ecx			;caso base, si T_celda = 0
	jle no_multiplica		;salta si es menor igual
	
	mov ebx, 256			;Numero para poderme desplazar
	mul ebx					;multiplico, para obtener el resultado en eax
		
no_multiplica:	
	;en el eax, tengo el numero con el cual tengo que multiplicar por el escalar
	push ecx
	xor ecx,ecx
	mov ecx, [escalar]		;multiplico por el escalar
	mul ecx					
	pop ecx

	;PutLInt eax		
	;nwln

	loop matriz_result			;ciclo
	
	push eax					;guarado resultado 

	;Escribimos la matriz en un fichero
	mov eax, 19					;sys_lseek
	mov ebx, 0					;unsigned int
	mov ecx, [direccion_celda]	;off_t
	mov edx, 0					;unsigned int
	int 80h		
	
	;Logica para escribir en el archivo
	;Escribirlo en fichero, el # multiplicado
	;write
	mov eax, 4
	mov ebx, 1
	mov ecx, resultado
	mov edx, [largo_celda]
	int 80h
	
	;
	
	xor ecx, ecx				;clean register
	xor ebx, ebx
	xor edx, edx
	
	pop eax						;Obtengo resultado
	
	;Obtengo registro antiguos, para regresar de donde veniamos
	pop edx
	pop ecx
	pop ebx
	pop eax	
	ret
