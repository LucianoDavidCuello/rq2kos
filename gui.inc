
include 'macros.inc'
include 'struct.inc'
include 'rq2kos.inc'

rq_id	     equ [edi]		     ;ширина компонента
rq_tipo      equ [edi+2]	     ;положение по оси х
rq_parent    equ [edi+4]	     ;положение по оси у
rq_visible   equ [edi+8]
rq_left      equ [edi+10]
rq_top	     equ [edi+14]
rq_width     equ [edi+18]
rq_height    equ [edi+22]
rq_color     equ [edi+26]

struc qbutton
{
local normal
.id dw 0
.tipo dw 11
.parent dd 0
.visible dw 1
.left dd 0
.top dd 0
.width dd 0
.height db 0
.color	db 0
.caption rb 256
.enabled dw 1
; para los hilos hijos
.align dw 0
.numbmps dw 0
.bmp rb 256
.hint rb 256
.popupmenu db 0
.showhint dw 0
;events
.onclick db 0
.onmousemove db 0
.onkeypress db 0
.event:

.draw:
mov di,.parent
cmp rq_tipo, 10
je normal

normal:
 boton .left,.top,.width,.height,.id,.texto,.color,.visible
ret
}


struc qlabeljuu left
{
.id dw 0
.parent db 0
.visible dw 1
.left dd left
.top dd 0
.width dd 0
.height db 0
.caption rb 256
.align dw 0
.numbmps dw 0
.bmp rb 256
.enabled dw 1
.hint rb 256
.popupmenu db 0
.showhint dw 0
.draw:
ret
}
