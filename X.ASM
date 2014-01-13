; RQ2Fasm Kolibrios
; Autor: NeoTEC 2009  - Luciano David Cuello -santa fe- ARGENTINA
; Mail: jackerscomp2002@yahoo.com.ar
; Compilar con FASM para Kolibri OS

include 'rq2kos.inc'

use32
  meos_app_start
include 'editbox.inc'
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
     movstr  ttemp1,  edit_1t
     len edit_1t

     mov [temp1],eax

     len edit_2t
     mov [temp2],eax

     clearw ttemp1
     clearw labelt_1t

     movstr ttemp1, edit_1t
     mov di,ttemp1
     mov eax,dword [temp1]
     add di,ax
     movstr di,edit_2t

     movstr labelt_1t, ttemp1
     jmp red  ;end sub


draw_window:
   mcall 12,1
   mcall 0,(329*65536+497),(230*65536+130),0x33AABBCC,0x805080DD,MAINFORM_CAPTION
     outcount dword [temp1],10,10,cl_Black,3*65536
    ;Boton : <BUTTON1_1
    outcount dword [temp2],10,20,cl_Black,3*65536
   boton boton_1x,boton_1y,boton_1x2,boton_1y2,boton_1i,boton_1t,boton_1c,boton_1v

;Label de < LABEL1_1            >
 plabel  labelt_1x,labelt_1y, labelt_1t,cl_Black,0
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

   mcall 12,2
   ret

;Variables-Datos

MAINFORM_CAPTION db 'MAINFORM                                                                                                                                                                                                                                                       ',0
addr dd 0x0
string_length dd 0x0
temp1  dd  0x0
temp2  dd  0x0
ttemp1 db 0
  rb  255
ttemp2 db 0
  rb  255
temp  dd  0
string_x       dd    0
string_y       dd    0
lives dd 5
editboxes:
edit1 edit_box 121,168,28,0xffffff,0x6a9480,0,0xAABBCC,0,255,edit_1t,ed_focus,200,0
edit2 edit_box 121,304,28,0xffffff,0x6a9480,0,0xAABBCC,0,255,edit_2t,0,200,0
editboxes_end:
data_of_code dd 0
mouse_flag dd 0x0

;labelt_1
labelt_1v dd 1
labelt_1x dd 40
labelt_1y dd 36
labelt_1c dd 0x000000
labelt_1l dd 8
labelt_1lm dd 255
labelt_1t db 'LABEL1_1',0
	  rb 255-8

;edit_1
edit_1v dd 1
edit_1x dd 168
edit_1y dd 28
edit_1c dd 0x000000
edit_1l dd 7
edit_1lm dd 255
edit_1t db 'EDIT1_1',0
	  rb 255-7

;edit_2
edit_2v dd 1
edit_2x dd 304
edit_2y dd 28
edit_2c dd 0x000000
edit_2l dd 7
edit_2lm dd 255
edit_2t db 'EDIT1_2',0
	  rb 255-7

;boton_1
boton_1i dd 2
boton_1v dd 1
boton_1x dd 192
boton_1y dd 60
boton_1x2 dd 75
boton_1y2 dd 20
boton_1c dd 0xaabbcc
boton_1l dd 9
boton_1lm dd 255
boton_1t db 'BUTTON1_1',0
	  rb 255-9
sc system_colors
align 16
procinfo process_information
meos_app_end
udata
