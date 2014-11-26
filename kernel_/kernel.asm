;Code du Kernel
[BITS 16]				; mets nasm en mode 16 bits
	
	mov ah, 0x0E			; mode teletype
	mov bh, 0x01			; mode page un
	mov bl, 0x07			; gris léger
	
	mov si, msg 	; On met l'adresse du msg dans le registre de segment de la pile
	
	printMessage:
		mov al, [si]			; On met le pointeur dans AL
		or al, al				; On regarde si AL est vide
		jz fin
		int 0x10				; On affiche le caractère à l'écran
		inc si					; On passe au caractère suivant
		jmp printMessage			; On boucle
		
	fin:
		jmp fin
	
	msg db "Je suis un gentil kernel, car figurez-vous, je suis en train de fonctionner!!",13,10,0

	
