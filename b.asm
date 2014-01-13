; RQ2Fasm Kolibrios
; Autor: NeoTEC 2009  - Luciano David Cuello -santa fe- ARGENTINA
; Mail: jackerscomp2002@yahoo.com.ar
; Compilar con FASM para Kolibri OS

include 'macros.inc'
use32
  meos_app_start
include 'editbox.inc'
include 'check.inc'
  version_ch1
  use_check_box
  use_edit_box procinfo,22,5
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
   mouse_check_boxes check_boxes,check_boxes_end
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


   jmp still

draw_window:
   mcall 12,1
   mcall 0,(217*65536+299),(131*65536+424),0x33AABBCC,0x805080DD,MAINFORM_CAPTION



    ;Boton : <BUTTON1_1            >

    xor  eax,eax
    mov  eax,[boton_1v]
    cmp  eax,0
    je	boton_1_no_visible
    mov  eax,8
    mov  ebx,[boton_1x]
    shl  ebx,16
    add  ebx,[boton_1x2]
    mov  ecx,[boton_1y]
    shl  ecx,16
    add  ecx,[boton_1y2]
    mov  edx,[boton_1i]
    mov  esi,[boton_1c]
    int  0x40
boton_1_no_visible:


    ;Boton : <BUTTON1_2            >

    xor  eax,eax
    mov  eax,[boton_2v]
    cmp  eax,0
    je	boton_2_no_visible
    mov  eax,8
    mov  ebx,[boton_2x]
    shl  ebx,16
    add  ebx,[boton_2x2]
    mov  ecx,[boton_2y]
    shl  ecx,16
    add  ecx,[boton_2y2]
    mov  edx,[boton_2i]
    mov  esi,[boton_2c]
    int  0x40
boton_2_no_visible:


    ;Boton : <BUTTON1_3            >

    xor  eax,eax
    mov  eax,[boton_3v]
    cmp  eax,0
    je	boton_3_no_visible
    mov  eax,8
    mov  ebx,[boton_3x]
    shl  ebx,16
    add  ebx,[boton_3x2]
    mov  ecx,[boton_3y]
    shl  ecx,16
    add  ecx,[boton_3y2]
    mov  edx,[boton_3i]
    mov  esi,[boton_3c]
    int  0x40
boton_3_no_visible:


;Label de < LABEL1_1            >

    xor  eax,eax
    mov  eax,[labelt_1v]
    cmp  eax,0
    je	labelt_1_no_visible
    mov  eax,4
    mov  ebx,[labelt_1x]
    shl  ebx,16
    add  ebx,[labelt_1y]
    mov  ecx,[labelt_1c]
    mov  [addr],dword labelt_1t
    mov  edx,[addr]
    mov  esi,[labelt_1l]
    int  0x40
labelt_1_no_visible:

;Label de < LABEL1_2            >

    xor  eax,eax
    mov  eax,[labelt_2v]
    cmp  eax,0
    je	labelt_2_no_visible
    mov  eax,4
    mov  ebx,[labelt_2x]
    shl  ebx,16
    add  ebx,[labelt_2y]
    mov  ecx,[labelt_2c]
    mov  [addr],dword labelt_2t
    mov  edx,[addr]
    mov  esi,[labelt_2l]
    int  0x40
labelt_2_no_visible:

;Label de < LABEL1_3            >

    xor  eax,eax
    mov  eax,[labelt_3v]
    cmp  eax,0
    je	labelt_3_no_visible
    mov  eax,4
    mov  ebx,[labelt_3x]
    shl  ebx,16
    add  ebx,[labelt_3y]
    mov  ecx,[labelt_3c]
    mov  [addr],dword labelt_3t
    mov  edx,[addr]
    mov  esi,[labelt_3l]
    int  0x40
labelt_3_no_visible:

;Label de < BUTTON1_1           >

    xor  eax,eax
    mov  eax,[boton_1v]
    cmp  eax,0
    je	boton_1t_no_visible
    mov  eax,4
    mov  ebx,[boton_1x]
    add  ebx,5
    shl  ebx,16
    add  ebx,[boton_1y]
    add  ebx,5
    mov  ecx,0x000000
    mov  [addr],dword boton_1t
    mov  edx,[addr]
    mov  esi,[boton_1l]
    int  0x40
boton_1t_no_visible:

;Label de < BUTTON1_2           >

    xor  eax,eax
    mov  eax,[boton_2v]
    cmp  eax,0
    je	boton_2t_no_visible
    mov  eax,4
    mov  ebx,[boton_2x]
    add  ebx,5
    shl  ebx,16
    add  ebx,[boton_2y]
    add  ebx,5
    mov  ecx,0x000000
    mov  [addr],dword boton_2t
    mov  edx,[addr]
    mov  esi,[boton_2l]
    int  0x40
boton_2t_no_visible:

;Label de < BUTTON1_3           >

    xor  eax,eax
    mov  eax,[boton_3v]
    cmp  eax,0
    je	boton_3t_no_visible
    mov  eax,4
    mov  ebx,[boton_3x]
    add  ebx,5
    shl  ebx,16
    add  ebx,[boton_3y]
    add  ebx,5
    mov  ecx,0x000000
    mov  [addr],dword boton_3t
    mov  edx,[addr]
    mov  esi,[boton_3l]
    int  0x40
boton_3t_no_visible:


     mov ax,66
     mov [ch1.left], ax
     mov ax,108
     mov [ch1.top], ax

     draw_check_boxes check_boxes,check_boxes_end
     draw_edit_boxes editboxes,editboxes_end,use_f9,procinfo

   mcall 12,2
   ret

;Variables-Datos

MAINFORM_CAPTION db 'RAPIDQ EN KOLIBRI OS                                                                                                                                                                                                                                           ',0
addr dd 0x0
string_length dd 0x0
temp  dd  0
string_x       dd    0
string_y       dd    0
editboxes:
edit1 edit_box 121,80,44,0xffffff,0x6a9480,0,0xAABBCC,0,255,EDIT1_1,ed_focus,200,0
edit2 edit_box 121,80,68,0xffffff,0x6a9480,0,0xAABBCC,0,255,EDIT1_2,0,200,0
editboxes_end:
check_boxes:
ch1 check_box1 0,0,CHECKBOX1_1,20

check_boxes_end:
data_of_code dd 0
mouse_flag dd 0x0

;labelt_1
labelt_1v dd 1
labelt_1x dd 16
labelt_1y dd 52
labelt_1c dd 0x000000
labelt_1l dd 6
labelt_1lm dd 255
labelt_1t db 'NOMBRE                                                                                                                                                                                                                                                         ',0

;labelt_2
labelt_2v dd 1
labelt_2x dd 16
labelt_2y dd 68
labelt_2c dd 0x000000
labelt_2l dd 4
labelt_2lm dd 255
labelt_2t db 'EDAD                                                                                                                                                                                                                                                           ',0

;labelt_3
labelt_3v dd 1
labelt_3x dd 80
labelt_3y dd 292
labelt_3c dd 0x000000
labelt_3l dd 27
labelt_3lm dd 255
labelt_3t db 'PRUEBA DE FORM EN KOLIBRIOS                                                                                                                                                                                                                                    ',0

;boton_1
boton_1i dd 2
boton_1v dd 1
boton_1x dd 16
boton_1y dd 204
boton_1x2 dd 75
boton_1y2 dd 25
boton_1c dd 0xaabbcc
boton_1l dd 6
boton_1lm dd 255
boton_1t db 'GUARDA                                                                                                                                                                                                                                                         ',0

;boton_2
boton_2i dd 3
boton_2v dd 1
boton_2x dd 192
boton_2y dd 204
boton_2x2 dd 75
boton_2y2 dd 25
boton_2c dd 0xaabbcc
boton_2l dd 5
boton_2lm dd 255
boton_2t db 'EDITA                                                                                                                                                                                                                                                          ',0

;boton_3
boton_3i dd 4
boton_3v dd 1
boton_3x dd 104
boton_3y dd 204
boton_3x2 dd 75
boton_3y2 dd 25
boton_3c dd 0xaabbcc
boton_3l dd 4
boton_3lm dd 255
boton_3t db 'SALE                                                                                                                                                                                                                                                           ',0

EDIT1_1 db 'DAVID CUELLO                                                                                                                                                                                                                                                   ',0


EDIT1_2 db '24                                                                                                                                                                                                                                                             ',0


CHECKBOX1_1 db 'MUJER                                                                                                                                                                                                                                                          ',0


CHECKBOX1_2 db 'HOMBRE                                                                                                                                                                                                                                                         ',0

sc system_colors
align 16
procinfo process_information
meos_app_end
udata
