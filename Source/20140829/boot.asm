%include "pm.inc"
;%define BOOT_DEBUG
%ifdef BOOT_DEBUG
	org 0100h
%else
	org	07c00h
%endif
	jmp LABEL_BEGIN
;[SECTION .gdt] Begin
[SECTION .gdt]
	;GDT Begin
	LABEL_GDT:
		Descr	0, 0, 0	
	LABEL_DESC_CODE32:
		Descr 0, SegCode32Len-1, DA_C+DA_32
	LABEL_DESC_VIDEO:
		Descr 0B8000h, 0FFFFh, DA_RAW
	;GDT END.

GDTLen	equ $-LABEL_GDT		; GDT Len
GDTPtr  dw  GDTLen			; GDT Limit
		dd  0				; GDT baseAddress
	
;GDT Selector
SelectorCode32	equ	LABEL_DESC_CODE32-LABEL_GDT
SelectorVideo		equ LABEL_DESC_VIDEO-LABEL_GDT
;[SECTION .gdt] End

[SECTION .s16]
[BITS	16]
LABEL_BEGIN:
	mov	ax, cs
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	sp, 0100h

	xor	eax, eax
	mov	ax, cs
	shl	eax, 4
	add	eax, LABEL_SEG_CODE32
	mov	word [LABEL_DESC_CODE32 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_CODE32 + 4], al
	mov	byte [LABEL_DESC_CODE32 + 7], ah

	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_GDT		
	mov	dword [GDTPtr + 2], eax	

	lgdt	[GDTPtr]

	cli

	in	al, 92h
	or	al, 00000010b
	out	92h, al

	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax

	jmp	dword SelectorCode32:0	
; END of [SECTION .s16]


[SECTION .s32]
[BITS	32]

LABEL_SEG_CODE32:
	mov	ax, SelectorVideo
	mov	gs, ax			
	mov	edi, (80 * 10 + 0) * 2
	mov	ah, 0Ch			
	mov	al, 'P'
	mov	[gs:edi], ax

	; µ½´ËÍ£Ö¹
	jmp	$

SegCode32Len	equ	$ - LABEL_SEG_CODE32
; END of [SECTION .s32]
