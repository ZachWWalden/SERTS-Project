Imports System.Threading

Public Class Form1
    Delegate Sub ListBoxDelegate(ByVal command As Integer, ByVal myStr As String)
    Dim ListBoxDel As New ListBoxDelegate(AddressOf ListBoxDelMethod)

    Dim PC_Comm As New Thread(AddressOf PC_Comm_method)
    Dim ShowFiles As Integer = 1
    Dim StartFileList As Integer = 2
    Dim EndFileList As Integer = 3

    Dim ShowFilesStr As String = "1"
    Dim StartFileListStr As String = "2"
    Dim EndFileListStr As String = "3"
    Dim SendSelectedStr As String = "4"
    Dim PlayFileStr As String = "5"
    Dim PauseFileStr As String = "6"
    Dim ResumeFileStr As String = "7"
    Dim StopFileStr As String = "8"

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load


        ' Get the list of available com ports and put them in the list box
        ComResultTextBox.Text = "Com port closed"
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComListBox.Items.Add(sp)
        Next

        ' Make this a background thread so it automatically
        ' aborts when the main program stops.
        PC_Comm.IsBackground = True
        ' Set the thread priority to lowest
        PC_Comm.Priority = ThreadPriority.Lowest
        ' Start the thread
        PC_Comm.Start()
    End Sub

    Private Sub Connect_Click(sender As Object, e As EventArgs) Handles Connect.Click

        ' Connect to a selected serial port
        If SerialPort1.IsOpen = False Then
            ' a serial port in not already open
            If ComListBox.SelectedItem <> Nothing Then
                ' an item in the listbox has been selected
                SerialPort1.PortName = ComListBox.SelectedItem

                Try
                    'try to open the selected serial port
                    SerialPort1.Open()
                Catch
                    Debug.WriteLine("Failed to open serial port")
                End Try
                If SerialPort1.IsOpen Then
                    ' The serial port was opened
                    ComResultTextBox.Text = "Com port " + SerialPort1.PortName + " connected"
                Else
                    ' The serial port open failed
                    ComResultTextBox.Text = "Com port " + SerialPort1.PortName + " not connected"
                End If
            Else
                ComResultTextBox.Text = "Nothing selected"
            End If
        Else
            ' A com port is already open
            ComResultTextBox.Text = "Com port " + SerialPort1.PortName + " already connected"
        End If

    End Sub

    Private Sub Disconnect_Click(sender As Object, e As EventArgs) Handles Disconnect.Click
        ' Close the serial port if it is open
        If SerialPort1.IsOpen Then
            SerialPort1.Close()
            ComResultTextBox.Text = "Com port closed"
        End If
    End Sub

    ' Delegate function that accesses the ListBox object
    ' command = 2 - clear the contents of the ListBox
    ' command = 3 - add the string to the ListBox
    Public Sub ListBoxDelMethod(ByVal command As Integer, ByVal myStr As String)

        If command = StartFileList Then
            File_List.Items.Clear()
        ElseIf command = EndFileList Then
            File_List.Items.Add(myStr)
        End If
    End Sub
    ' Thread that monitors the receive items on the serial port
    Private Sub PC_Comm_method()
        Dim str As String
        While 1
            If SerialPort1.IsOpen Then
                Try
                    str = SerialPort1.ReadLine() ' Wait for start string
                Catch ex As Exception
                End Try

                'String.Compare return values:
                ' Less than zero: strA precedes strB in the sort order.
                'Zero" strA occurs in the same position as strB in the sort order.
                'Greater than zero: strA follows strB in the sort order.
                If Not String.Compare(str, StartFileListStr) Then
                    ' Received a StartFileList response
                    ' clear the list
                    ' Use the delegate to access the ListBox
                    File_List.Invoke(ListBoxDel, StartFileList, "")
                    ' get next string
                    Try
                        str = SerialPort1.ReadLine() ' read file name
                    Catch ex As Exception
                    End Try
                    While String.Compare(str, EndFileListStr)
                        ' The read string is a file name and not the EndFileList
                        File_List.Invoke(ListBoxDel, EndFileList, str)
                        Try
                            str = SerialPort1.ReadLine() ' read file name
                        Catch ex As Exception
                        End Try
                    End While
                    ' While loop ends when a 3 is received
                End If
            Else
                Threading.Thread.Sleep(500)
            End If
        End While
    End Sub

    Private Sub Show_Files_Click(sender As Object, e As EventArgs) Handles Show_Files.Click
        If SerialPort1.IsOpen Then
            ' Send Show_Files command
            SerialPort1.Write(ShowFilesStr, 0, 1)
        End If
    End Sub

    'Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
    'Dim b(1) As Byte
    '   b(0) = 0
    '' A value of negative one (-1) is returned if no item is selected
    'If Not (File_List.SelectedIndex = -1) Then
    '       SerialPort1.Write("4", 0, 1)
    '      SerialPort1.Write(File_List.SelectedItem)
    '     SerialPort1.Write(b, 0, 1) ' New Line character at the end of the string
    'End If

    'End Sub
    'Play
    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        SerialPort1.Write(PlayFileStr, 0, 1)
    End Sub
    'Pause
    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        SerialPort1.Write(PauseFileStr, 0, 1)
    End Sub
    'Resume
    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        SerialPort1.Write(ResumeFileStr, 0, 1)
    End Sub
    'Stop
    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        SerialPort1.Write(StopFileStr, 0, 1)
    End Sub

    Private Sub File_List_SelectedIndexChanged(sender As Object, e As EventArgs) Handles File_List.SelectedIndexChanged
        Dim b(1) As Byte
        b(0) = 0
        ' A value of negative one (-1) is returned if no item is selected
        If Not (File_List.SelectedIndex = -1) Then
            SerialPort1.Write("4", 0, 1)
            SerialPort1.Write(File_List.SelectedItem)
            SerialPort1.Write(b, 0, 1) ' New Line character at the end of the string
        End If

    End Sub
End Class
