; RQ2Fasm Kolibrios
; Autor: NeoTEC 2009  - Luciano David Cuello -santa fe- ARGENTINA 
; Mail: jackerscomp2002@yahoo.com.ar
; Compilar con FASM para Kolibri OS 

include 'rq2kos.inc'

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

    mcall  10                 ; wait here for event

    cmp  eax,1                  ; redraw request ?
    je red
    cmp  eax,2                  ; key in buffer ?
    je   key
    cmp  eax,3                  ; button in buffer ?
    je button

   mouse_edit_boxes editboxes,editboxes_end 
   mouse_check_boxes check_boxes,check_boxes_end
    jmp still

  red:                          ; redraw
    call draw_window
    jmp still

  key:                          ; key
    mcall 2                  ; just read it and ignore
      key_edit_boxes editboxes,editboxes_end
    jmp still

  button:                       ; button
    mcall 17                 ; get id

    cmp  ah,1                   ; button id=1 ?
    jne noclose

    mcall -1                 ; close this program
noclose:

   jmp still

;Sub 
BUTTON1_2CLICK:
; MOVESTR
clearw LABEL1_1CAPTION 
movstr LABEL1_1CAPTION , EDIT1_1TEXT

     jmp red  ;end sub
 

;Sub 
PANEL1_2CLICK:
; MOVESTR
clearw LABEL1_1CAPTION 
movstr LABEL1_1CAPTION ,texto4

     jmp red  ;end sub
 

;Sub 
MAINFORMMOUSEMOVE:

     jmp red  ;end sub
 

;Sub 
GROUPBOX1_1MOUSEMOVE:
; NUM2REG
mov eax,  MOUSEX
mov [X ] ,eax
; NUM2REG
mov eax,  MOUSEY
mov [Y ] ,eax
; NUM2REG
mov eax,  STR$(X)
mov [LABEL1_3CAPTION ] ,eax
; NUM2REG
mov eax,  STR$(Y)
mov [LABEL1_5CAPTION ] ,eax

     jmp red  ;end sub
 

draw_window:
   mcall 12,1
   mcall 0,(405*65536+443),(302*65536+381),0x33AABBCC,0x805080DD,MAINFORM_CAPTION

    ;Boton : <BUTTON1_1            >
   boton BUTTON1_1LEFT,BUTTON1_1TOP,BUTTON1_1WIDTH,BUTTON1_1HEIGHT,BUTTON1_1ID,BUTTON1_1CAPTION,BUTTON1_1COLOR,BUTTON1_1VISIBLE

;Label de < LABEL1_1            >
 plabel  LABEL1_1LEFT,LABEL1_1TOP, LABEL1_1CAPTION,cl_Black,0

;Label de < LABEL1_2            >
 plabel  LABEL1_2LEFT,LABEL1_2TOP, LABEL1_2CAPTION,cl_Black,0

;Label de < LABEL1_3            >
 plabel  LABEL1_3LEFT,LABEL1_3TOP, LABEL1_3CAPTION,cl_Black,0

;Label de < LABEL1_4            >
 plabel  LABEL1_4LEFT,LABEL1_4TOP, LABEL1_4CAPTION,cl_Black,0

;Label de < LABEL1_5            >
 plabel  LABEL1_5LEFT,LABEL1_5TOP, LABEL1_5CAPTION,cl_Black,0
;check box
     mov eax,[checkbox_1LEFT]
     mov [ch1.left], ax
     mov eax,[checkbox_1TOP]
     mov [ch1.top], ax
;check box
     mov eax,[checkbox_2LEFT]
     mov [ch2.left], ax
     mov eax,[checkbox_2TOP]
     mov [ch2.top], ax
;check box
     mov eax,[checkbox_3LEFT]
     mov [ch3.left], ax
     mov eax,[checkbox_3TOP]
     mov [ch3.top], ax
   draw_check_boxes check_boxes,check_boxes_end
;edit box
     mov eax,[EDIT1_1LEFT]
     mov [edit1.left], eax
     mov eax,[EDIT1_1TOP]
     mov [edit1.top], eax
   draw_edit_boxes editboxes,editboxes_end,use_f9,procinfo

   mcall 12,2
   ret

;codigo antes de form.show


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
Y  dd  0
G  dd  0
texto4  db 'PANEL CLICKED',0
temp  dd  0
string_x       dd    0
string_y       dd    0
lives dd 5
editboxes:
edit1 edit_box 121,88,276,0xffffff,0x6a9480,0,0xAABBCC,0,255,EDIT1_1TEXT,ed_focus,200,0
editboxes_end:
check_boxes:
ch1 check_box1 0,0,checkbox_1t,11
ch2 check_box1 0,0,checkbox_2t,11
ch3 check_box1 0,0,checkbox_3t,11
check_boxes_end:

data_of_code dd 0
mouse_flag dd 0x0

;LABEL1_1
LABEL1_1VISIBLE dd 1
LABEL1_1LEFT dd 40
LABEL1_1TOP dd 228
LABEL1_1COLOR dd 0x000000
LABEL1_1CAP dd 8
LABEL1_1LEN dd 255
LABEL1_1CAPTION db 'LABEL1_1',0
          rb 255-8

;LABEL1_2
LABEL1_2VISIBLE dd 1
LABEL1_2LEFT dd 232
LABEL1_2TOP dd 172
LABEL1_2COLOR dd 0x000000
LABEL1_2CAP dd 8
LABEL1_2LEN dd 255
LABEL1_2CAPTION db 'MOUSE X:',0
          rb 255-8

;LABEL1_3
LABEL1_3VISIBLE dd 1
LABEL1_3LEFT dd 288
LABEL1_3TOP dd 172
LABEL1_3COLOR dd 0x000000
LABEL1_3CAP dd 1
LABEL1_3LEN dd 255
LABEL1_3CAPTION db '0',0
          rb 255-1

;LABEL1_4
LABEL1_4VISIBLE dd 1
LABEL1_4LEFT dd 232
LABEL1_4TOP dd 196
LABEL1_4COLOR dd 0x000000
LABEL1_4CAP dd 8
LABEL1_4LEN dd 255
LABEL1_4CAPTION db 'MOUSE Y:',0
          rb 255-8

;LABEL1_5
LABEL1_5VISIBLE dd 1
LABEL1_5LEFT dd 288
LABEL1_5TOP dd 196
LABEL1_5COLOR dd 0x000000
LABEL1_5CAP dd 1
LABEL1_5LEN dd 255
LABEL1_5CAPTION db '0',0
          rb 255-1

;EDIT1_1
EDIT1_1VISIBLE dd 1
EDIT1_1LEFT dd 88
EDIT1_1TOP dd 276
EDIT1_1COLOR dd 0x000000
EDIT1_1CAP dd 7
EDIT1_1LEN dd 255
EDIT1_1TEXT db 'EDIT1_1',0
          rb 255-7

;CHECKBOX1_1
CHECKBOX1_1VISIBLE dd 1
CHECKBOX1_1LEFT dd 232
CHECKBOX1_1TOP dd 52
CHECKBOX1_1COLOR dd 0x000000
CHECKBOX1_1CAP dd 11
CHECKBOX1_1LEN dd 255
CHECKBOX1_1CAPTION db 'CHECKBOX1_1',0
          rb 255-11

;CHECKBOX1_2
CHECKBOX1_2VISIBLE dd 1
CHECKBOX1_2LEFT dd 232
CHECKBOX1_2TOP dd 84
CHECKBOX1_2COLOR dd 0x000000
CHECKBOX1_2CAP dd 11
CHECKBOX1_2LEN dd 255
CHECKBOX1_2CAPTION db 'CHECKBOX1_2',0
          rb 255-11

;CHECKBOX1_3
CHECKBOX1_3VISIBLE dd 1
CHECKBOX1_3LEFT dd 232
CHECKBOX1_3TOP dd 116
CHECKBOX1_3COLOR dd 0x000000
CHECKBOX1_3CAP dd 11
CHECKBOX1_3LEN dd 255
CHECKBOX1_3CAPTION db 'CHECKBOX1_3',0
          rb 255-11

;BUTTON1_1
BUTTON1_1ID dd 2
BUTTON1_1VISIBLE dd 1
BUTTON1_1LEFT dd 88
BUTTON1_1TOP dd 308
BUTTON1_1WIDTH dd 75
BUTTON1_1HEIGHT dd 20
BUTTON1_1COLOR dd 0xaabbcc
BUTTON1_1CAP dd 9
BUTTON1_1LEN dd 255
BUTTON1_1CAPTION db 'BUTTON1_2',0
          rb 255-9
sc system_colors
align 16
procinfo process_information
meos_app_end
udata
