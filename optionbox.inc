;��������� OptionBox (�᭮��� �� Checkbox)
;��஬��� �������୮��� Maxxxx32, Diamond, Heavyiron, � ��㣨� �ணࠬ���⠬, � �� �ணࠬ���, ���
;������ � �� ᬮ� �� ������� ��� ���������. 
;21.02.2007 ����୨���� � �����প� ���� ࠧ��� ��ਠ�⮢ � �ᯮ�짮������ �� 梥⮢ � ��ன �奬��
;19.02.2007 ��饥 ���襭�� ����, 㬥��襭�� ࠧ��� � �ᯮ�짮����� ��⥬��� 梥⮢ ��� �⮡ࠦ���� optionkbox
;16.02.2007 ��� ᮧ����� ���������
;<Lrz>  - ������ ����ᥩ  www.lrz.land.ru

macro version_op	   ;��� ᮢ���⨬��� � ���묨 ����ﬨ optionbox �� 梥� �������� ��窠��
{
op_struc_size=26
option_group equ [edi]
op_left equ [edi+4]    ;���न��� ��砫� �ᮢ���� �� �
op_top equ [edi+6]   ;���न��� ��砫� �ᮢ���� �� �
op_color equ [edi+8]
op_border_color equ [edi+12] ; or [edi+4] ;梥� ࠬ�� checkbox �� ����� ������ ᠬ����⥫쭮
op_text_color equ   [edi+16];[edi+4]  ;梥� ⥪��
op_text_ptr equ [edi+20]    ;㪠��⥫� �� ��砫� ⥪�⮢�� ��ப� 
op_text_length equ [edi+24] ;����� ������ (2^64 ⠪�� ����� ����� ���� ⥪��)
}

macro	version_op1	   ;�த������ �����, �ᯮ���� 梥� ᪨��. 
{
op_struc_size=14
option_group equ [edi]
op_left equ [edi+4]    ;���न��� ��砫� �ᮢ���� �� �
op_top equ [edi+6]   ;���न��� ��砫� �ᮢ���� �� �
op_color equ [sc.work] ;
op_border_color equ [sc.work_graph] ; or [edi+4] ;梥� ࠬ�� checkbox �� ����� ������ ᠬ����⥫쭮
op_text_color equ   [sc.work_text];[edi+4]  ;梥� ⥪��
op_text_ptr equ [edi+8]    ;㪠��⥫� �� ��砫� ⥪�⮢�� ��ப� 
op_text_length equ [edi+12] ;����� ������ (2^64 ⠪�� ����� ����� ���� ⥪��)
}


macro use_option_box
{
option_box:
.draw:
pusha	;��࠭�� �� ॣ�����
op_text_margin=4     ;����ﭨ� �� ��אַ㣮�쭨�� 祪 ���� �� ������ 
op_size=11	     ;ࠧ��� ������ 祪 ���� 
       mov eax,13 
       mov ebx,op_left 
       shl ebx,16 
       add ebx,op_size 
       mov ecx,op_top 
       shl ecx,16 
       add ecx,op_size 
       mov edx,op_border_color 
       mcall ;��㥬 ࠬ�� 

       mov edx,op_color 
       add ebx,1 shl 16 - 2 
       add ecx,1 shl 16 - 2 
       mcall ;����訢��� ����७���� 祪���� 

	mov	eax,option_group
	mov	dword eax,[eax]
	cmp	eax,edi
	jne	@f
	call	.draw_op  ;���ᮢ��� ����祭�� 祪 ����
;----------------------------
;���� �㤠 �㤥� �ந������ �뢮� ⥪��
;----------------------------
@@:	movzx	ebx,word op_left	;����㧨�� ���祭�� � ��� 祪 ����
	add	ebx,(op_size+op_text_margin) ;�������� ࠧ��� ��஭� � ����ﭨ� �� ���஬ ��筥��� �뢮� ⥪��
	shl	ebx,16		;ᤢ���� �� 16 ࠧ�冷� � ���� (㬭���� �� 65536)
	mov	bx,op_top	;����㧨� ���祭�� �� y
	add	ebx,(op_size-9+1)	;������� ���祭�� ����� ��஭� -9+1
	mov	ecx,op_text_color	;����㧨� 梥� ������
	
	mov	edx,op_text_ptr 	;㪠��� ���� �� �㤠 �㦭� �뢮���� ��ப�
	movzx	esi,word op_text_length ;����㧨� ����� ������ � esi
	;���ᥬ � eax ���祭�� �뢮�� ������ �� �����
	mov	eax,4
	mcall		;�뢮� 
popa				;����⠭����� ���祭�� ॣ���஢ �� �⥪�
ret				;�멤�� �� ��楤���

.clear_op:			;���⪠ 祪 ����
	mov	edx,op_color	;梥� ����� 祪 ����
	jmp	@f		;����᫮��� ��릮� �� ������ ���� @@

.draw_op:	     ;���ᮢ��� ����祭�� 祪 ����

	mov   edx,op_border_color	;����㧨�� 梥�
@@:
	movzx ebx,word op_left	;����㧨�� ���न���� �� �
	add   ebx,(op_size/3)	;�������� (��஭� ��אַ㣮�쭨��/3)
	shl   ebx,16		;ᤢ���� �� 16 ࠧ�冷� � ���� (㬭���� �� 65536)
	mov   bx,(op_size/2)	;����㧨�� (��஭� ��אַ㣮�쭨��/2)
	mov   bp,bx		;��࠭�� ॣ���� bx � ॣ���� 㪠��⥫� ����
	;push        bx
	movzx ecx,word op_top ;����㧨�� ���न���� �� �
	mov   eax,13	      ;� eax - ���祭�� �㭪樨 ��� �뢮�� ������ �.�. �� ��� ��אַ㣮�쭨��, ����� �⮡ࠦ��� ����祭�� ��������� 祪 ����
	add   ecx,(op_size/3) ;�������� (��஭� ��אַ㣮�쭨��/3)
	shl   ecx,16	      ;ᤢ���� �� 16 ࠧ�冷� � ���� (㬭���� �� 65536)
	mov   cx,bp	      ;����㧨� ���祭�� ॣ���� 㪠��⥫� ���� � cx
	mcall		 ;�뢮�
ret				;��� �� ��楤���

.mouse: 		;��ࠡ�⪠ ��� 
pusha
	mov	eax,37		;�㤥� �� � ������ �᫨ � ��� �� - ���� �����
	mov	ebx,2		;����� � ॣ���� ���祭�� 2
	mcall		;�஢�ઠ �� ����� �� ���짮��⥫� ������ ��誨
	test	eax,eax    ;�஢�ઠ �᫨ � ��� � eax=0, � ��⠭���� 䫠� � �멤��
	jnz	@f	   ;��३� �� ������ ���� @@
	popa			;�᫨ ��祣� �� �ந��諮, � ����⠭���� ���祭�� ॣ���஢ �� �⥪�
	ret			;��室
@@:
	movzx	esi,word op_text_length ;����㧨�� ���-�� ᨬ����� � ⥪�⮢�� ��ப�
	;��������� �� 6 ����஥ 㬭������ ����� ��ᯮ�짮������ ��� �� ��⮤��, �� �� ����� ������� (386,486,P1)����॥ �㤥� � ������樥� Lea
	;lea    esi,[eax*2+eax]
	;shl    eax,1
	imul	esi,6		    ; ��� ����� � ⠪ 㬭����� �� 6
	xor	ebx,ebx
	add	esi,op_text_margin   ;�������� 3 - ����ﭨ� �� 祪 ���� �� ������
	
	mov	eax,37		;����稬 ���न���� ��誨 
	inc	ebx		;�������� 1
	mcall		     ;������� ���न���� ����� �⭮�⥫쭮 ���� 

	movzx	ebx,word op_top 	  ;����㧨�� � bx ���祭�� ���न���� �
	cmp	ax,bx		    ;�ࠢ���� � � ���न��⮩ �����
	jl	.mouse_end	    ;SF <> OF �᫨ ����� 
	add	ebx,op_size	     ;�������� ࠧ��� 
	cmp	ax,bx		    ;�ࠢ����
	jg	.mouse_end	    ;ZF = 0 � SF = OF �᫨ ����� 
	
	shr	eax,16		    ;ࠧ����� �� 65536 ��� ���� ᤢ���� ���� �� 16 ���祭��
	movzx	ebx,word op_left	  ;�ந������ �������筮� �ࠢ�����
	cmp	ax,bx		     ;�ࠢ���� ॣ�����
	jl	.mouse_end	     ;�᫨ �����
	add	ebx,op_size	     ;�������� ����� ��஭� ��אַ㣮�쭨��
	add	ebx,esi 	     ;����� � ���祭�� �� � �� � ����� ������ � 祪�����
	cmp	ax,bx		     ;��ࠢ���� ॣ�����
	jg	.mouse_end	     ;�᫨ ����� 
	mov	eax,option_group
	mov	[eax],edi

.mouse_end:
popa				  ;����⠭����� ॣ����� �� �⥪�
ret				  ;���
}

struc option_box1 point_gr,left,top,text,text_length
{	;������� ��ࠬ��஢ ��� 祪 ����
.option_group: dd point_gr	;㪠��⥫� �� ࠧ��饭�� edi - �����䨪��� optibox
.left: dw left	;+0     ;��������� �� �
.top: dw top	;+2     ;��������� �� �
.text: dd text	     ;+16               ���� � ���� �ணࠬ�� ��� �ᯮ����� ⥪���
.text_length: dw text_length ; +20      ����� ⥪��
}
struc option_box point_gr,left,top,color,border_color,text_color,text,text_length
{	;������� ��ࠬ��஢ ��� 祪 ����
.option_group: dd point_gr	;㪠��⥫� �� ࠧ��饭�� edi - �����䨪��� optibox
.left: dw left	;+0     ;��������� �� �
.top: dw top	;+2     ;��������� �� �
.color: dd color
.border_color: dd border_color; or [edi+4] ;梥� ࠬ�� checkbox �� ����� ������ ᠬ����⥫쭮
.text_color:   dd text_color;[edi+4]  ;梥� ⥪��
.text: dd text	     ;+16               ���� � ���� �ணࠬ�� ��� �ᯮ����� ⥪���
.text_length: dw text_length ; +20      ����� ⥪��
}

op_flag_en=10b
macro draw_option_boxes start,end	;�ᮢ��� 祪 �����
{

	mov	edi,start			;�����⥫� �� ��砫� ������ 祪 ���ᮢ �.�. �� ��砫� ������ ��ࢮ�� 祪����
	mov	ecx,((end-start)/op_struc_size) ;������⢮ 祪 ���ᮢ
@@:
	call	option_box.draw 		 ;�⮡ࠧ��� 祪 ����
	add	edi,op_struc_size		;�����⥫� �� ��᫥���騥 祪 �����  �.�. +28
	loop	@b	;��룭��� �᫨ � ecx/cx ���祭�� �� 0 �� ������ @@
}
macro mouse_option_boxes start,end	;��⠭���� 祪 ���ᮢ, � ����ᨬ��� �� ᮡ���
{
	local .home,.nxtm
	mov	edi,start		; �����⥫� �� ��砫� ������ 祪 ���ᮢ �.�. �� ��砫� ������ ��ࢮ�� 祪����
	mov	ecx,((end-start)/op_struc_size) ;������⢮ 祪 ���ᮢ
@@:
	call	option_box.mouse		;�஢�ઠ ��誨 � ��ࠡ�⪠ ᮡ�⨩
	add	edi,op_struc_size	;�����⥫� �� ��᫥���騥 祪 �����
	loop	@b	;��룭��� �᫨ � ecx/cx ���祭�� �� 0 �� ������ @@

	mov	edi,start		; �����⥫� �� ��砫� ������ 祪 ���ᮢ �.�. �� ��砫� ������ ��ࢮ�� 祪����
	mov	ecx,((end-start)/op_struc_size) ;������⢮ 祪 ���ᮢ

.home:
	mov	eax,[edi]	;op_optibox_gr
	mov	dword eax,[eax]

	pusha

	cmp	eax,edi
	jne	@f
	
	call	option_box.draw_op
	jmp	.nxtm
@@:	call	option_box.clear_op

.nxtm:	popa
	add	edi,op_struc_size		;�����⥫� �� ��᫥���騥 祪 �����  �.�. +28
	loop	.home

}