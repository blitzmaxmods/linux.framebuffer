'SuperStrict

'
'	Alternate Video Driver for BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

Interface IVideoDriver
EndInterface

' The video driver uses replaceable functions

Type TVideoDriver

	Field bgcolor:UInt	' Current cls colour
	Field fgcolor:UInt	' Current foreground colour

	Method InitDriver:Int(); Return False; EndMethod
	Method DoneDriver(); EndMethod

	'Method Cls() Abstract

	Method GraphicsHeight:Int() ; End Method

	Method GraphicsWidth:Int() ; End Method

	Method Clearscreen(); EndMethod
	Method FlipScreen( sync:Int=-1 ); EndMethod
	
'	Method GetCapabilities:Short(); endmethod
'	Method GetCursorType:Short(); endmethod
'	Method GetVideoModeCount:Short(); endmethod
'	Method GetVideoModeData:Int( index:Short, data:TVideoMode ); endmethod
'	Method SetCursorPos( X:Short, Y:Short ); endmethod
'	Method SetCursorType( cursor:Short ); endmethod
'	Method SetVideoMode:Int( mode:TVideoMode ); endmethod
'	Method UpdateScreen( force:Int ); EndMethod

	' DRAWING FUNCTIONS
	' These may be slow, please override in your driver
	
	Public Method Plot( x:Float, y:Float ); EndMethod

	' TODO: Replace with proper line drawing algorithm
	Public Method DrawLine( x1:Float, y1:Float, x2:Float, y2:Float, draw_last_pixel:Int=True )
		If x1=x2
			drawVline( x1, y1, y2 )
		ElseIf y1=y2
			drawHline( y1, x1, x2 )
		Else
			Print "Drawline not implemented"
		EndIf
	EndMethod
	
	Public Method DrawRect( x:Float, y:Float, width:Float, height:Float )
		DrawLine( x,y, x+width,y )					' TOP
		DrawLine( x+width, y, x+width, y+height )	' RIGHT
		DrawLine( x, y+height, x+width, y+height )	' BOTTOM
		DrawLine( x, y, x, y+height )				' LEFT
	EndMethod

	Public Method FillRect( x:Float, y:Float, width:Float, height:Float )
		For Local line:Float = 0 Until height
			DrawLine( x, y+line, x+width, y+line )
		Next
	EndMethod

	Private Method drawHline( y:Float, x1:Float, x2:Float )
		For Local x:Float = x1 Until x2
			Plot( x, y )
		Next
	EndMethod

	Private Method drawVline( x:Float, y1:Float, y2:Float )
		For Local y:Float = y1 Until y2
			Plot( x, y )
		Next
	EndMethod

	'
	Method SetColor( color:UInt )	
		fgcolor = color 
	EndMethod

	Method SetClsColor( color:UInt )
		bgcolor = color 
	EndMethod

	

End Type

