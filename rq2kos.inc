
macro outcount data, x, y, c, numtype
{
    mov ecx,data
    mov ebx,numtype
    mov bl,0
;    mov edx,x*65536+y
    words2reg edx,x,y
    mov esi,c
    mov eax,47
    int 0x40
}

macro clearw dest
{
local cot
mov di, dest
xor ecx,ecx
mov ax,0
cot:
mov [di],ax
inc di
inc cx
cmp cx,255
jne cot

}
CLEARW fix clearw

macro len dest
;devuelve en ax el tamaёo de texto
{
 local len1, flen
  mov cx,0xff
 len1:

  dec cx


  mov di,dest
  add di,cx
  mov ah,byte [di]
  cmp ah,0
  je len1
  ;cmp ah,32
  ;je len1
  ;cmp ah, byte ' '
  ;je len1
  cmp ah,255
  je len1

  xor eax,eax
   cmp cx,0
   je flen

 flen:
  inc cx
  mov ax,cx
}


 ;movestr: mueve texto de [si] a [di]

macro movstr destino, origen
{
local movestr1
 mov di, destino
 mov si, origen
   cld
movestr1:
   lodsb
   stosb
   or al,al
   jnz movestr1
   }

macro concatword destino, origen
{
len destino
mov di, destino
add di, ax
movstr di, origen

}

macro words2reg reg,hiword,lowword
{
if hiword eq
   if lowword eq
      ; not changes
   else
      if lowword eqtype 12
  and reg,dword 0xffff0000
  add reg,dword lowword
      else
  and reg,dword 0xffff0000
  add reg,dword lowword
      end if
   end if
else
   if lowword eq
      if hiword eqtype 12
  and reg,dword 0x0000ffff
  add reg,dword hiword*65536
      else
  shl reg,16
  add reg,dword hiword
  ror reg,16
      end if
   else
      if lowword eqtype 12 & hiword eqtype 12
  if lowword eq 0 & hiword eq 0
	xor reg,reg
     else
	mov reg,dword hiword*65536+lowword
  end if
      else
  mov reg,dword hiword
  shl reg,16
  add reg,dword lowword
      end if
   end if
end if
}


macro boton x,y,x2,y2,id,texto,color,visible
{
 local no_visiblexx


xor eax,eax
mov eax ,[x2]
shr ax,1
add eax,[x]
mov [temp1],eax
len texto
shr ax,1
mov bx,6
imul bx
sub [temp1],eax

xor eax,eax
mov eax ,[y2]
shr ax,1
add eax,[y]
mov [temp2],eax

    xor  eax,eax
    mov  ax,word [visible]
    cmp  ax,0
    je	 no_visiblexx
    mov  eax,8
    xor bx,bx
    mov  ebx,dword [x]
    shl  ebx,16
    add  ebx,dword [x2]
    mov  ecx,dword [y]
    shl  ecx,16
    add  ecx,dword [y2]
    xor edx,edx
    mov  dx,[id]
    mov  esi,[color]
    int  0x40
    mov  ax,4
    len texto
mov bx,6
imul bx
mov [temp3],eax
mov [temp4],9
    plabel temp1,temp2,temp3,temp4,texto,color
 no_visiblexx:
}

macro kpanel x,y,x2,y2,id,texto,color,visible,parent
{
 local no_visiblexx,lx,ly

 xor bx,bx
    mov  ebx,dword [x]
    shl  ebx,16
    add  ebx,dword [x2]

    mov  ecx,dword [y]

    shl  ecx,16
    add  ecx,dword [y2]
    xor edx,edx

    mov  edx,[color]

mov eax,13
mcall

xor eax,eax
mov eax ,[x2]
shr ax,1
add eax,[x]
mov [temp1],eax
len texto
shr ax,1
mov bx,6
imul bx
sub [temp1],eax

xor eax,eax
mov eax ,[y2]
shr ax,1
add eax,[y]
mov [temp2],eax
;len texto



   ;--- сверху ---
	mov edx,0xffffff;[color]
mov	eax,38
	mov	ebx,[x]
	mov	ecx,ebx
	shl	ebx,16
	mov	bx,cx
	add	ebx,[x2]
	mov	ecx,[y]
	mov	esi,ecx
	shl	ecx,16
	mov	cx,si
	mcall
;--- снизу ---
	  mov edx,0xffffff ;abajo
	mov	esi,ecx
	add	ecx,[y2]
	mov	ebp,ecx
	shl	ecx,16
	mov	cx,bp
       ; mcall
;--- слева ---
      mov edx,0xffffff
	mov	cx,si
	mov	ebp,ebx
	sub	ebx,[x2]
	mcall
;--- справа ---
  mov edx,0xffffff ;izq
	mov	ebx,ebp
	shl	ebx,16
	mov	bx,bp
       ; mcall


	mov edx,0x000000;[color]
mov	eax,38
	mov	ebx,[x]
	inc ebx
	mov	ecx,ebx

	shl	ebx,16
	mov	bx,cx

	add	ebx,[x2]
	mov	ecx,[y]
inc cx
mov	esi,ecx
	shl	ecx,16
	inc ecx
	mov	cx,si
     ;   mcall
;--- снизу ---
	  mov edx,0xfffffff
	mov	esi,ecx
	add	ecx,[y2]
	mov	ebp,ecx
inc ecx
shl	ecx,16
	mov	cx,bp
inc cx
	mcall
;--- слева ---
      mov edx,0x888888
	mov	cx,si
	mov	ebp,ebx
	sub	ebx,[x2]
       ; mcall
;--- справа ---
  mov edx,0x888888 ;izq
	mov	ebx,ebp
	shl	ebx,16
	mov	bx,bp
	mcall

len texto
mov bx,6
imul bx
mov [temp3],eax
mov [temp4],9

plabel temp1,temp2,temp3,temp4,texto,color

 no_visiblexx:
}

macro kgroupbox x,y,x2,y2,id,texto,color,visible,parent
{
 local no_visiblexx,lx,ly

mov eax,[x]
add eax,5
mov [temp1], eax

mov eax,[y]
sub eax,5
mov [temp2], eax

    xor bx,bx
    mov  ebx,dword [x]
    shl  ebx,16
    add  ebx,dword [x2]

    mov  ecx,dword [y]

    shl  ecx,16
    add  ecx,dword [y2]
    xor edx,edx

    mov  edx,[color]

   mov eax,13
   mcall

   ;--- сверху ---
	mov edx,0xffffff
	mov	eax,38
	mov	ebx,[x]
	mov	ecx,ebx
	shl	ebx,16
	mov	bx,cx
	add	ebx,[x2]
	mov	ecx,[y]
	mov	esi,ecx
	shl	ecx,16
	mov	cx,si
	mcall
;--- снизу ---
	  mov edx,0xffffff ;abajo
	mov	esi,ecx
	add	ecx,[y2]
	mov	ebp,ecx
	shl	ecx,16
	mov	cx,bp
	mcall
;--- слева ---
      mov edx,0xffffff
	mov	cx,si
	mov	ebp,ebx
	sub	ebx,[x2]
	mcall
;--- справа ---
	mov edx,0xffffff ;izq
	mov	ebx,ebp
	shl	ebx,16
	mov	bx,bp
	mcall


	mov edx,0x000000
	mov	eax,38
	mov	ebx,[x]
	inc ebx
	mov	ecx,ebx

	shl	ebx,16
	mov	bx,cx

	add	ebx,[x2]
	mov	ecx,[y]
	inc cx
	mov	esi,ecx
	shl	ecx,16
	inc ecx
	mov	cx,si
	mcall
;--- снизу ---
	  mov edx,0xfffffff
	mov	esi,ecx
	add	ecx,[y2]
	mov	ebp,ecx
	inc ecx
	shl	ecx,16
	mov	cx,bp
	inc cx
	mcall
;--- слева ---
	mov edx,0x888888
	mov	cx,si
	mov	ebp,ebx
	sub	ebx,[x2]
	mcall
;--- справа ---
	mov edx,0x888888 ;izq
	mov	ebx,ebp
	shl	ebx,16
	mov	bx,bp
	mcall


;x = x2 / 2
;
len texto
mov bx,6
imul bx
mov [temp3],eax
  ;  xor bx,bx
  ;  mov  ebx,dword [x]
  ;  add  ebx,3
  ;  shl  ebx,16
  ;  add  bx,ax
 ;   add bx,2
  ;
  ;  mov  ecx,dword [y]
  ;  ;sub  ecx,4
  ;  shl  ecx,16
 ;   add  ecx,12
  ;  xor edx,edx
  ;  mov  edx,[color]
  ;  mov eax,13
 ;  mcall

    
mov [temp4],9

plabel temp1,temp2,temp3,temp4,texto,color

 no_visiblexx:
}

macro plabel x,y,x2,y2,texto,color
 {




    xor bx,bx
    mov  ebx,dword [x]
    ;add  ebx,3
    shl  ebx,16
    add ebx,[x2]
    ;add bx,2   

    mov  ecx,dword [y]
    ;sub  ecx,4
    shl  ecx,16
    add  ecx,[y2]
    xor edx,edx
    mov  edx,[color]
    mov eax,13
    mcall
    mov  eax,4
    mov  ebx,[x]

    shl  ebx,16
    add  ebx,[y]

    mov  ecx,cl_Black

    mov  edx,texto;[addr]
    mov  esi,255 ;'string_length]
    int  0x40
  }

cl_White  equ 0x00ffffff
cl_Black  equ 0x00000000
cl_Grey   equ 0x00888888
cl_Gray   equ 0x00888888
cl_Red	 equ 0x00ff0000
cl_Lime   equ 0x0000ff00
cl_Green  equ 0x0000af00
cl_Blue   equ 0x000000ff
cl_Purple equ 0x008080ff
cl_Violet equ 0x008040ff
cl_Cyan   equ 0x0040e0ff


macro sssswindow arg1,arg2,arg3,arg4,arg5,arg6,arg7
{
;    mov ebx,arg1*65536+arg3
;    mov ecx,arg2*65536+arg4
    bx,[arg1]
    shl bx,16
    add bx,[arg2]
    words2reg ecx,[arg3],[arg4]
    mov edx,[arg5]
    mov edi,arg6
    mov esi,arg7
    mov eax,0
    int 0x40
;0,(dword [MainForm.top] * 65536 + dword [MainForm.left]),(dword [MainForm.width] * 65536+ dword [MainForm.height]),0x33AABBCC,0x805080DD,MainForm.text
}

macro window arg1,arg2,arg3,arg4,arg5,arg6,arg7
{
    mov ebx,[arg1]
    shl ebx,16
    add ebx,[arg3]
    mov ecx,[arg2]
    shl ecx,16
    add ecx,[arg4]
    mov edx,arg5
    mov esi,arg6
    mov edi,arg7
    mov eax,0
    int 0x40
}

macro cmpstr arg1,arg2
{
local StrCmp1,StrCmp2


     mov di, arg1
     mov si, arg2
     Cld
StrCmp1:
     Lodsb
     Scasb
     Jne  StrCmp2
     Or   AL,AL
     Jne  StrCmp1
StrCmp2:


}

macro ifmouseclick x,y,x2,y2,dir

{
local click,_True_01,_True_02,_True_03,_True_04,fin
mcall 37,2
test	eax,eax   
jnz	click
jmp	fin
click:
mcall 37,1
xor ebx,ebx
mov bx,ax
mov [temp2],ebx ;y mouse
shr eax,16
mov bx,ax
mov [temp1],ebx ;x mouse

mov cx,0	
 
;
;if mx = > x then 
;
     Mov  eAX,[temp1]
     Cmp  eAX,[x]
     Jge  _True_01
     Jmp  fin
_True_01:
;
;if mx = < x2 then 
;
     Mov  eax,[x]
     add eax,[x2]
     Cmp  eAX,[temp1]
     Jge  _True_02
     Jmp  fin
_True_02:
;
;if my = > y then 
     Mov  eax,[y]

     Cmp  eAX,[temp2]

    Jle  _True_03
    Jmp  fin
_True_03:
;
;if mu = < y2 then 
;
      Mov  eax,[y]
      add eax,[y2]
      Cmp  eAX,[temp2]
    Jge  _True_04
     Jmp  fin
_True_04:
;
;eax = 1 
;
     Mov  cx,1
;
;end if 
;
fin:

cmp cx,1
je dir
}

macro mousex arg
{
pusha
mcall 37,1

xor ebx,ebx
;mov bx,ax
;mov [temp2],ebx ;y mouse
shr eax,16
mov bx,ax
mov [arg],ebx ;x mouse
popa
}

macro mousey arg
{
pusha
mcall 37,1
xor ebx,ebx
mov bx,ax
mov [arg],ebx ;y mouse
popa
}

macro str arg 
; = str$(arg)
; di = destino
{

local Str_1,Str_2,Str_3,Str_4
    
     mov eax,arg
     Cmp  BX,1
     Je   Str_1
     Mov  [DI],Byte 32
     Inc  DI
Str_1:
     Xor  BX,BX
     Cmp  AX,32768
     Jb   Str_2
     Neg  AX
     Mov  [DI],Byte  '-'
     Inc  DI
Str_2:
     Xor  CX,CX
     Mov  BX,10
Str_3:
     Inc  CX
     Xor  DX,DX
     Div  BX
     Push DX
     Cmp  AX,0
     Jne  Str_3
Str_4:
     Pop  AX
     Add  AL,'0'
     Mov  [DI],AL
     Inc  DI
     Loop Str_4
     Xor  AX,AX
     Mov  [DI],AL
 
}

macro ifmousemove x,y,x2,y2,dir

{
local click,_True_01,_True_02,_True_03,_True_04,fin
mcall 37,1
mov ebx,eax
mcall 37,1

cmp eax,ebx
jne dir
jmp fin


click:

xor ebx,ebx
mov [temp1],ebx
mov [temp2],ebx
mov bx,ax
mov [temp2],ebx ;y mouse
shr eax,16
mov bx,ax
mov [temp1],ebx ;x mouse

mov cx,0	
 
;
;if mx = > x then 
;
     Mov  eAX,[temp1]
     Cmp  eAX,[x]
     Jge  _True_01
     Jmp  fin
_True_01:

;
;if mx = < x2 then 
;
     Mov  eax,[x]
     add eax,[x2]
     Cmp  eAX,[temp1]
     Jge  _True_02
     Jmp  fin
_True_02:
;
;if my = > y then 
     Mov  eax,[y]

     Cmp  eAX,[temp2]

    Jle  _True_03
    Jmp  fin
_True_03:
;
;if mu = < y2 then 
;
      Mov  eax,[y]
      add eax,[y2]
      Cmp  eAX,[temp2]
    Jge  _True_04
     Jmp  fin
_True_04:
;
;eax = 1 
;
     Mov  cx,1
;
;end if 
;
fin:

cmp cx,1
je dir

}

macro chr arg
{
; di = destino

mov eax, arg
mov [di],byte ax
xor ebx,ebx
mov [di+1],byte bx


}