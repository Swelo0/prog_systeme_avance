.global _read_sector_raw
.global _write_sector_raw

;void _read_sector_raw(unint drive, uint packet_addr)
_read_sector_raw:
	push bp
	mov bp, sp
	mov ah, #0x42
	xor al, al
	mov dx, [bp+4]
	mov si, [bp+6]
	mov bx, ds
	mov [si+6], bx ;fix up the segment
	int #0x13
	pop bp
	ret
	
;void _write_sector_raw(unint drive, uint packet_addr)
_write_sector_raw:
	push bp
	mov bp, sp
	mov ah, #0x43
	xor al, al
	mov dx, [bp+4]
	mov si, [bp+6]
	mov bx, ds
	mov [si+6], bx ;fix up the segment
	int #0x13
	pop bp
	ret
