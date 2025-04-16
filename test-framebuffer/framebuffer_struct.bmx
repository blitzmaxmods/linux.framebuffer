
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