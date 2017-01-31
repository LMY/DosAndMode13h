.model  small
.code
ORG     100H
start:          JMP     begin


;*** VARIABILI ***
msb     EQU     0000H          ;la prima parte dell'offset
lsb     EQU     055AH          ;la seconda parte dell'offset
cnt     EQU     3H             ;numero di bytes della patch
patch_data      DB 'EB2E90',0  ;la stringa da scrivere
file_name       DB '********.***',0     ;nome del file da crackare

logo            DB 'Cracked by Lord Mayrus',0AH,0DH
                DB '   <<<LMY'97>>>   ',0AH,0DH

error1          DB 'FILE NOT FOUND',0AH,0DH
                DB 'Make sure you have CRACK.COM in the same',0AH,0DH
                DB 'directory as ********.***',0AH,0DH
		DB '$'
		
error2          DB 'A fatal error has occured',0AH,0DH
                DB 'the crack was not applied',0AH,0DH
		DB '$'
		
error3          DB '********.*** has the read only attribute set',0AH,0DH
		DB 'reset it before attempting to make the patch',0AH,0DH
		DB '$'
		
handle          DW 0

;******************************************************************************
;       this procedure opens the file to be cracked
;******************************************************************************

open_it         PROC    near
                MOV     DX,offset file_name     ;setup to open file to be
                MOV     AX,3D02H                ;cracked
		INT     21H
                JNC     done                    ;if successful, continue

		CMP     AX,05H
                JZ      read_only
                MOV     AH,09H                  ;else display error message
                MOV     DX,offset error1        ;and exit
		INT     21H
                JMP     exit
read_only:      MOV     AH,09H
                MOV     DX,offset error3
		INT     21H
                JMP     exit
		
done:           MOV     handle,AX               ;store the file handle for
                RET                             ;use later and return
open_it         ENDP

;******************************************************************************
;       this procedure sets the file pointer to the patch location
;******************************************************************************

move_it         PROC    near
                MOV     AH,42H                  ;setup to move the file
                MOV     AL,00H                  ;pointer to the patch site
                MOV     BX,handle               ;load the file handle
                MOV     CX,msb                  ;the first part of offset
                MOV     DX,lsb                  ;and the second part
                INT     21H                     ;move the pointer
                JNC     ok                      ;if successful, continue

		MOV     AH,09H
                MOV     DX,offset error2
                INT     21H                     ;else print error message and
                JMP     exit                    ;exit
ok:             RET
move_it         ENDP

;******************************************************************************
;       this procedure writes the crack to the file and closes it
;******************************************************************************

patch_it        PROC    near
                MOV     AH,40H                  ;setup to write the crack
                MOV     BX,handle               ;load file handle
                MOV     CX,cnt                  ;load number of bytes to write
                MOV     DX,offset patch_data    ;point DX to patch data
                INT     21H                     ;make the patch

                JNC     close_it                ;if successful, contintue
		MOV     AH,3EH
		INT     21H
                MOV     AH,09H                  ;if not then something
                MOV     DX,offset error2        ;is wrong, disk may be write
                INT     21H                     ;protected. If so, print error
                JMP     exit                    ;message and exit
	    
close_it:       MOV     AH,3EH                  ;crack was successful
                INT     21H                     ;close file and return
		RET
patch_it        ENDP

;******************************************************************************
;       the main program
;******************************************************************************

begin           PROC    near
                CALL    open_it                 ;open file to be patched
                CALL    move_it                 ;move pointer to patch site
                CALL    patch_it                ;make the patch and close file
                MOV     AH,09H
                MOV     DX,offset logo          ;display logo
		INT     21H

exit:           MOV     AX,4C00H                ;and exit
		INT     21H
begin           ENDP

		END     START                
