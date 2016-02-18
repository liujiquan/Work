org	07c00h	
bits 16

jmp main	;
;*********************************
;   Prints a String
;   DS=>SI: 0 terminated string
;*********************************
Print:
	lodsb
	or  al, al
	jz 	PrintEnd
	mov	ah, 0eh
	int 10h
	jmp Print
PrintEnd:		; print End
	ret	
	
main:
	cli			;close interuppt 
;    push cs
;    pop ds
    
    mov si, BootMessage
    call Print
    
    cli
 ;   hlt			; Stop EveryThing
    jmp	$	    	; wuxian xunhuan
;********************************
; Data section
;********************************
;Msg db "First os by liujiquan.....................",13,10,0
BootMessage:		db	"First os by liujiquan....................."
