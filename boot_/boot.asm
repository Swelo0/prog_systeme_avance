A_CONSTANT	equ	0x100 ; Constante valant 256 d'une utilité pour le moment obscure
;Code du bootloader
[BITS 16] ; Indique que ce code est en 16 bits
[ORG 0x7c00] ; Indique que le code sera à cet emplacment après avoir été chargé
	
	; setup stack
	
	mov ax, 0x7ff0        	; On positionne la pile looooiiiinnnnn très loooiiiiin
    mov ss, ax				; On avance de 16 bits pour que ss:sp donne bien 16 de large
    mov sp, 0xff			; sp prend la valeur de 4096
    
    ; reset drive
    ; reset:
	;	mov dl, 0x00			; 0x00
	;	int 0x13				; Interruption 13 avec ah = 0 -> reset du disque dur
	;	jc reset				; Si ça merdouille on reset encore et encore jusqu'à ce que mort s'ensuive
		
	; initialize segments
	
	mov ax, 0x1000			; 
	mov es, ax				; On met la valeur 0x1000 pour l'extra segment
	
	; display message
	
	mov ah, 0x0E			; mode teletype
	mov bh, 0x00			; mode page zero
	mov bl, 0x07			; gris léger
	
	mov si, msg 	; On met l'adresse du msg dans le registre de segment de la pile
	
	printMessage:
		mov al, [si]		; On met le pointeur dans AL
		cmp al, 0				; On regarde si AL est vide
		je loadKernel
		int 0x10				; On affiche le caractère à l'écran
		inc si					; On passe au caractère suivant
		jmp printMessage		; On boucle
		
	;load kernel
			
	loadKernel:

		mov ah, 0x42	; On indique que l'interruption 0x13 utilisera la fonction Extended Read (en utlisant un paquet)
		mov si, packet
		int 0x13		; On trigger l'interruption 13, qui prend la valeur ah comme paramètre
		
		mov ax, 0x2000  ;
		mov ds, ax      ; On met le data segment à 0x2000
		
		jmp 0x2000:0x0000
        

	; execute kernel


	msg db "Kernel is loading...",13,10,0
	
	packet:
		size db 0x10 ;
		reserved db 0
		sect_count dw 0xff
		addr_offset dw 0
		addr_segment dw 0x2000
		first_sect dq 0x1

	; fill with nop instructions until offset 510
	times 510-($-$$) db 0x90

	; last 2 bytes of sector: indicate a bootable sector
	dw 0xAA55
