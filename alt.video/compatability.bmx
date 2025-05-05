'SuperStrict

'
'	Compatable video driver function for BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

' MAX2D Compatible functions

Function GetGraphicsDriver:TVideoDriver()
	Return TVideo.GetVideoDriver()
EndFunction

' ##### BRL.GRAPHICS COMPATABLITY

Function CloseGraphics( video:TVideo )
	video.close()
EndFunction
'	Function CountGraphicsModes()
'		If selected And context.driver; selected.driver.CountGraphicsModes()
'	EndFunction
'	Function CreateGraphics()
'	EndFunction
'	Function DefaultGraphicsFlags()
'	EndFunction
'	Function EndGraphics()
'	EndFunction
Function Flip()
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.FlipScreen()
EndFunction
'	Function GetGraphicsDriver:TVideoDriver()
'		Return GetVideoDriver()
'	EndFunction
'	Function GetGraphicsMode()
'	EndFunction
'	' Select the graphics mode using the current driver
'	Function Graphics(width:Int,height:Int,depth:Int=0,hertz:Int=60,flags:Long=0,x:Int=-1,y:Int=-1 )
'		If Not context; Return
'		' find graphicsmode
'	EndFunction
'	Function GraphicsDepth()
'	EndFunction
'	Function GraphicsFlags()
'	EndFunction
Function GraphicsHeight:Int()
	If TVideo.selected And TVideo.selected.driver;
		Return TVideo.selected.driver.GraphicsHeight()
EndFunction
'	Function GraphicsHertz()
'	EndFunction
'	Function GraphicsModeExists()
'	EndFunction
'	Function GraphicsModes()
'	EndFunction
'	Function GraphicsPosition()
'	EndFunction
'	Function GraphicsResize()
'	EndFunction
Function GraphicsWidth:Int()
	If TVideo.selected And TVideo.selected.driver;
		Return TVideo.selected.driver.GraphicsWidth()
EndFunction

Function SetClsColor( color:Int )
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.SetClsColor( UInt(color) )
End Function
'Function SetClsColor( color:SColor8 )
'End Function
Function SetClsColor( r:Int, g:Int, b:Int, alpha:Int )
	Local color:UInt
	Local argb:Byte Ptr = Varptr color
	argb[0] = b
	argb[1] = g
	argb[2] = r
	argb[3] = alpha
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.SetClsColor( color )
End Function
Function SetColor( color:Int )
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.SetColor( UInt(color) )
End Function
'Function SetColor( color:SColor8 )
'End Function
Function SetColor( r:Int, g:Int, b:Int, alpha:Int )
	Local color:UInt
	Local argb:Byte Ptr = Varptr color
	argb[0] = b
	argb[1] = g
	argb[2] = r
	argb[3] = alpha
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.SetColor( color )
End Function

' Select the video screen and driver
Function SetGraphics( video:TVideo )
	setVideo( video )
EndFunction

'	Function SetGraphicsDriver( gd:TGraphDriver, gm:TGraphMode )
'	'	If Not gd Or Not gm; Return
'	'	If Not TGraph.context
'	'		' Initialise the new driver
'	'		TGraph.context = gd
'	'		TGraph.context.initGraphics( gd )
'	'	ElseIf TGraph.context <> gd
'	'		' Close existing context
'	'		TGraph.context.CloseGraphics()
'	'		' Initialise the new driver
'	'		TGraph.context = gd
'	'		TGraph.context.initGraphics( gd )
'	'	EndIf
'	'	' Set the graphics mode
'	'	If TGraph.context.getmode()<>gm
'	'		TGraph.context.setMode(gm)
'	'	EndIf
'	End Function

' ##### MAX2D COMPATABILITY

Function Cls()
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.ClearScreen()
EndFunction

Function DrawLine( x1:Float, y1:Float, x2:Float, y2:Float, draw_last_pixel:Int=True )
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.DrawLine( x1, y1, x2, y2, draw_last_pixel )	
EndFunction
'	Function DrawOval()
'	EndFunction
'	Function DrawPoly()
'	EndFunction
Function DrawRect( x:Float, y:Float, width:Float, height:Float )
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.DrawRect( x, y, width, height )
EndFunction
'	Function DrawText()
'	EndFunction
'	Function DrawImage()
'	EndFunction
'	Function DrawPixmap()
'	EndFunction
Function Plot( x:Float, y:Float )
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.Plot( x, y )
EndFunction


