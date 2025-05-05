SuperStrict

'
'	Example 1, Framebuffer Driver For BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

Framework brl.standardio

' This example uses the framebuffer
Import "../linux.framebuffer/framebuffer.bmx"

' We also need the SIGINT handler to catch Ctrl-C
Import "../os.sigint/sigint.bmx"

' Create a replacement Appterminate() using global
Global appTerminated:Int = False
Function AppTerminate:Int()
	Return appTerminated
End Function

' Create a Ctrl-C handler for appterminate
Function onCtrlC()
	Print "~nCTRL-C Detected, Exiting."
	appTerminated = True
End Function

' Set the Ctrl-C Handler using SIGINT
setSIGINT( onCtrlC )

' Create a video framebuffer 
Local fb0:TVideo = getFramebuffer( "/dev/fb0" )

' Select the framebuffer video
SetGraphics( fb0 )

Print "~nRead individual variables"

Print "XRES: "+ GraphicsWidth()
Print "YRES: "+ GraphicsHeight()

' Set up basic animation object
Local xpos:Float = GraphicsWidth() /2
Local ypos:Float = GraphicsHeight()/2

Local dx:Float = 2	' Speed
Local dy:Float = 2	' Speed

' Set up basic frame counter
Local frametimer:Int = MilliSecs() + 1000
Local framecount:Int
Local fps:Int

Repeat
	Cls

	Local now:Int = MilliSecs()
	
	' Frame counter
	framecount :+ 1
	If now > frametimer
		fps = framecount
		framecount = 0
		frametimer = now + 1000
		Print "FPS: "+fps
	EndIf
			
	' Draw a static BLUE filled rectangle
	SetColor( $0000ff );
	FillRect( 50,50, 50,50 )
	
	' Draw an animated RED box
	SetColor( $ff0000 );
	xpos :+ dx
	ypos :+ dy
	If xpos<=0 Or xpos+20>GraphicsWidth(); dx = -dx
	If ypos<=0 Or ypos+20>GraphicsHeight(); dy = -dy
	DrawRect( xpos,ypos, 20,20 )

	Flip
Until AppTerminate()

Print "Closing"
CloseGraphics( fb0 )

Print "Closed"

