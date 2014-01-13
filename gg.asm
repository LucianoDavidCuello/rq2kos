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
     call predrawwindow
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

;  BUTTON1_2
    cmp  ah,3 ;ID BOTON               '    ; button id=1 ?
    je	 BUTTON1_2CLICK

   jmp still

;Sub
BUTTON1_1CLICK:
; CONCATWORD
clearw ttemp1
movstr ttemp1,	EDIT1_1TEXT
concatword ttemp1,  EDIT1_2TEXT
clearw LABEL1_1CAPTION
movstr LABEL1_1CAPTION	, ttemp1

     jmp red  ;end sub


;Sub
BUTTON1_2CLICK:
; REG2REG
mov eax,dword [X]
;if x = 0
cmp eax,0
jne else_1
;button.top+20
mov ecx, dword [BUTTON1_1TOP]
add ecx, 20
mov [BUTTON1_1TOP],ecx
;x=1
mov ecx, 1
mov [X], ecx
jmp endif_1

else_1:

;button.top-20
mov ecx, dword [BUTTON1_1TOP]
sub ecx, 20
mov [BUTTON1_1TOP],ecx
;x=0
mov ecx, 0
mov [X], ecx

endif_1:



; REG2REG

     jmp red  ;end sub


draw_window:
   mcall 12,1
   mcall 0,(217*65536+304),(131*65536+381),0x33AABBCC,0x805080DD,MAINFORM_CAPTION

    ;Boton : <BUTTON1_1            >
   boton BUTTON1_1LEFT,BUTTON1_1TOP,BUTTON1_1WIDTH,BUTTON1_1HEIGHT,BUTTON1_1ID,BUTTON1_1CAPTION,BUTTON1_1COLOR,BUTTON1_1VISIBLE

    ;Boton : <BUTTON1_2            >
   boton BUTTON1_2LEFT,BUTTON1_2TOP,BUTTON1_2WIDTH,BUTTON1_2HEIGHT,BUTTON1_2ID,BUTTON1_2CAPTION,BUTTON1_2COLOR,BUTTON1_2VISIBLE

;Label de < LABEL1_1            >
 plabel  LABEL1_1LEFT,LABEL1_1TOP, LABEL1_1CAPTION,cl_Black,0
;edit box
     mov eax,[EDIT1_1LEFT]
     mov [edit1.left], eax
     mov eax,[EDIT1_1TOP]
     mov [edit1.top], eax
;edit box
     mov eax,[EDIT1_2LEFT]
     mov [edit2.left], eax
     mov eax,[EDIT1_2TOP]
     mov [edit2.top], eax
   draw_edit_boxes editboxes,editboxes_end,use_f9,procinfo

   mcall 12,2
   ret

;codigo antes de form.show
predrawwindow:
   mov eax,1
   mov [X],eax
ret

;Variables-Datos

MAINFORM_CAPTION db 'MAINFORM                                                                                                                                                                                                                                                       ',0
addr dd 0x0
string_length dd 0x0
temp1  dd  0
temp2  dd  0
ttemp1 db 0
  rb  255
ttemp2 db 0
  rb  255
X  dd  0
temp  dd  0
string_x       dd    0
string_y       dd    0
lives dd 5
editboxes:
edit1 edit_box 121,48,116,0xffffff,0x6a9480,0,0xAABBCC,0,255,EDIT1_1TEXT,ed_focus,200,0
edit2 edit_box 121,48,156,0xffffff,0x6a9480,0,0xAABBCC,0,255,EDIT1_2TEXT,0,200,0
editboxes_end:
data_of_code dd 0
mouse_flag dd 0x0

;LABEL1_1
LABEL1_1VISIBLE dd 1
LABEL1_1LEFT dd 56
LABEL1_1TOP dd 60
LABEL1_1COLOR dd 0x000000
LABEL1_1CAP dd 8
LABEL1_1LEN dd 255
LABEL1_1CAPTION db 'LABEL1_1',0
	  rb 255-8

;EDIT1_1
EDIT1_1VISIBLE dd 1
EDIT1_1LEFT dd 48
EDIT1_1TOP dd 116
EDIT1_1COLOR dd 0x000000
EDIT1_1CAP dd 7
EDIT1_1LEN dd 255
EDIT1_1TEXT db 'EDIT1_1',0
	  rb 255-7

;EDIT1_2
EDIT1_2VISIBLE dd 1
EDIT1_2LEFT dd 48
EDIT1_2TOP dd 156
EDIT1_2COLOR dd 0x000000
EDIT1_2CAP dd 7
EDIT1_2LEN dd 255
EDIT1_2TEXT db 'EDIT1_2',0
	  rb 255-7

;BUTTON1_1
BUTTON1_1ID dd 2
BUTTON1_1VISIBLE dd 1
BUTTON1_1LEFT dd 48
BUTTON1_1TOP dd 244
BUTTON1_1WIDTH dd 75
BUTTON1_1HEIGHT dd 20
BUTTON1_1COLOR dd 0xaabbcc
BUTTON1_1CAP dd 9
BUTTON1_1LEN dd 255
BUTTON1_1CAPTION db 'BUTTON1_1',0
	  rb 255-9

;BUTTON1_2
BUTTON1_2ID dd 3
BUTTON1_2VISIBLE dd 1
BUTTON1_2LEFT dd 144
BUTTON1_2TOP dd 244
BUTTON1_2WIDTH dd 75
BUTTON1_2HEIGHT dd 20
BUTTON1_2COLOR dd 0xaabbcc
BUTTON1_2CAP dd 9
BUTTON1_2LEN dd 255
BUTTON1_2CAPTION db 'BUTTON1_2',0
	  rb 255-9
sc system_colors
align 16
procinfo process_information
meos_app_end
udata
