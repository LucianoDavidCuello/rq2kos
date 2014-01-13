$Include "Rapidq.inc"
 
Declare Sub Button1_1Click(Sender as QButton)
Create MainForm as QForm
      Caption = "MainForm"
      Top     = 230
      Left    = 329
      Width   = 477
      Height  = 110
End Create
Create Button1_1 as QButton
      Parent  = MainForm
      Top     = 40
      Left    = 192
      Width   = 75
      Height  = 25
      Caption = "Button1_1"
      OnClick = Button1_1Click
End Create
Create Label1_1 as QLabel
      Parent  = MainForm
      Top     = 16
      Left    = 40
      Width   = 44
      Height  = 13
      Caption = "Label1_1"
      Color   = &HF0F0F0
End Create
Create Edit1_1 as QEdit
      Parent  = MainForm
      Top     = 8
      Left    = 168
      Width   = 121
      Height  = 21
      Text    = "Edit1_1"
      Color   = &HFFFFFF
End Create
Create Edit1_2 as QEdit
      Parent  = MainForm
      Top     = 8
      Left    = 304
      Width   = 121
      Height  = 21
      Text    = "Edit1_2"
      Color   = &HFFFFFF
End Create
$Include "Minimize.inc"

SetMinimize(MainForm)
MainForm.ShowModal
 
Sub Button1_1Click(Sender as QButton)
label1_1.Caption = edit1_1.Text + edit1_2.Text
'Code here....
End Sub
