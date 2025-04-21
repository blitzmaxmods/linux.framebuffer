SuperStrict

Framework brl.StandardIO

'Import brl.SystemDefault
'Import brl.PolledInput
Import "SIGINT.c"

Extern
'	Function os_sigint:Byte Ptr( handler( signal:Int ) )
	Function setsig:Byte Ptr(handler( signal:Int ))
EndExtern

'Local oldHandler( signal:Int ) = os_sigint( onCtrlC )

Local oldHandler( signal:Int ) = setsig( onCtrlC )
global terminated:Int = False
'EnablePolledInput()
'KeyHit

Print "STARTING"
Repeat
	Delay(1)
Until terminated

Print "FINISHED"
'os_sigint( oldHandler )


Function onCtrlC( signal:Int )
	Print "CTRL-C Pressed"
	terminated = True
End Function

Function OnEnd()
	Print "Exiting"
End Function