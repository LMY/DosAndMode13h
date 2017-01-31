#include <dos.h>

void ResetDSP(unsigned int BasePort);
void WriteDSP(unsigned int BasePort, unsigned char Byte);
unsigned char ReadDSP(unsigned int BasePort);
void SpeakerOn(unsigned int BasePort);
void SpeakerOff(unsigned int BasePort);
void DMAstop(unsigned int BasePort);
void DMAcontinue(unsigned int BasePort);
void SetFreq(unsigned int BasePort, unsigned int Freq);
void WriteDAC(unsigned int BasePort,unsigned char Level);
unsigned char ReadDAC(unsigned int BasePort);
void Play(unsigned int BasePort, unsigned char far *Pointer, unsigned int Size, unsigned int Freq);

void ResetDSP(unsigned int BasePort)
{
	asm {
	mov al,1
	mov dx,BasePort
	add dx,6	// 226h
	out dx,al
	// wait 3us
	in al,dx
	in al,dx
	in al,dx
	xor al,al
	out dx,al
	add dx,8	// 22Eh
	L:
	in al,dx
	and al,1000000b
	jz L
	sub dx,4	// 22Ah
	M:
	in al,dx
	cmp al,0AAh
	jne M
	}
}
void WriteDSP(unsigned int BasePort, unsigned char Byte)
{
	asm {
	mov dx,BasePort
	add dx,0Ch
	M:
	in al,dx
	and al,10000000
	jnz M
	mov al,Byte
	out dx,al
	}
}
unsigned char ReadDSP(unsigned int BasePort)
{
	unsigned char Temp;
	asm {
	mov dx,BasePort
	add dx,0Eh
	N:
	in al,dx
	and al,10000000
	jz N
	sub dx,2
	in al,dx
	mov Temp,al
	}
	return Temp;
}
void SpeakerOn(unsigned int BasePort)
{
	WriteDSP(BasePort,209); //D1h
}
void SpeakerOff(unsigned int BasePort)
{
	WriteDSP(BasePort,211); //D3h
}
void DMAstop(unsigned int BasePort)
{
	WriteDSP(BasePort,208); //D0h
}
void DMAcontinue(unsigned int BasePort)
{
	WriteDSP(BasePort,212); //D4h
}
void SetFreq(unsigned int BasePort, unsigned int Freq)
{
	WriteDSP(BasePort,64); // 40h
	WriteDSP(BasePort,256-1000000/Freq);
}
void WriteDAC(unsigned int BasePort, unsigned char Level)
{
	WriteDSP(BasePort,16); //10h
	WriteDSP(BasePort,Level);
}
unsigned char ReadDAC(unsigned int BasePort)
{
	WriteDSP(BasePort,32); //20h
	return ReadDSP(BasePort);
}
void Play(unsigned int BasePort, unsigned char far *Pointer, unsigned int Size, unsigned int Freq)
{
	unsigned char Slo, Shi;
	unsigned int Of=FP_OFF(Pointer);
	unsigned int Sg=FP_SEG(Pointer);
	unsigned int Of1 = Sg*16+Of;
	unsigned int Sg1 = (Sg+Of/16)/4096;

	SpeakerOn(BasePort);
	Size--;

	asm {
	mov dx,0Ah
	mov al,5
	out dx,al
	mov dx,0Ch
	xor al,al
	out dx,al
	mov dx,0Bh
	mov al,049h
	out dx,al
	mov dx,2
	mov ax,Of1
	out dx,al
	out dx,ah
	mov dx,083h
	mov al,Sg1
	out dx,al
	mov dx,3
	mov ax,Size
	mov Slo,al
	mov Shi,ah
	out dx,al
	out dx,ah
	mov dx,0Ah
	mov al,1
	out dx,al
	}
	SetFreq(BasePort,Freq);
	// Set the playback type (8-bit)
	WriteDSP(BasePort,20); //14h
	WriteDSP(BasePort,Slo);
	WriteDSP(BasePort,Shi);
}