bits 32
call func0
    db 'user32.dll',0
func0 :
    mov eax,7C801D78H   ;LOADLIBRARY
    CALL eax
    push 0
    call Func1
    db "Infomation",0
Func1:
    call Func2
    db "This exe was Injected Code.",0
Func2:
    push 0  
    mov eax,77D507EAH  ; 77D507EAH  MESSAGEBOXA
    call eax
    mov eax,00401f50H  ;  01012475H  
    jmp eax