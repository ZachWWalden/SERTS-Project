<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.ComListBox = New System.Windows.Forms.ListBox()
        Me.Connect = New System.Windows.Forms.Button()
        Me.Disconnect = New System.Windows.Forms.Button()
        Me.ComResultTextBox = New System.Windows.Forms.TextBox()
        Me.File_List = New System.Windows.Forms.ListBox()
        Me.Show_Files = New System.Windows.Forms.Button()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.Button4 = New System.Windows.Forms.Button()
        Me.Button5 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'SerialPort1
        '
        Me.SerialPort1.PortName = "COM4"
        '
        'ComListBox
        '
        Me.ComListBox.FormattingEnabled = True
        Me.ComListBox.Location = New System.Drawing.Point(18, 19)
        Me.ComListBox.Margin = New System.Windows.Forms.Padding(2)
        Me.ComListBox.Name = "ComListBox"
        Me.ComListBox.Size = New System.Drawing.Size(91, 69)
        Me.ComListBox.TabIndex = 3
        '
        'Connect
        '
        Me.Connect.Location = New System.Drawing.Point(18, 92)
        Me.Connect.Margin = New System.Windows.Forms.Padding(2)
        Me.Connect.Name = "Connect"
        Me.Connect.RightToLeft = System.Windows.Forms.RightToLeft.Yes
        Me.Connect.Size = New System.Drawing.Size(56, 19)
        Me.Connect.TabIndex = 4
        Me.Connect.Text = "Connect"
        Me.Connect.UseVisualStyleBackColor = True
        '
        'Disconnect
        '
        Me.Disconnect.Location = New System.Drawing.Point(79, 92)
        Me.Disconnect.Margin = New System.Windows.Forms.Padding(2)
        Me.Disconnect.Name = "Disconnect"
        Me.Disconnect.Size = New System.Drawing.Size(70, 19)
        Me.Disconnect.TabIndex = 5
        Me.Disconnect.Text = "Disconnect"
        Me.Disconnect.UseVisualStyleBackColor = True
        '
        'ComResultTextBox
        '
        Me.ComResultTextBox.Location = New System.Drawing.Point(17, 115)
        Me.ComResultTextBox.Margin = New System.Windows.Forms.Padding(2)
        Me.ComResultTextBox.Name = "ComResultTextBox"
        Me.ComResultTextBox.Size = New System.Drawing.Size(167, 20)
        Me.ComResultTextBox.TabIndex = 6
        Me.ComResultTextBox.Text = "ComResultTextBox"
        '
        'File_List
        '
        Me.File_List.FormattingEnabled = True
        Me.File_List.Location = New System.Drawing.Point(274, 12)
        Me.File_List.Name = "File_List"
        Me.File_List.Size = New System.Drawing.Size(229, 121)
        Me.File_List.Sorted = True
        Me.File_List.TabIndex = 8
        '
        'Show_Files
        '
        Me.Show_Files.Location = New System.Drawing.Point(298, 161)
        Me.Show_Files.Name = "Show_Files"
        Me.Show_Files.Size = New System.Drawing.Size(75, 23)
        Me.Show_Files.TabIndex = 7
        Me.Show_Files.Text = "Show Files"
        Me.Show_Files.UseVisualStyleBackColor = True
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(410, 161)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(75, 23)
        Me.Button1.TabIndex = 9
        Me.Button1.Text = "Send Selected File"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(18, 140)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(75, 23)
        Me.Button2.TabIndex = 10
        Me.Button2.Text = "Play"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(109, 140)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(75, 23)
        Me.Button3.TabIndex = 11
        Me.Button3.Text = "Pause"
        Me.Button3.UseVisualStyleBackColor = True
        '
        'Button4
        '
        Me.Button4.Location = New System.Drawing.Point(18, 175)
        Me.Button4.Name = "Button4"
        Me.Button4.Size = New System.Drawing.Size(75, 23)
        Me.Button4.TabIndex = 12
        Me.Button4.Text = "Stop"
        Me.Button4.UseVisualStyleBackColor = True
        '
        'Button5
        '
        Me.Button5.Location = New System.Drawing.Point(109, 175)
        Me.Button5.Name = "Button5"
        Me.Button5.Size = New System.Drawing.Size(75, 23)
        Me.Button5.TabIndex = 13
        Me.Button5.Text = "Resume"
        Me.Button5.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(542, 210)
        Me.Controls.Add(Me.Button5)
        Me.Controls.Add(Me.Button4)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.File_List)
        Me.Controls.Add(Me.Show_Files)
        Me.Controls.Add(Me.ComResultTextBox)
        Me.Controls.Add(Me.Disconnect)
        Me.Controls.Add(Me.Connect)
        Me.Controls.Add(Me.ComListBox)
        Me.Margin = New System.Windows.Forms.Padding(2)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents SerialPort1 As IO.Ports.SerialPort
    Friend WithEvents ComListBox As ListBox
    Friend WithEvents Connect As Button
    Friend WithEvents Disconnect As Button
    Friend WithEvents ComResultTextBox As TextBox
    Friend WithEvents File_List As ListBox
    Friend WithEvents Show_Files As Button
    Friend WithEvents Button1 As Button
    Friend WithEvents Button2 As Button
    Friend WithEvents Button3 As Button
    Friend WithEvents Button4 As Button
    Friend WithEvents Button5 As Button
End Class
