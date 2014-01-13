@^ fix macro comment {
^@ fix }

; -------------------------
macro library [lname,fname]
{
  forward
    dd __#lname#_library_table__,__#lname#_library_name__
  common
    dd 0
  forward
    align 4
    __#lname#_library_name__ db fname,0
}

macro import lname,[name,sname]
{
  common
    align 4
    __#lname#_library_table__:
  forward
    if used name
      name dd __#name#_import_name__
    end if
  common
    dd 0
  forward
    if used name
      align 4
      __#name#_import_name__ db sname,0
    end if
}

macro export [name,sname]
{
  forward
    dd __#name#_export_name__,name
  common
    dd 0
  forward
    align 4
    __#name#_export_name__ db sname,0
}
; -------------------------

macro m2m dest,src {
 push src
 pop  dest
}


macro iglobal {
  IGlobals equ IGlobals,
  macro __IGlobalBlock { }

macro uglobal {
  UGlobals equ UGlobals,
  macro __UGlobalBlock { }

endg fix }	; Use endg for ending iglobal and uglobal blocks.


macro IncludeIGlobals{
  macro IGlobals dummy,[n] \{ __IGlobalBlock
     purge __IGlobalBlock  \}
  match I, IGlobals \{ I \} }

macro IncludeUGlobals{
  macro UGlobals dummy,[n] \{
    \common
      \local begin, size
      begin = $
      virtual at $
    \forward
      __UGlobalBlock
      purge __UGlobalBlock
    \common
      size = $ - begin
    end virtual
    rb size
  \}
  match U, UGlobals \{ U \} }

uglobal
endg

iglobal
endg


; new application structure
macro meos_app_start
 {
  use32
  org 0x0

  db 'MENUET01'
  dd 0x01
  dd __start
  dd __end
  dd __memory
  dd __stack

  if used __params & ~defined __params
    dd __params
  else
    dd 0x0
  end if

  dd 0x0
 }
MEOS_APP_START fix meos_app_start

macro code
 {
  __start:
 }
CODE fix code

macro data
 {
  __data:
  IncludeIGlobals
 }
DATA fix data

macro udata
 {
  if used __params & ~defined __params
    __params:
      db 0
    __end:
      rb 255
  else
    __end:
  end if
  __udata:
  IncludeUGlobals
 }
UDATA fix udata

macro meos_app_end
 {
  align 32
  rb 2048
  __stack:
  __memory:
 }
MEOS_APP_END fix meos_app_end


; macro for defining multiline text data
struc mstr [sstring]
 {
  forward
    local ssize
    virtual at 0
      db sstring
      ssize = $
    end virtual
    dd ssize
    db sstring
  common
    dd -1
 }

; macro for defining multiline text data
struc mls [sstring]
 {
  forward
    local ssize
    virtual at 0
      db sstring  ; mod
      ssize = $
    end virtual
    db ssize
    db sstring
  common
    db -1	  ; mod
 }



; strings
macro sz name,[data] {	     ; from MFAR [mike.dld]
 common
  if used name
   name db data
   .size = $-name
  end if
}

macro lsz name,[lng,data] {  ; from MFAR [mike.dld]
 common
  if used name
   label name
 forward
  if lang eq lng
   db data
  end if
 common
   .size = $-name
  end if
}

macro szc name,elsz,[data] {	     ; from MFAR [mike.dld]
 common
  local s,m
  m = 0
  if used name
   label name
 forward
   virtual at 0
    db data
    s = $
   end virtual
   d#elsz s
   if m < s
    m = s
   end if
   db data
 common
   .size = $-name
   .maxl = m
  end if
}

macro lszc name,elsz,[lng,data] {  ; from MFAR [mike.dld]
 common
  local s,m,c
  m = 0
  c = 0
  if used name
   label name
 forward
  if lang eq lng
   virtual at 0
    db data
    s = $
   end virtual
   d#elsz s
   if m < s
    m = s
   end if
   db data
   c = c+1
  end if
 common
   .size  = $-name
   .maxl  = m
   .count = c
  end if
}


; easy system call macro
macro mpack dest, hsrc, lsrc
{
  if (hsrc eqtype 0) & (lsrc eqtype 0)
    mov dest, (hsrc) shl 16 + lsrc
  else
    if (hsrc eqtype 0) & (~lsrc eqtype 0)
      mov dest, (hsrc) shl 16
      add dest, lsrc
    else
      mov dest, hsrc
      shl dest, 16
      add dest, lsrc
    end if
  end if
}

macro __mov reg,a,b {	    ; mike.dld
 if (~a eq)&(~b eq)
   mpack reg,a,b
 else if (~a eq)&(b eq)
   mov reg,a
 end if
}


include 'config.inc'
;__CPU_type     equ     p5
SYSENTER_VAR	equ	0

macro mcall a,b,c,d,e,f {   ; mike.dld, updated by Ghost for Fast System Calls
 local	..ret_point
 __mov eax,a
 __mov ebx,b
 __mov ecx,c
 __mov edx,d
 __mov esi,e
 __mov edi,f

 if __CPU_type eq p5
	int	0x40
 else
  if __CPU_type eq p6
	push	ebp
	mov	ebp, esp
	push	..ret_point	; it may be 2 or 5 byte
	sysenter
 ..ret_point:
	pop	edx
	pop	ecx

  else
   if __CPU_type eq k6
	push	ecx
	syscall
	pop	ecx
   else
	display 'ERROR : unknown CPU type (set to p5)', 10, 13
	__CPU_type equ p5
	int	0x40
   end if
  end if
 end if
}


; -------------------------
macro header a,[b] {
 common
  use32
  org 0
  db 'MENUET',a
 forward
  if b eq
   dd 0
  else
   dd b
  end if }
macro section name { align 16
 label name }
macro func name {
 if ~used name
  display 'FUNC NOT USED: ',`name,13,10
 else
  align 4
  name:
  ;diff16 `name,0,name
;pushad
;pushfd
;dps `name
;newline
;mcall 5,1
;popfd
;popad
}
macro endf { end if }

macro diff16 title,l1,l2
 {
  local s,d
  s = l2-l1
  display title,': 0x'
  repeat 8
   d = '0' + s shr ((8-%) shl 2) and $0F
   if d > '9'
    d = d + 'A'-'9'-1
   end if
   display d
  end repeat
  display 13,10
 }

macro diff10 title,l1,l2
 {
  local s,d,z,m
  s = l2-l1
  z = 0
  m = 1000000000
  display title,': '
  repeat 10
   d = '0' + s / m
   s = s - (s/m)*m
   m = m / 10
   if d <> '0'
    z = 1
   end if
   if z <> 0
    display d
   end if
  end repeat
  display 13,10
 }

; optimize the code for size
__regs fix <eax,ebx,ecx,edx,esi,edi,ebp,esp>

macro add arg1,arg2
 {
   if (arg2 eqtype 0)
      if (arg2) = 1
	 inc arg1
      else
	 add arg1,arg2
      end if
   else
      add arg1,arg2
   end if
 }

macro sub arg1,arg2
 {
   if (arg2 eqtype 0)
      if (arg2) = 1
	 dec arg1
      else
	 sub arg1,arg2
      end if
   else
      sub arg1,arg2
   end if
 }

macro mov arg1,arg2
 {
   if (arg1 in __regs) & ((arg2 eqtype 0) | (arg2 eqtype '0'))
      if (arg2) = 0
	 xor arg1,arg1
      else if (arg2) = 1
	 xor arg1,arg1
	 inc arg1
      else if (arg2) = -1
	 or  arg1,-1
      else if (arg2) > -128 & (arg2) < 128
	 push arg2
	 pop  arg1
      else
	 mov  arg1,arg2
      end if
   else
      mov arg1,arg2
   end if
 }


macro RGB [a] {
 common
  match (r=,g=,b),a \{
   \dd ((r) shl 16) or ((g) shl 8) or (b)
  \}
}


struc POINT _t,_dx,_dy {
 .x _t _dx
 .y _t _dy
}

; structure definition helper

macro struct name
 { fields@struct equ name
   match child parent, name \{ fields@struct equ child,fields@\#parent \}
   sub@struct equ
   struc db [val] \{ \common fields@struct equ fields@struct,.,db,<val> \}
   struc dw [val] \{ \common fields@struct equ fields@struct,.,dw,<val> \}
   struc du [val] \{ \common fields@struct equ fields@struct,.,du,<val> \}
   struc dd [val] \{ \common fields@struct equ fields@struct,.,dd,<val> \}
   struc dp [val] \{ \common fields@struct equ fields@struct,.,dp,<val> \}
   struc dq [val] \{ \common fields@struct equ fields@struct,.,dq,<val> \}
   struc dt [val] \{ \common fields@struct equ fields@struct,.,dt,<val> \}
   struc rb count \{ fields@struct equ fields@struct,.,db,count dup (?) \}
   struc rw count \{ fields@struct equ fields@struct,.,dw,count dup (?) \}
   struc rd count \{ fields@struct equ fields@struct,.,dd,count dup (?) \}
   struc rp count \{ fields@struct equ fields@struct,.,dp,count dup (?) \}
   struc rq count \{ fields@struct equ fields@struct,.,dq,count dup (?) \}
   struc rt count \{ fields@struct equ fields@struct,.,dt,count dup (?) \}
   macro db [val] \{ \common \local anonymous
		     fields@struct equ fields@struct,anonymous,db,<val> \}
   macro dw [val] \{ \common \local anonymous
		     fields@struct equ fields@struct,anonymous,dw,<val> \}
   macro du [val] \{ \common \local anonymous
		     fields@struct equ fields@struct,anonymous,du,<val> \}
   macro dd [val] \{ \common \local anonymous
		     fields@struct equ fields@struct,anonymous,dd,<val> \}
   macro dp [val] \{ \common \local anonymous
		     fields@struct equ fields@struct,anonymous,dp,<val> \}
   macro dq [val] \{ \common \local anonymous
		     fields@struct equ fields@struct,anonymous,dq,<val> \}
   macro dt [val] \{ \common \local anonymous
		     fields@struct equ fields@struct,anonymous,dt,<val> \}
   macro rb count \{ \local anonymous
		     fields@struct equ fields@struct,anonymous,db,count dup (?) \}
   macro rw count \{ \local anonymous
		     fields@struct equ fields@struct,anonymous,dw,count dup (?) \}
   macro rd count \{ \local anonymous
		     fields@struct equ fields@struct,anonymous,dd,count dup (?) \}
   macro rp count \{ \local anonymous
		     fields@struct equ fields@struct,anonymous,dp,count dup (?) \}
   macro rq count \{ \local anonymous
		     fields@struct equ fields@struct,anonymous,dq,count dup (?) \}
   macro rt count \{ \local anonymous
		     fields@struct equ fields@struct,anonymous,dt,count dup (?) \}
   macro union \{ fields@struct equ fields@struct,,union,<
		  sub@struct equ union \}
   macro struct \{ fields@struct equ fields@struct,,substruct,<
		  sub@struct equ substruct \}
   virtual at 0 }

macro ends
 { match , sub@struct \{ restruc db,dw,du,dd,dp,dq,dt
			 restruc rb,rw,rd,rp,rq,rt
			 purge db,dw,du,dd,dp,dq,dt
			 purge rb,rw,rd,rp,rq,rt
			 purge union,struct
			 match name=,fields,fields@struct \\{ fields@struct equ
							      make@struct name,fields
							      fields@\\#name equ fields \\}
			 end virtual \}
   match any, sub@struct \{ fields@struct equ fields@struct> \}
   restore sub@struct }

macro make@struct name,[field,type,def]
 { common
    if $
     display 'Error: definition of ',`name,' contains illegal instructions.',0Dh,0Ah
     err
    end if
    local define
    define equ name
   forward
    local sub
    match , field \{ make@substruct type,name,sub def
		     define equ define,.,sub, \}
    match any, field \{ define equ define,.#field,type,<def> \}
   common
    match fields, define \{ define@struct fields \} }

macro define@struct name,[field,type,def]
 { common
    local list
    list equ
   forward
    if ~ field eq .
     name#field type def
     sizeof.#name#field = $ - name#field
    else
     rb sizeof.#type
    end if
    local value
    match any, list \{ list equ list, \}
    list equ list <value>
   common
    sizeof.#name = $
    restruc name
    match values, list \{
    struc name value \\{
    match any, fields@struct \\\{ fields@struct equ fields@struct,.,name,<values> \\\}
    match , fields@struct \\\{ label .
   forward
     match , value \\\\{ field type def \\\\}
     match any, value \\\\{ field type value
			   if ~ field eq .
			    rb sizeof.#name#field - ($-field)
			   end if \\\\}
   common \\\} \\} \} }

macro enable@substruct
 { macro make@substruct substruct,parent,name,[field,type,def]
    \{ \common
	\local define
	define equ parent,name
       \forward
	\local sub
	match , field \\{ match any, type \\\{ enable@substruct
					       make@substruct type,name,sub def
					       purge make@substruct
					       define equ define,.,sub, \\\} \\}
	match any, field \\{ define equ define,.\#field,type,<def> \\}
       \common
	match fields, define \\{ define@\#substruct fields \\} \} }

enable@substruct

macro define@union parent,name,[field,type,def]
 { common
    virtual at 0
   forward
    if ~ field eq .
     virtual at 0
      parent#field type def
      sizeof.#parent#field = $ - parent#field
     end virtual
     if sizeof.#parent#field > $
      rb sizeof.#parent#field - $
     end if
    else if sizeof.#type > $
     rb sizeof.#type - $
    end if
   common
    sizeof.#name = $
    end virtual
    struc name [value] \{ \common
    label .\#name
    last@union equ
   forward
    match any, last@union \\{ virtual at .\#name
			       field type def
			      end virtual \\}
    match , last@union \\{ match , value \\\{ field type def \\\}
			   match any, value \\\{ field type value \\\} \\}
    last@union equ field
   common rb sizeof.#name - ($ - .\#name) \} }

macro define@substruct parent,name,[field,type,def]
 { common
    virtual at 0
   forward
    if ~ field eq .
     parent#field type def
     sizeof.#parent#field = $ - parent#field
    else
     rb sizeof.#type
    end if
    local value
   common
    sizeof.#name = $
    end virtual
    struc name value \{
    label .\#name
   forward
     match , value \\{ field type def \\}
     match any, value \\{ field type value
			  if ~ field eq .
			   rb sizeof.#parent#field - ($-field)
			  end if \\}
   common \} }


struct RECT
  left	 dd ?
  top	 dd ?
  right  dd ?
  bottom dd ?
ends

struct BOX
  left	 dd ?
  top	 dd ?
  width  dd ?
  height dd ?
ends

; structures used in MeOS
struct process_information
  cpu_usage		  dd ?	; +0
  window_stack_position   dw ?	; +4
  window_stack_value	  dw ?	; +6
			  dw ?	; +8
  process_name		  rb 12 ; +10
  memory_start		  dd ?	; +22
  used_memory		  dd ?	; +26
  PID			  dd ?	; +30
  box			  BOX	; +34
  slot_state		  dw ?	; +50
			  dw ?	; +52
  client_box		  BOX	; +54
  wnd_state		  db ?	; +70
  rb (1024-71)
ends

struct system_colors
  frame 	   dd ?
  grab		   dd ?
  grab_button	   dd ?
  grab_button_text dd ?
  grab_text	   dd ?
  work		   dd ?
  work_button	   dd ?
  work_button_text dd ?
  work_text	   dd ?
  work_graph	   dd ?
ends

struct FILEDATE
  Second db ?
  Minute db ?
  Hour	 db ?
	 db ?
  Day	 db ?
  Month  db ?
  Year	 dw ?
ends

struct FILEINFO
  Attributes dd ?
  IsUnicode  db ?
	     db 3 dup(?)
  DateCreate FILEDATE
  DateAccess FILEDATE
  DateModify FILEDATE
  Size	     dq ?
ends

; constants

; events
EV_IDLE        = 0
EV_TIMER       = 0
EV_REDRAW      = 1
EV_KEY	       = 2
EV_BUTTON      = 3
EV_EXIT        = 4
EV_BACKGROUND  = 5
EV_MOUSE       = 6
EV_IPC	       = 7
EV_STACK       = 8

; event mask bits for function 40
EVM_REDRAW     =	1b
EVM_KEY        =       10b
EVM_BUTTON     =      100b
EVM_EXIT       =     1000b
EVM_BACKGROUND =    10000b
EVM_MOUSE      =   100000b
EVM_IPC        =  1000000b
EVM_STACK      = 10000000b

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


macro boton x,y,x2,y2,id,texto,color,visible,parent
{
 local no_visiblexx
    xor  eax,eax
    mov  ax,word [visible]
    cmp  ax,0
    je	 no_visiblexx
    mov  ax,word [parent]
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
    plabel x,y,texto,color,7
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
;mov [color],0x000000
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
len texto



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


;x = x2 / 2
;

;mov [color],0x000000

plabel temp1,temp2,texto,cl_Black,0

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
;mov [color],0x000000
    mov  edx,[color]

mov eax,13
mcall

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

    xor bx,bx
    mov  ebx,dword [x]
    add  ebx,3
    shl  ebx,16
    add  bx,ax
    add bx,2	

    mov  ecx,dword [y]
    sub  ecx,6
    shl  ecx,16
    add  ecx,12
    xor edx,edx
;mov [color],0x000000
    mov  edx,[color]

mov eax,13
mcall

    mov [ttemp1],0x000000


plabel temp1,temp2,texto,ttemp1,0

 no_visiblexx:
}

macro plabel x,y,texto,color,tipo
 {
    mov  eax,4
    mov  ebx,[x]
    add  bx,tipo
    shl  ebx,16
    add  ebx,[y]
    add  bx,tipo
    mov  ecx,0x00000000
   ; mov  [addr],dword texto
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

macro draw objeto
{



}
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