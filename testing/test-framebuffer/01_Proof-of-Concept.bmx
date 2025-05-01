SuperStrict

'
'	Framebuffer functions For BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

Framework brl.standardio

' https://e2e.ti.com/support/processors-group/processors/f/processors-forum/8343/please-tell-me-what-they-mean-for-fbioget_vscreeninfo-and-fbioget_fscreeninfo

Import "01_framebuffer.c"

Extern
	Function fb_open:Int()
	Function fb_close()
	Function fb_cls( color:Int )
	Function fb_flip()
	Function fb_getbpp:Int()
	Function fb_getheight:Int()
	Function fb_getwidth:Int()
	Function fb_plot( x:Int, y:Int, col:Int )
	Function fb_fill_rect( x:Int, y:Int, w:Int, h:Int, col:Int )
	
	' Not sure if I will expose these yet, may make a mode function
	Function fb_setbpp( bpp:Int )
EndExtern

' WE ONLY SUPPORT RASPBERRY PI AT THE MOMENT
?Not raspberrypi
	Print "Only supported on Raspberry Pi"
	End
?
' ABORT IF RUNNING A DESKTOP
If getenv_( "DISPLAY" ) 
	Print "Not supported in a desktop environment"
	End
EndIf

''

Print "OPEN FRAMEBUFFER"
Local fb:Int = fb_open()
If fb=-1
	Print "- Failed to open framebuffer"
	End
EndIf
Print "- Success"

Print "GET SCREEN INFORMATION"
Print "- HEIGHT: "+fb_getheight()
Print "- WIDTH:  "+fb_getwidth()
Print "- BPP:    "+fb_getbpp()

Local xpos:Int = fb_getwidth() /2
Local dx:Int = 2	' Speed

Local timeout:Int = MilliSecs() + 5000
Repeat
	fb_cls(3)

	For Local y:Int = 0 Until fb_getheight()
		For Local x:Int = 0 Until fb_getwidth()
			fb_plot( x, y, 16 * x / fb_getwidth() )
		Next
	Next

	' Example animation
	fb_fill_rect( xpos, 50, 20, 20, 7 );
	xpos :+ dx
	If xpos<0 Or xpos>fb_getwidth(); dx = -dx

	fb_flip()
Until MilliSecs() > timeout

Print "CLOSE FRAMEBUFFER"
fb_close()


