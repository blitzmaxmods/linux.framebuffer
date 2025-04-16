' LINUX FRAMEBUFFER
' (c) Copyright Si Dunford [Scaremonger] April 2025
'

' LIMITATIONS:
' * Designed for Raspberry Pi and untested on other Linux platforms
' * Must run in a console (Ctrl-Alt-F2) or non desktop environment

'Module linux.framebuffer
'
' import "lib/framebuffer.c"
'

' WE ONLY SUPPORT RASPBERRY PI AT THE MOMENT
?Not raspberrypi
	Print "linux.framebuffer only supports the Raspberry Pi"
	End
?

' ABORT IF RUNNING A DESKTOP
If getenv_( "DISPLAY" ) 
	Print "linux.framebuffer only supports the console"
	End
EndIf





