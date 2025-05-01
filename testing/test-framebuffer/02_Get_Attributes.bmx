SuperStrict

'
'	Framebuffer functions For BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

Framework brl.standardio

Import "02_framebuffer.c"

Extern
	Function fb_open:Byte Ptr( device$z )
	Function fb_close( fb:Byte Ptr )

	Function fb_get_bitsperpixel:Int( fb:Byte Ptr )
	Function fb_get_line_length:Int( fb:Byte Ptr )
	Function fb_get_xres:Int( fb:Byte Ptr )
	Function fb_get_yres:Int( fb:Byte Ptr )

	Function fb_get_res:Int( fb:Byte Ptr, xres:Int Var, yres:Int Var )
EndExtern

' OPEN THE FRAMEBUFFER
Print "Framebuffer"
Global fb0:Byte Ptr = fb_open( "/dev/fb0" )
If Not fb0
	Print "- FAILED"
	End
EndIf
Print "- OPEN"

Print "~nRead individual variables"

Print "BITS PER PIXEL: "+ fb_get_bitsperpixel( fb0 )
Print "LINE LENGTH:    "+ fb_get_line_length( fb0 )
Print "XRES:           "+ fb_get_xres( fb0 )
Print "YRES:           "+ fb_get_yres( fb0 )

Print "~nGet resolution"

Global xres:Int, yres:Int
fb_get_res( fb0, xres, yres )
Print "XRES:           "+ xres
Print "YRES:           "+ yres

fb_close( fb0 )

