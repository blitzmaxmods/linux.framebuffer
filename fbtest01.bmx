SuperStrict

' V
' 0.01  12 APR 2025  Scaremonger  Open Framebuffer and get resolution
' 0.02  12 APR 2025  Scaremonger  Added backbuffer

Framework brl.standardio



' https://e2e.ti.com/support/processors-group/processors/f/processors-forum/8343/please-tell-me-what-they-mean-for-fbioget_vscreeninfo-and-fbioget_fscreeninfo

Import "framebuffer.c"

Extern
	Function fb_open:Int()
	Function fb_close()
	Function fb_cls( color:Int )
	Function fb_flip()
	'Function fb_getscreeninfo:Int( fbfd:Int, var_info:Byte Ptr )
	Function fb_getbpp:Int()
	Function fb_getheight:Int()
	Function fb_getwidth:Int()
	Function fb_plot( x:Int, y:Int, col:Int )
	Function fb_fill_rect( x:Int, y:Int, w:Int, h:Int, col:Int )
	
	' Not sure if I will expose these yet, may make a mode function
	Function fb_setbpp( bpp:Int )
EndExtern

' https://docs.huihoo.com/doxygen/linux/kernel/3.7/structfb__bitfield.html
Struct FB_BITFIELD
	Field offset:Int
	Field Length:Int
	Field msb_right:Int
End Struct

' https://docs.huihoo.com/doxygen/linux/kernel/3.7/structfb__var__screeninfo.html
' https://www.kernel.org/doc/Documentation/fb/api.txt
Struct FB_VAR_SCREENINFO
	Field xres:Int			' Visible resolution
	Field yres:Int
	Field xres_virtual:Int	' Virtual resolution
	Field yres_virtual:Int
	Field xoffset:Int
	Field yoffset:Int
	Field bits_per_pixel:Int
	Field grayscale:Int
	Field red:FB_BITFIELD
	Field green:FB_BITFIELD
	Field blue:FB_BITFIELD
	Field transp:FB_BITFIELD
	Field nonstd:Int
	Field activate:Int
	Field height:Int
	Field width:Int
	Field accel_flags:Int
	Field pixclock:Int
	Field left_margin:Int
	Field right_margin:Int
	Field upper_margin:Int
	Field lower_margin:Int
	Field hsync_len:Int
	Field vsync_len:Int
	Field sync:Int
	Field vmode:Int
	Field Rotate:Int
	Field colorspace:Int
	Field reserved:Int[4]
End Struct

Struct FB_VAR_INFO

End Struct

Print "OPEN FRAMEBUFFER"
Local fb:Int = fb_open()
If fb=-1
	Print "- Failed to open framebuffer"
	End
EndIf
Print "- Success"

'Local var_info:FB_VAR_SCREENINFO
Print "GET SCREEN INFORMATION"
'If fb_getscreeninfo( fb, Varptr var_info )
'	Print( "SUCCESS" )
'Else
'	Print( "FAIL")
'EndIf
Print "- HEIGHT: "+fb_getheight()
Print "- WIDTH:  "+fb_getwidth()
Print "- BPP:    "+fb_getbpp()


'Print "Chnage to 8bpp"
'fb_setbpp( 8 )

'Print "- HEIGHT: "+fb_getheight()
'Print "- WIDTH:  "+fb_getwidth()
'Print "- BPP:    "+fb_getbpp()

Local timeout:Int = MilliSecs() + 5000
Local xpos:Int = fb_getwidth() /2
Local dx:Int = 30
Repeat
	fb_cls(3)

	For Local y:Int = 0 Until fb_getheight()
		For Local x:Int = 0 Until fb_getwidth()
			fb_plot( x, y, 16 * x / fb_getwidth() )
		Next
	Next

	fb_fill_rect( xpos, 50, 20, 20, 7 );
	xpos :+ dx
	If xpos<0 Or xpos>fb_getwidth(); dx = -dx

	fb_flip()
Until MilliSecs() > timeout
'Delay( 5000 )

Print "CLOSE FRAMEBUFFER"
fb_close()

DebugStop
