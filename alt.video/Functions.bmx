'SuperStrict

'
'	Video driver functions for BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

' Close the currently active video
Function closeVideo( video:TVideo = Null )
	If video
		video.close()
	Else
		TVideo.closeVideo()
	EndIf
End Function

' Get the current video driver
Function GetVideoDriver:TVideoDriver()
	Return TVideo.GetVideoDriver()
EndFunction

' Sets the current video
Function setVideo( video:TVideo )
	TVideo.setActive( video )
End Function


Function FillRect( x:Float, y:Float, width:Float, height:Float )
	If TVideo.selected And TVideo.selected.driver;
		TVideo.selected.driver.FillRect( x, y, width, height )
EndFunction
