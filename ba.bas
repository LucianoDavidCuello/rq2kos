$Include "Rapidq.inc"
 
Declare Sub Button1_1Click(Sender as QButton)
Declare Sub CheckBox1_1Click(Sender as QCheckBox)
Create MainForm as QForm
      Caption = "Rapidq en Kolibri OS"
      Top     = 132
      Left    = 218
      Width   = 297
      Height  = 422
      BorderStyle = bsSizeable
End Create
Create Button1_1 as QButton
      Parent  = MainForm
      Top     = 184
      Left    = 16
      Width   = 75
      Height  = 25
      Caption = "guarda"
      OnClick = Button1_1Click
End Create
Create Edit1_1 as QEdit
      Parent  = MainForm
      Top     = 24
      Left    = 80
      Width   = 121
      Height  = 21
      Text    = "david cuello"
      Color   = &HFFFFFF
End Create
Create CheckBox1_1 as QCheckBox
      Parent  = MainForm
      Top     = 88
      Left    = 56
      Width   = 97
      Height  = 17
      Caption = "mujer"
      OnClick = CheckBox1_1Click
End Create
Create Label1_1 as QLabel
      Parent  = MainForm
      Top     = 32
      Left    = 16
      Width   = 35
      Height  = 13
      Caption = "nombre"
      Color   = &HF0F0F0
End Create
Create Button1_2 as QButton
      Parent  = MainForm
      Top     = 184
      Left    = 192
      Width   = 75
      Height  = 25
      Caption = "edita"
End Create
Create Button1_3 as QButton
      Parent  = MainForm
      Top     = 184
      Left    = 104
      Width   = 75
      Height  = 25
      Caption = "sale"
End Create
Create Edit1_2 as QEdit
      Parent  = MainForm
      Top     = 48
      Left    = 80
      Width   = 121
      Height  = 21
      Text    = "24"
      Color   = &HFFFFFF
End Create
Create Label1_2 as QLabel
      Parent  = MainForm
      Top     = 48
      Left    = 16
      Width   = 44
      Height  = 13
      Caption = "edad"
      Color   = &HF0F0F0
End Create
Create Label1_3 as QLabel
      Parent  = MainForm
      Top     = 272
      Left    = 80
      Width   = 132
      Height  = 13
      Caption = "Prueba de Form en Kolibrios"
      Color   = &HF0F0F0
End Create
Create CheckBox1_2 as QCheckBox
      Parent  = MainForm
      Top     = 104
      Left    = 56
      Width   = 97
      Height  = 17
      Caption = "hombre"
      Checked = True
End Create
Create RadioButton1_1 as QRadioButton
      Parent  = MainForm
      Top     = 312
      Left    = 16
      Width   = 113
      Height  = 17
      Caption = "RadioButton1_1"
End Create
Create RadioButton1_2 as QRadioButton
      Parent  = MainForm
      Top     = 328
      Left    = 16
      Width   = 113
      Height  = 17
      Caption = "RadioButton1_2"
End Create
Create RadioButton1_3 as QRadioButton
      Parent  = MainForm
      Top     = 344
      Left    = 16
      Width   = 113
      Height  = 17
      Caption = "RadioButton1_3"
End Create
Create RadioButton1_4 as QRadioButton
      Parent  = MainForm
      Top     = 312
      Left    = 152
      Width   = 113
      Height  = 17
      Caption = "RadioButton1_4"
      Checked = True
End Create
Create RadioButton1_5 as QRadioButton
      Parent  = MainForm
      Top     = 328
      Left    = 152
      Width   = 113
      Height  = 17
      Caption = "RadioButton1_5"
End Create
$Include "Minimize.inc"

SetMinimize(MainForm)
MainForm.ShowModal
 
Sub Button1_1Click(Sender as QButton)
mainform.Caption=edit1_1.Text
'Code here....
End Sub
 
Sub CheckBox1_1Click(Sender as QCheckBox)
'Code here....
End Sub
