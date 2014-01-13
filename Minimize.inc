Declare Function SetWindow Lib "user32" Alias "SetWindowLongA" (hwnd As Long, nIndex As Long, dwNewLong As Long) As Long
Sub SetMinimize (Form as QForm)
Setwindow(Form.Handle, -8, 0)
Setwindow(Application.Handle, -8, Form.Handle)
End Sub
