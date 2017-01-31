   .MODEL SMALL   ; Data segment < 64K, code segment < 64K
   .STACK 200H    ; Set up 512 bytes of stack space
   .386
  .DATA
BufferX   EQU 320                       ; Width of screen buffer
BufferY   EQU 105                       ; Height of screen buffer
Buffer    DB BufferX * BufferY DUP (?) ; The screen buffer

Seed      DW 5419h
ALLDONE db"Program ripped and improved by LMY'97$"
INCLUDE PALETTE.DAT
   .CODE

Start:
   MOV   AX, @DATA
   MOV   DS, AX

   push 0a000h
   pop es

   mov ax,13h
   INT   10H                           ; We are now in 320x200x256

   MOV   SI, OFFSET Palette            ; SI now points to the palette
   MOV   CX, 768                       ; Prepare for 768 OUTs
   MOV   DX, 03C8H                     ; Palette WRITE register
   XOR   AL, AL                        ; Start at color 0
   OUT   DX, AL                        ; Send value
   INC   DX                            ; Now use palette DATA register
   REP   OUTSB                         ; 768 multiple OUTs

MainLoop:
   MOV   CX, 32960 
   MOV   SI, OFFSET Buffer + 320

Alter:
   XOR   AX, AX                        ; Zero out AX
   MOV   AL, DS:[SI]                   ; Get the value of the current pixel
   ADD   AL, DS:[SI+1]                 ; Get the value of pixel to the right
   ADC   AH, 0
   ADD   AL, DS:[SI-1]                 ; Get the value of pixel to the left
   ADC   AH, 0
   ADD   AL, DS:[SI+320]
   ADC   AH, 0
   SHR   AX, 2                         ; Divide the total by four

   JZ    NextPixel                     ; Is the result zero?
   DEC   AX                            ; No, so decrement it by one

NextPixel:
   MOV   DS:[SI-320], AL
   INC   SI                            ; Next pixel
   DEC   CX                            ; One less to do
   JNZ   Alter                         ; Have we done them all?

   MOV   SI, OFFSET Buffer + 32960
   MOV   CX, 640

BottomLine:
   MOV   AX, Seed                     ; Move the seed value into AX
   MOV   DX, 8405H                    ; Move 8405H into DX
   MUL   DX                           ; Put 8405H x Seed into DX:AX
   INC   AX                           ; Increment AX
   MOV   Seed, AX                     ; We have a new seed
   MOV   DS:[SI], DL                  ; Use only the low byte of DX - ie,
   INC   SI                           ; the number will be 0 --> 255
   DEC   CX                           ; One less pixel to do
   JNZ   BottomLine                   ; Are we done yet?

   MOV   SI, OFFSET Buffer             ; Point SI to the start of the buffer
   XOR   DI, DI                        ; Start drawing at 0, 0
   MOV   BX, 100

Row:
   MOV   CX, BufferX SHR 1             ; 160 WORDS
   REP   MOVSW                         ; Move them
   SUB   SI, 320                       ; Go back to the start of the array row
   MOV   CX, BufferX SHR 1             ; 160 WORDS
   REP   MOVSW                         ; Move them
   DEC   BX                            ; Decrease the number of VGA rows left
   JNZ   Row                           ; Are we finished?

   MOV   AH, 01H                       ; Check for keypress
   INT   16H                           ; Is a key waiting in the buffer?
   JZ    MainLoop                      ; No, keep on going

   MOV   AH, 00H                       ; Yes, so get the key
   INT   16H

   mov ax,3
   INT   10H                           ; Enter 80x25x16 mode

   MOV   DX, OFFSET AllDone            ; DS:DX points to the ending message
   MOV   AH, 09H
   INT   21H                           ; Display the ending message
   mov ax,4c00h
   INT   21H                           ; Return to DOS
END Start
