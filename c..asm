; RQ2Fasm Kolibrios
; Autor: NeoTEC 2009  - Luciano David Cuello -santa fe- ARGENTINA
; Mail: jackerscomp2002@yahoo.com.ar
; Compilar con FASM para Kolibri OS

   include 'macros.inc'
macro len dest
;devuelve en ax el tamaño de texto
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
  cmp ah,32
  je len1
  cmp ah, byte ' '
  je len1
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

macro movestr destino, origen
{
local movestr1
 mov di,destino
 mov si,origen
   cld
movestr1:
   lodsb
   stosb
   or al,al
   jnz movestr1
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

    xor  eax,eax
    mov  eax,[visible]
    cmp  eax,0
    je	 no_visible
    mov  eax,8
    mov  ebx,[x]
    shl  ebx,16
    add  ebx,[x2]
    mov  ecx,[y]
    shl  ecx,16
    add  ecx,[y2]
    mov  edx,[id]
    mov  esi,[color]
    int  0x40
    mov  eax,4
    plabel x,y,texto,color,7
 no_visible:
}

macro plabel x,y,texto,color,tipo
 {
    mov  eax,4
    mov  ebx,[x]
    add  ebx,tipo
    shl  ebx,16
    add  ebx,[y]
    add  ebx,tipo
    mov  ecx,color
    mov  [addr],dword texto
    mov  edx,[addr]
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


use32
  meos_app_start
include 'editbox.inc'
  use_edit_box procinfo,22,5
   include 'optionbox.inc'
   version_op
   use_option_box
  align 4
code
     mov eax,48
     mov ebx,3
     mov ecx,sc
     mov edx, sizeof.system_colors
     mcall

     mov eax, 40
     mov ebx,0x25
     mcall
 mcall 40,0x27
START:
     call draw_window
still:

    mcall  10		      ; wait here for event

    cmp  eax,1			; redraw request ?
    je red
    cmp  eax,2			; key in buffer ?
    je	 key
    cmp  eax,3			; button in buffer ?
    je button

   mouse_edit_boxes editboxes,editboxes_end
 mouse_option_boxes option_boxes,option_boxes_end
    jmp still

  red:				; redraw
    call draw_window
    jmp still

  key:				; key
    mcall 2		     ; just read it and ignore
      key_edit_boxes editboxes,editboxes_end
    jmp still

  button:			; button
    mcall 17		     ; get id

    cmp  ah,1			; button id=1 ?
    jne noclose

    mcall -1		     ; close this program
noclose:

;  BUTTON1_1
    cmp  ah,2 ;ID BOTON               '    ; button id=1 ?
    je	 BUTTON1_1CLICK

   jmp still

;Sub
BUTTON1_1CLICK:
   ;  mov di,  edit_1t
   ;  mov cx,1
   ;  add di,cx
   ;  mov ax ,[di]
     mov si, labelt_1t
   ;  mov [si],ax
    len edit_1t
    mov [temp],eax

     jmp red  ;end sub


draw_window:
   mcall 12,1
   mcall 0,(329*65536+477),(230*65536+110),0x33AABBCC,0x805080DD,MAINFORM_CAPTION
    outcount dword [temp], 20, 20 , cl_Black ,3 * 65536
    ;Boton : <BUTTON1_1            >
   boton boton_1x,boton_1y,boton_1x2,boton_1y2,boton_1i,boton_1t,boton_1c,boton_1v
 ;   xor  eax,eax
 ;   mov  eax,[boton_1v]
 ;   cmp  eax,0
 ;   je  boton_1_no_visible
 ;   mov  eax,8
 ;   mov  ebx,[boton_1x]
 ;   shl  ebx,16
 ;   add  ebx,[boton_1x2]
 ;   mov  ecx,[boton_1y]
 ;   shl  ecx,16
 ;   add  ecx,[boton_1y2]
 ;   mov  edx,[boton_1i]
 ;   mov  esi,[boton_1c]
 ;   int  0x40
boton_1_no_visible:


;Label de < LABEL1_1            >
 plabel  labelt_1x,labelt_1y, labelt_1t,cl_Black,0
   ; xor  eax,eax
   ; mov  eax,[labelt_1v]
   ; cmp  eax,0
   ; je  labelt_1_no_visible
   ; mov  eax,4
   ; mov  ebx,[labelt_1x]
   ; shl  ebx,16
   ; add  ebx,[labelt_1y]
   ; mov  ecx,[labelt_1c]
   ; mov  [addr],dword labelt_1t
   ; mov  edx,[addr]
   ; mov  esi,[labelt_1l]
   ; int  0x40
labelt_1_no_visible:
;edit box
     mov eax,[edit_1x]
     mov [edit1.left], eax
     mov eax,[edit_1y]
     mov [edit1.top], eax
;edit box
     mov eax,[edit_2x]
     mov [edit2.left], eax
     mov eax,[edit_2y]
     mov [edit2.top], eax
   draw_edit_boxes editboxes,editboxes_end,use_f9,procinfo
;radio_boton
     mov eax,[radioboton_1x]
     mov [op1.left], ax
     mov eax,[radioboton_1y]
     mov [op1.top], ax
;radio_boton
     mov eax,[radioboton_2x]
     mov [op2.left], ax
     mov eax,[radioboton_2y]
     mov [op2.top], ax
draw_option_boxes option_boxes,option_boxes_end

   mcall 12,2
   ret

;Variables-Datos

MAINFORM_CAPTION db 'MAINFORM                                                                                                                                                                                                                                                       ',0
addr dd 0x0
string_length dd 0x0
temp  dd  0
string_x       dd    0
string_y       dd    0
lives dd 5

editboxes:
edit1 edit_box 121,168,28,0xffffff,0x6a9480,0,0xAABBCC,0,255,edit_1t,ed_focus,200,0
edit2 edit_box 121,304,28,0xffffff,0x6a9480,0,0xAABBCC,0,255,edit_2t,0,200,0
editboxes_end:
check_boxes:
check_boxes_end:

option_boxes:
op1 option_box option_group1,0,0,0xffffff,0,0,radioboton_1t,14
op2 option_box option_group1,0,0,0xffffff,0,0,radioboton_2t,14
option_boxes_end:
option_group1 dd op2
data_of_code dd 0
mouse_flag dd 0x0
   txt1 db 'dsadsadsadsa'
   txt2 db 'aaaaaaaaaaa'
;labelt_1
labelt_1v dd 1
labelt_1x dd 40
labelt_1y dd 36
labelt_1c dd 0x000000
labelt_1l dd 8
labelt_1lm dd 255
labelt_1t db 'LABEL1_1                                                                                                                                                                                                                                                       ',0

;edit_1
edit_1v dd 1
edit_1x dd 168
edit_1y dd 28
edit_1c dd 0x000000
edit_1l dd 7
edit_1lm dd 255
edit_1t db 'EDIT1_1                                                                                                                                                                                                                                                        ',0

;edit_2
edit_2v dd 1
edit_2x dd 304
edit_2y dd 28
edit_2c dd 0x000000
edit_2l dd 7
edit_2lm dd 255
edit_2t db 'EDIT1_2                                                                                                                                                                                                                                                        ',0

;radioboton_1
radioboton_1v dd 1
radioboton_1x dd 248
radioboton_1y dd 60
radioboton_1c dd 0x000000
radioboton_1l dd 14
radioboton_1lm dd 255
radioboton_1t db 'RADIOBUTTON1_1                                                                                                                                                                                                                                                 ',0

;radioboton_2
radioboton_2v dd 1
radioboton_2x dd 248
radioboton_2y dd 76
radioboton_2c dd 0x000000
radioboton_2l dd 14
radioboton_2lm dd 255
radioboton_2t db 'RADIOBUTTON1_2                                                                                                                                                                                                                                                 ',0

;boton_1
boton_1i dd 2
boton_1v dd 1
boton_1x dd 136
boton_1y dd 60
boton_1x2 dd 75
boton_1y2 dd 20
boton_1c dd 0xaabbcc
boton_1l dd 9
boton_1lm dd 255
boton_1t db 'BUTTON1_1                                                                                                                                                                                                                                                      ',0
sc system_colors
align 16
procinfo process_information
meos_app_end
udata
