'SuperStrict

'
'	Max2D video debug driver for BlitzMax
'	(c) Copyright Si Dunford [Scaremonger], April 2025
'

' See Examples for how to use this

'Function EnableVideoDebug()
'	__videodebug = GetVideoDriver()
'	Local driver:TVideo = New TVideo()
'	
'End Function
'
'Function DisableVideoDebug()
'End Function

Type TVideoDebug Extends TVideo
	Field oldDriver:TVideo
	Field logfile:TStream
	Field logfilename:String = "videolog.txt"
	
	Method initDriver()
'		oldDriver.initDriver()
'		logfile = OpenFile( logfilename )
'		If Not logfile; Return
'		Log( "initDriver()" )
	EndMethod
	
	Method doneDriver()
'		If Not logfile; Return
'		Log( "doneDriver()" )
'		CloseFile( logfile )
	EndMethod
	
	Method flipScreen( sync:Int=-1 )
'		Log( "Flipscreen()" )
	EndMethod

End Type