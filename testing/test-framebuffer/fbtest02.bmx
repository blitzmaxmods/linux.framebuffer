SuperStrict

Rem 16 APR 2025

Test obtaining the FIX and VAR structures

EndRem

Framework brl.standardio

' https://e2e.ti.com/support/processors-group/processors/f/processors-forum/8343/please-tell-me-what-they-mean-for-fbioget_vscreeninfo-and-fbioget_fscreeninfo

Import "framebuffer2.c"

Extern
	Function fb_open:Int()
	Function fb_get_finfo:Int( fbfd:Int, finfo:Byte Ptr )
	Function fb_get_vinfo:Int( fbfd:Int, vinfo:Byte Ptr )

EndExtern

' Fixed screen information
' https://github.com/torvalds/linux/blob/master/include/uapi/linux/fb.h#L158
' https://docs.huihoo.com/doxygen/linux/kernel/3.7/include_2uapi_2linux_2fb_8h_source.html
Struct FB_FIX_SCREENINFO
	Field id:Byte[16]			' char[16], identification String eg "TT Builtin"
	Field smem_start:ULong		' unsigned Long, Start of frame buffer mem
	Field smem_len:UInt			' __u32, Length of frame buffer mem
	Field fbType:UInt			' __u32, see FB_TYPE_* 
	Field type_aux:UInt			' __u32, Interleave For interleaved Planes
	Field visual:UInt			' __u32, see FB_VISUAL_* 
	Field xpanstep:Short		' __u16, zero If no hardware panning 
	Field ypanstep:Short		' __u16, zero If no hardware panning 
	Field ywrapstep:Short		' __u16, zero If no hardware ywrap 
	Field line_length:UInt		' __u32, Length of a line in bytes 
	Field mmio_start:ULong		' unsigned Long, Start of Memory Mapped I/O 
	Field mmio_len:UInt			' __u32, Length of Memory Mapped I/O 
	Field accel:UInt			' __u32, Indicate To driver which specific chip/card we have 
	Field capabilities:Short	' __u16, see FB_CAP_* 
	Field reserved:Short[2]		' __u16[2], Reserved For future compatibility
	
	Method dump:String()
		Print( "- FINFO:" )
		Print( "  sizeof="+SizeOf( FB_FIX_SCREENINFO ) )
' NEXT LINE CAUSES SEGFAULT
		'Print( "  id:           "+ showArray( id ) )
		'Print( "  id:           "+String.fromCString(id) )
		Print( "  smem_start:   "+ smem_start)
		Print( "  smem_len:     "+ smem_len )
		Print( "  fbType:       "+ fbType)
		Print( "  type_aux:     "+ type_aux)
		Print( "  visual:       "+ visual)
		Print( "  xpanstep:     "+ xpanstep)
		Print( "  ypanstep:     "+ ypanstep)
		Print( "  ywrapstep:    "+ ywrapstep)
		Print( "  line_length:  "+ line_length)
		Print( "  mmio_start:   "+ mmio_start)
		Print( "  mmio_len:     "+ mmio_len)
		Print( "  accel:        "+ accel)
		Print( "  capabilities: "+ capabilities)
' NEXT LINE CAUSES SEGFAULT
		'Print( "  reserved:     "+ showArray( reserved ) )
	End Method

End Struct

' Variable Screen Information
' https://github.com/torvalds/linux/blob/master/include/uapi/linux/fb.h#L243

Struct FB_VAR_SCREENINFO
	Field xres:UInt				' __u32, visible resolution 
	Field yres:UInt				' __u32,
	Field xres_virtual:UInt		' __u32, virtual resolution 
	Field yres_virtual:UInt		' __u32,
	Field xoffset:UInt			' __u32, offset from virtual To visible 
	Field yoffset:UInt			' __u32, resolution 

	Field bits_per_pixel:UInt	' __u32, guess what 
	Field grayscale:UInt		' __u32, 0 = color, 1 = grayscale, >1 = FOURCC
	
	Field red:FB_BITFIELD		' Struct fb_bitfield , bitfield in fb mem If True color, 
	Field green:FB_BITFIELD		' Struct fb_bitfield, Else only Length is significant 
	Field blue:FB_BITFIELD		' Struct fb_bitfield,
	Field transp:FB_BITFIELD	' Struct fb_bitfield, transparency 

	Field nonstd:UInt			' __u32, != 0 Non standard pixel format 

	Field activate:UInt 		' __u32, see FB_ACTIVATE_* 

	Field height:UInt 			' __u32, height of picture in mm 
	Field width:UInt 			' __u32, width of picture in mm 

	Field accel_flags:UInt 		' __u32, (OBSOLETE) see fb_info.flags 

	' Timing: All values in pixclocks, except pixclock (of course) 
	Field pixclock:UInt 		' __u32, pixel clock in ps (pico seconds) 
	Field left_margin:UInt 		' __u32, time from sync To picture 
	Field right_margin:UInt 	' __u32, time from picture To sync 
	Field upper_margin:UInt 	' __u32, time from sync To picture 
	Field lower_margin:UInt		' __u32,
	Field hsync_len:UInt 		' __u32, Length of horizontal sync 
	Field vsync_len:UInt 		' __u32, Length of vertical sync 
	Field sync:UInt 			' __u32, see FB_SYNC_* 
	Field vmode:UInt 			' __u32, see FB_VMODE_* 
	Field Rotate:UInt 			' __u32, angle we Rotate counter clockwise 
	Field colorspace:UInt		' __u32, colorspace For FOURCC-based modes 
	Field reserved:UInt[4] 		' __u32[4], Reserved For future compatibility 

	Method dump:String()
		Print( "- VINFO:" )
		Print( "  sizeof="+ SizeOf(FB_VAR_SCREENINFO) )
		Print( "  xres:           "+ xres )
		Print( "  yres:           "+ yres )
		Print( "  xres_virtual:   "+ xres_virtual )
		Print( "  yres_virtual:   "+ yres_virtual )
		Print( "  xoffset:        "+ xoffset )
		Print( "  yoffset:        "+ yoffset )
		Print( "  bits_per_pixel: "+ bits_per_pixel )
		Print( "  grayscale:      "+ grayscale )
		Print( "  red:            "+ red.debug() )
		Print( "  green:          "+ green.debug() )
		Print( "  blue:           "+ blue.debug() )
		Print( "  transp:         "+ transp.debug() )
		Print( "  nonstd:         "+ nonstd )
		Print( "  activate:       "+ activate )
		Print( "  height:         "+ height )
		Print( "  width:          "+ width )
		Print( "  accel_flags:    "+ accel_flags )
		Print( "  pixclock:       "+ pixclock )
		Print( "  left_margin:    "+ left_margin )
		Print( "  right_margin:   "+ right_margin )
		Print( "  upper_margin:   "+ upper_margin )
		Print( "  lower_margin:   "+ lower_margin )
		Print( "  hsync_len:      "+ hsync_len )
		Print( "  vsync_len:      "+ vsync_len )
		Print( "  sync:           "+ sync )
		Print( "  vmode:          "+ vmode )
		Print( "  rotate:         "+ Rotate )
		Print( "  colorspace:     "+ colorspace )
' NEXT LINE CAUSES SEGFAULT
'		Print( "  reserved:       "+ showArray( reserved ) )
	End Method
End Struct

' https://github.com/torvalds/linux/blob/master/include/uapi/linux/fb.h#L189
Struct FB_BITFIELD
	Field offset:UInt 			' __u32, beginning of bitfield 
	Field Length:UInt 			' __u32, Length of bitfield 
	Field msb_right:UInt 		' __u32, != 0 : Most significant bit is right

	Method debug:String()
		Return offset+","+Length+","+msb_right
	End Method
End Struct

Function showArray:String( array:Byte[] )
	Local data:String
	For Local n:Int = 0 Until array.Length
		data :+ array[n]+","
	Next
	Return "("+data[..(Len(data)-1)]+")"
End Function

Function showArray:String( array:Short[] )
	Local data:String
	For Local n:Int = 0 Until array.Length
		data :+ array[n]+","
	Next
	Return "("+data[..(Len(data)-1)]+")"
End Function

Function showArray:String( array:UInt[] )
	Local data:String
	For Local n:Int = 0 Until array.Length
		data :+ array[n]+","
	Next
	Return "("+data[..(Len(data)-1)]+")"
End Function

' OPEN THE FRAMEBUFFER
Print "Framebuffer"
Global fbfd:Int = fb_open()
Print "- File Descriptor: "+fbfd
If fbfd=-1
	Print "- FAILED"
	End
EndIf
Print "- OPEN"

' READ FIXED SCREEN INFORMATION
Print "Fixed Screen Informaton"
Global finfo:FB_FIX_SCREENINFO
If fb_get_finfo( fbfd, Varptr finfo )
	Print "- BMX: SUCCESS"
	finfo.dump()
Else
	Print "- BMX: FAILED"
EndIf

Input( "Press enter" )

' Read Variable screen information
Print "Variable Screen Informaton"
Global vinfo:FB_VAR_SCREENINFO
If fb_get_vinfo( fbfd, Varptr vinfo )
	Print "- BMX: SUCCESS"
	vinfo.dump()
Else
	Print "- BMX: FAILED"
EndIf