'SuperStrict

'
'	Alternate Video handler for BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

' This is a graphics context which represents a screen
' on the hardware. You create one of these PER hardware 
' display and use setactive() to select the one you want
' as current.

Type TVideo

	' Currently selected video
	Global selected:TVideo
	
	' The driver for this video
	Field driver:TVideoDriver

	' Set the active video
	Public Function setActive( video:TVideo )
		selected = video
	EndFunction
		
	' Close the selected video driver
	Public Function closeVideo()
		If selected; selected.close()
	EndFunction
	
	' Set the driver
	Public Method setDriver:Int( driver:TVideoDriver )
		' Driver must be manually closed before setting a new one
		If Self.driver; Return False
		Self.driver = driver
	EndMethod

	' Close the driver
	Method close()
		driver.doneDriver()
		driver = Null
	End Method
	
' ----- STATIC FUNCTIONS -----
	
'	Function Cls()
'		If selected; selected.Cls()
'	EndFunction

'	Function DrawLine( x1:Float, y1:Float, x2:Float, y2:Float, draw_last_pixel:Int=True )
'		If selected; DrawLine( x1, y1, x2, y2, draw_last_pixel )
'	EndFunction

'	Function GraphicsHeight:Int()
'		If Not selected; Return 0
'		Return selected.GraphicsHeight()
'	EndFunction
'
'	Function GraphicsWidth:Int()
'		If Not selected; Return 0
'		Return selected.GraphicsWidth()
'	EndFunction
'
'	Function Flip( sync:Int=-1 )
'		If selected; selected.Flip()
'	EndFunction
'
	Function GetVideoDriver:TVideoDriver()
		If selected; Return selected.driver
	EndFunction

End Type


	

	
