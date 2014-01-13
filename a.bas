$Include "Rapidq.inc"
dim x as integer
dim y as integer
dim g as integer



Declare Sub Button1_2Click(Sender as QButton)
Declare Sub Panel1_2Click(Sender as QPanel)
Declare Sub MainFormMouseMove(X%, Y%, Shift%)
Declare Sub GroupBox1_1MouseMove(X%, Y%, Shift%)
Create MainForm as QForm
      Caption = "MainForm"
      Top     = 302
      Left    = 405
      Width   = 423
      Height  = 361
      OnMouseMove = MainFormMouseMove
End Create
Create Button1_1 as QButton
      Parent  = MainForm
      Top     = 288
      Left    = 88
      Width   = 75
      Height  = 25
      Caption = "Button1_2"

End Create
Create GroupBox1_1 as QGroupBox
      Parent  = MainForm
      Top     = 24
      Left    = 24
      Width   = 153
      Height  = 81
      Caption = "GroupBox1_1"
      Color   = &HF0F0F0

End Create
Create Edit1_1 as QEdit
      Parent  = MainForm
      Top     = 256
      Left    = 88
      Width   = 121
      Height  = 21
      Text    = "Edit1_1"
      Color   = &HFFFFFF
End Create
Create CheckBox1_1 as QCheckBox
      Parent  = MainForm
      Top     = 32
      Left    = 232
      Width   = 97
      Height  = 17
      Caption = "CheckBox1_1"
End Create
Create CheckBox1_2 as QCheckBox
      Parent  = MainForm
      Top     = 64
      Left    = 232
      Width   = 97
      Height  = 17
      Caption = "CheckBox1_2"
End Create
Create CheckBox1_3 as QCheckBox
      Parent  = MainForm
      Top     = 96
      Left    = 232
      Width   = 97
      Height  = 17
      Caption = "CheckBox1_3"
End Create
Create Panel1_2 as QPanel
      Parent  = MainForm
      Top     = 104
      Left    = 24
      Width   = 113
      Height  = 81
      Caption = "Panel1_2"
      Color   = &HF0F0F0
      OnMouseMove = GroupBox1_1MouseMove
      OnClick = Panel1_2Click
End Create
Create Label1_1 as QLabel
      Parent  = MainForm
      Top     = 208
      Left    = 40
      Width   = 44
      Height  = 13
      Caption = "Label1_1"
      Color   = &HF0F0F0
End Create
Create Label1_2 as QLabel
      Parent  = MainForm
      Top     = 152
      Left    = 232
      Width   = 44
      Height  = 13
      Caption = "mouse X:"
      Color   = &HF0F0F0
End Create
Create Label1_3 as QLabel
      Parent  = MainForm
      Top     = 152
      Left    = 288
      Width   = 44
      Height  = 13
      Caption = "0"
      Color   = &HF0F0F0
End Create
Create Label1_4 as QLabel
      Parent  = MainForm
      Top     = 176
      Left    = 232
      Width   = 44
      Height  = 13
      Caption = "mouse Y:"
      Color   = &HF0F0F0
End Create
Create Label1_5 as QLabel
      Parent  = MainForm
      Top     = 176
      Left    = 288
      Width   = 44
      Height  = 13
      Caption = "0"
      Color   = &HF0F0F0
End Create
print "dd"+chr$(32)+"dd"


MainForm.ShowModal
 

 
Sub Button1_2Click(Sender as QButton)
label1_1.Caption = edit1_1.Text
'Code here....
End Sub
 
Sub Panel1_2Click(Sender as QPanel)
label1_1.Caption = "Panel clicked"
'Code here....
End Sub
 
Sub MainFormMouseMove(X%, Y%, Shift%)

'Code here....
End Sub
 
Sub GroupBox1_1MouseMove(X%, Y%, Shift%)
x = mousex
y = mousey
label1_3.Caption = str$(x)
label1_5.Caption = str$(y)

'Code here....
End Sub
