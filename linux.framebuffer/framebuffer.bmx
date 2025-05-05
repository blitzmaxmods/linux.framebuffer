SuperStrict

'
'	Framebuffer functions For BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

'Module linux.framebuffer

Import "framebuffer.c"
Import "../alt.video/video.bmx"

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

Extern
	Function fb_open:Byte Ptr( device$z )
	Function fb_close( fb:Byte Ptr )

	Function fb_get_bitsperpixel:Int( fb:Byte Ptr )
	Function fb_get_line_length:Int( fb:Byte Ptr )
	Function fb_get_xres:Int( fb:Byte Ptr )
	Function fb_get_yres:Int( fb:Byte Ptr )

	Function fb_get_res:Int( fb:Byte Ptr, xres:Int Var, yres:Int Var )

	Function fb_cls( fb:Byte Ptr, color:Int )
	' Flip using C-side backbuffer
	Function fb_flip( fb:Byte Ptr )
	' Flip using Blitzmax backbuffer
	'Function fb_flip( fb:Byte Ptr, bbuf:Byte Ptr )
	
	Function fb_color_forbpp:UInt( fb:Byte Ptr, color:UInt )

	Function fb_plot( fb:Byte Ptr, x:Int, y:Int, col:Int )
	Function fb_putpixel( fb:Byte Ptr, pix:UInt, col:Int )
	
EndExtern

Type TFramebuffer Extends TVideoDriver

	Field fb:Byte Ptr
	Field device:String
	
	' Attributes
	Field bpp:Int		' Bits per pixel
	Field stride:Int	' Bytes between rows
	Field xres:Int
	Field yres:Int
	
	Field bytespp:Int	' Bytes per pixel
		
	Method New( device:String )
		Self.device = device
	End Method
		
	Method initDriver:Int()
		fb = fb_open( device )
		If Not fb; Return False
		
		' Retrieve attributes
		bpp         = fb_get_bitsperpixel( fb )
		stride      = fb_get_line_length( fb )
		fb_get_res( fb, xres, yres )
		'xres       = fb_get_xres( fb )
		'yres       = fb_get_yres( fb )

		' Calculations
		bytespp     = bpp / 8

		Print "~nResolution=("+xres+","+yres+"), bpp="+bpp
		Return True
	EndMethod
	
	Method doneDriver()
		fb_close( fb )
	EndMethod

	Method Clearscreen()
		fb_cls( fb, bgcolor )
	EndMethod

	Method FlipScreen( sync:Int=-1 )
		fb_flip( fb )
		'fb_flip( fb, backbuffer )
	End Method
	
	Method GraphicsHeight:Int()
		Return yres
	EndMethod

	Method GraphicsWidth:Int()
		Return xres
	EndMethod
	
	Method Plot( x:Float, y:Float )
		fb_plot( fb, Int(x), Int(y), fgcolor )
		RuntimeError( "Shouldn't be using plot!" )
	EndMethod

	Method putPixel( pix:UInt )
		fb_putpixel( fb, pix, fgcolor )
Rem
		Select bpp
		Case 16
			fb_putpixel( fb, pix, fgcolor )
		Default
			RuntimeError( "putpixel() for "+bpp+"bpp is not implemented" )
		EndSelect
EndRem		
	EndMethod

	Private Method drawHline( y:Float, x1:Float, x2:Float )
		Local pix:UInt = ( x1 * bytespp + y * stride )
		For Local x:Float = x1 Until x2
			putpixel( pix )
			pix :+ bytespp
		Next
	EndMethod

	Private Method drawVline( x:Float, y1:Float, y2:Float )
		Local pix:UInt = ( x * bytespp + y1 * stride )
		For Local y:Float = y1 Until y2
			putpixel( pix )
			pix :+ stride
		Next
	EndMethod

	Method SetColor( color:UInt )
		' Depending on the bpp we need to convert the colour
		fgcolor = fb_color_forbpp( fb, color )
	EndMethod

	Method SetClsColor( color:UInt )
		bgcolor = fb_color_forbpp( fb, color ) 
	EndMethod
	
EndType

' This is similar to the way Graphics() works in Blitzmax
' It creates a video and attaches the framebuffer driver
' Then initialises it
Function getFrameBuffer:TVideo( device:String )
	Local driver:TVideoDriver = New TFramebuffer( device )
	If Not driver.initDriver(); Return Null
	Local video:TVideo = New TVideo()
	video.SetDriver( driver )
	Return video
EndFunction

