; Note: Here, we are executed like a normal COM program, but we are still in
; Ring 0. We will use this loader to set up 32 bit mode and basic exception
; handling

; This loaded program will be our 32 bit kernal.

; We do not have the limitation of 512 bytes here, so we can add anything we
; want here!

org 0x0             ; offset to 0, we will set segments later
bits 16             ; we are still in real mode

; we are loaded at linear address 0x10000

jmp main

;*********************************
;   Prints a String
;   DS=>SI: 0 terminated string
;*********************************

Print:
        lodsb
        or al, al
        jz PrintDone
        mov ah, 0eh
        int 10h
        jmp Print
PrintDone:
        ret
        
;********************************
; Second Stage Loader Entry Point
;********************************

main:
        cli
        push cs
        pop ds
        
        mov si, Msg
        call Print
        
        cli
        hlt
        
;********************************
; Data section
;********************************

Msg db "Preparing to load operating system...",13,10,0