SuperStrict

'
'	Framebuffer functions For BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

'Module os.sigint

Import brl.StandardIO
Import "SIGINT.c"

Extern
	Function setsignal:Byte Ptr(handler( signal:Int ))
EndExtern

' Portable Signal Numbers
Global SIGINT:Int = 2

' Current Ctrl-C Handler
Global __os_sigint_current()

' SIGINT Event handler
Function __os_sigint_handler( signal:Int )
	Select signal
	Case SIGINT
		If __os_sigint_current
			__os_sigint_current()
		Else
			' Default Handler
			Print "CTRL-C Detected, Exiting."
			End
		EndIf
	End Select
End Function

' Public function to set the Ctrl-C handler
Function setSIGINT( handler() )
	__os_sigint_current = handler
EndFunction

' Set the SIGINT handler
setsignal( __os_sigint_handler )




