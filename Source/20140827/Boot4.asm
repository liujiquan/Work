;*********************************************
;	Boot1.asm
;		- A Simple Bootloader
;*********************************************

org 0
bits 16

start:
        jmp main
        
;*********************************************
;	BIOS Parameter Block
;*********************************************

; BPB Begins 3 bytes from start. We do a far jump, which is 3 bytes in size.
; If you use a short jump, add a "nop" after it to offset the 3rd byte.

bpbOEM			db "My OS   "			; OEM identifier (Cannot exceed 8 bytes!)
bpbBytesPerSector:  	DW 512
bpbSectorsPerCluster: 	DB 1
bpbReservedSectors: 	DW 1
bpbNumberOfFATs: 	DB 2
bpbRootEntries: 	DW 224
bpbTotalSectors: 	DW 2880
bpbMedia: 		DB 0xf8  ;; 0xF1
bpbSectorsPerFAT: 	DW 9
bpbSectorsPerTrack: 	DW 18
bpbHeadsPerCylinder: 	DW 2
bpbHiddenSectors: 	DD 0
bpbTotalSectorsBig:     DD 0
bsDriveNumber: 	        DB 0
bsUnused: 		DB 0
bsExtBootSignature: 	DB 0x29
bsSerialNumber:	        DD 0xa0a1a2a3   ; will be overwritten
bsVolumeLabel: 	        DB "MOS FLOPPY "
bsFileSystem: 	        DB "FAT12   "

;*********************************************
;	Prints a string
;       DS=>SI: 0 terminated string
;   Changed Register
;       AX, SI
;*********************************************

Print:
        lodsb
        or al, al
        jz PrintDone
        mov ah, 0eh
        int 10h
        jmp Print
PrintDone:
        ret
        
;************************************************;
; Reads a series of sectors
; Input:
;       CX=>Number of sectors to read
;       AX=>Starting sector (logical block addressing)
;       ES:BX=>Buffer to read to
; Changed:
;       DI, SI, AX, CX, BX
;************************************************;

ReadSectors:
    .MAIN:
        mov di, 0x0005          ; five retries for error
    .SECTORLOOP:
        push ax
        push bx
        push cx
        call LBACHS             ; compute absoluteTrack, absoluteSector, absoluteHead
        mov ah, 0x02            ; BIOS read sector
        mov al, 0x01            ; read one sector
        mov ch, BYTE [absoluteTrack]
        mov cl, BYTE [absoluteSector]
        mov dh, BYTE [absoluteHead]
        mov dl, BYTE [bsDriveNumber]
        int 0x13                ; invoke BIOS
        jnc .SUCCESS            ; test for read error. CF=0 then jump
        xor ax, ax              ; BIOS reset disk
        int 0x13
        dec di
        pop cx
        pop bx
        pop ax
        jnz .SECTORLOOP
        int 0x18
    .SUCCESS:
        mov si, msgProgress
        call Print
        pop cx
        pop bx
        pop ax
        add bx, WORD [bpbBytesPerSector]            ; queue next buffer
        inc ax                                      ; queue next sector
        loop .MAIN                                  ; read next sector. Controlled by CX, If CX=0, then stop
        ret
        
;************************************************;
; Convert CHS to LBA
; Input:
;       AX=>the cluster to be changed
; Changed:
;       AX, CX
; Return:
;       AX=>sector number
; LBA = (cluster - 2) * sectors per cluster
;************************************************;

ClusterLBA:
        sub ax, 0x0002                                ; zero base cluster number
        xor cx, cx
        mov cl, BYTE [bpbSectorsPerCluster]           ; convert byte to word
        mul cx
        add ax, WORD [datasector]                     ; base data sector
        ret
        
;************************************************;
; Convert LBA to CHS
; Input:
;       AX=>LBA Address to convert
; Changed:
;       DX, AX
; Return:
;       BYTE [absoluteSector], BYTE [absoluteHead], BYTE [absoluteTrack]
;
; absolute sector = (logical sector % sectors per track) + 1
; absolute head   = (logical sector / sectors per track) MOD number of heads
; absolute track  = logical sector / (sectors per track * number of heads)
;
;************************************************;

LBACHS:
        xor dx, dx          ; prepare dx:ax for operation
        div WORD [bpbSectorsPerTrack]
        inc dl              ; adjust for sector 0
        mov BYTE [absoluteSector], dl
        xor dx, dx
        div WORD [bpbHeadsPerCylinder]
        mov BYTE [absoluteHead], dl
        mov BYTE [absoluteTrack], al
        ret
        
;*********************************************
;	Bootloader Entry Point
;*********************************************

main:
    
    ;-----------------------------------------------------
    ; code located at 0000:7c00, adjust segment registers
    ;-----------------------------------------------------
    
        cli
        mov ax, 0x07c0          ; setup registers to point to our segment. s*16+off = address
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        
    ;-----------------------------------------------------
    ; create stack
    ;-----------------------------------------------------
    
        mov ax, 0x0000          ; set the stack
        mov ss, ax
        mov sp, 0xffff
        sti                     ; restore interrupts
        
    ;-----------------------------------------------------
    ; display loading message
    ;-----------------------------------------------------
    
        mov si, msgLoading      ; "Loading Boot Image "
        call Print
        
    ;-----------------------------------------------------
    ; load root directory table
    ;-----------------------------------------------------
    
    LOAD_ROOT:
    
    ; compute size of root directory and store in "cx"
    
        xor cx, cx                                
        xor dx, dx
        mov ax, 0x0020                            ; 32 bytes directory entry
        mul WORD [bpbRootEntries]                 ; total size of directory. bpbTotalSectors = 2880
        div WORD [bpbBytesPerSector]              ; sectors used by directory. ax is the consult
        xchg ax, cx                               ; now cx is the result, ax is 0x0000
        
    ; compute location of root directory and store in "ax"
    
        mov al, BYTE [bpbNumberOfFATs]
        mul WORD [bpbSectorsPerFAT]
        add ax, WORD[bpbReservedSectors]
        mov WORD [datasector], ax                 ; base of root directory
        add WORD [datasector], cx                 ; ?
        
    ; read root directory into memory (7c00:0200)
    
        mov bx, 0x0200
        call ReadSectors
        
    ;------------------------------------------------
    ; Find stage 2
    ;------------------------------------------------
    
    ; browse root directory for binary image
        
        mov cx, WORD [bpbRootEntries]
        mov di, 0x0200
        
    .LOOP:
        push cx
        mov cx, 0x000b              ; eleven character name
        mov si, ImageName           ; image name to find
        push di
        rep cmpsb                   ; test for entry match
        pop di
        je LOAD_FAT                 ; if found, "DI" is the pointer to ImageName in the Root Directory
        pop cx
        add di, 0x0020              ; queue next directory entry. Each entry in Root Directory is 32 bytes (0x20)
        loop .LOOP                  ; cx = bpbRootEntries, check "cx" times.
        jmp FAILURE
        
    ;----------------------------------------------
    ; load FAT
    ;----------------------------------------------
    
    LOAD_FAT:
    
    ; save starting cluster of boot image
    
        mov si, msgCRLF
        call Print
        mov dx, WORD [di + 0x001a]          ; di contains starting address of entry. Just refrence byte 26 (0x1A) of entry
        mov WORD [cluster], dx              ; file's first cluster
        
    ; compute size of FAT and store in "cx"
    
        xor ax, ax
        mov al, BYTE [bpbNumberOfFATs]
        mul WORD [bpbSectorsPerFAT]
        mov cx, ax
        
    ; compute location of FAT and store in "ax"
    
        mov ax, WORD [bpbReservedSectors]       ; adjust for bootsector
        
    ; read FAT into memory (7c00:0200)
    
        mov bx, 0x0200
        call ReadSectors
        
    ; read image file into memory (0050:0000)
    
        mov si, msgCRLF
        call Print
        mov ax, 0x0050
        mov es, ax
        mov bx, 0x0000
        push bx
        
    ;----------------------------------------------
    ; load stage 2
    ;----------------------------------------------
    
    LOAD_IMAGE:
        
        mov ax, WORD [cluster]              ; cluster to read. File's first cluster
        pop bx                              ; buffer to read into. ES:BX. es=0x0050
        call ClusterLBA                     ; convert cluster to LBA
        xor cx, cx
        mov cl, BYTE [bpbSectorsPerCluster]
        call ReadSectors
        push bx
        
    ; compute next cluster
    
        mov ax, WORD [cluster]          ; identify current cluster
        mov cx, ax                      ; copy current cluster
        mov dx, ax
        shr dx, 0x0001                  ; divide by two
        add cx, dx                      ; sum for (3/2)
        mov bx, 0x0200                  ; location of FAT in memory
        add bx, cx                      ; index into FAT
        mov dx, WORD [bx]               ; read two bytes from FAT
        test ax, 0x0001
        jnz .ODD_CLUSTER
        
    .EVEN_CLUSTER:
    
        and dx, 0000111111111111b       ; take low twelve bits
        jmp .DONE
        
    .ODD_CLUSTER:
    
        shr dx, 0x0004                  ; take high twelve bits
        
    .DONE:
    
        mov WORD [cluster], dx          ; store new cluster
        cmp dx, 0x0ff0                  ; test for end of file
        jb LOAD_IMAGE
        
    DONE:
    
        mov si, msgCRLF
        call Print
        push WORD 0x0050
        push WORD 0x0000
        retf                            ; jmp to 0x0050:0000 to excute (MAY BE)
        
    FAILURE:
    
        mov si, msgFailure
        call Print
        mov ah, 0x00
        int 0x16                ; a wait keypress
        int 0x19                ; warm boot computer
        
    absoluteSector db 0x00
    absoluteHead db 0x00
    absoluteTrack db 0x00
    
    datasector dw 0x0000
    cluster dw 0x0000
    ImageName db "KRNLDR  SYS"
    msgLoading db 0x0d, 0x0a, "Loading Boot Image ", 0x0d, 0x0a, 0x00
    msgCRLF db 0x0d, 0x0a, 0x00
    msgProgress db ".", 0x00
    msgFailure db 0x0d, 0x0a, "ERROR : Press Any Key to Reboot", 0x0a, 0x00
    
        TIMES 510-($-$$) db 0   ; confirm the compiled bin file is 512B
        dw 0xaa55               ; the bootable special character