org	0100h
segment .data
	message1 	db 	"liujiquan$"			;$ is End
	message2	db	"123$"					;
	message3	db	"liujiquan1$"				;
segment .text
	mov ah, 09h
	;
;	mov dx, message1
;	int 21h
	;
;	mov dx, message2
;	int 21h
	;
	mov ax, message3
	mov bp, ax
	jmp $