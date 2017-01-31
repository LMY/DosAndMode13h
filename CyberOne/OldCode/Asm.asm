assume cs:cyber
cyber segment

start:

xor al,al
mov dx,037ah
out dx,al

mov dx,0378h
mov al,0FFh
out dx,al

mov al,1
mov dx,037ah
out dx,al

mov ah,4ch
int 21h

cyber ends
end start