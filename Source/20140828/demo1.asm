;%define BOOT_DEBUG
;%ifdef BOOT_DEBUG
;	org 0100h
;%else
;	org	07c00h
;%endif
	
;bits 16

jmp main
Print:
	lodsb
;	or  al, al
	cmp al, 0
	jz 	PrintEnd
	mov	ah, 0eh
	int 10h
	jmp Print
PrintEnd:		; print End
	ret				; 
DispStr:
	mov	ax, BootMessage1
	mov	bp, ax			; 
	mov	cx, 42			; 
	mov	ax, 01301h		; 
	mov	bx, 000ch		; 
	mov	dl, 0
	int	10h			
	ret	
main:
	mov	ax, cs
	mov	ds, ax
	mov	es, ax
	MOV AX,0003H	;	Clear Screen
	INT 10H			;	Clear Screen

;	mov si, BootMessage1
;	call	Print
	call	DispStr			
	jmp	$
;********************************
; Data section
;********************************
BootMessage1:		db	"This Is a Operation System."
BootMessage2:		db	"Author  : Liujiquan."
BootMessage3:		db	"Datetime: 2014/08/29 13:15."
BootMessage4:		db	"Address : Amano."