; Change MS-Windows volume through the command line. Useful through EMMS.
; Passing a signed percentage amends the volume, whereas a number outright sets
; it.

; N.B.: AHK prints to stdout but not to the current cmd.exe (but text appears in
; eshell)
; Compile like this on cmd:
;          AutoHotKey\Compiler\Ahk2Exe.exe /in WinVol.atk /out WinVol.exe

; Jordan Wilson, 27/01/2019

; Modified by zyt, <2024-09-25 ÖÜÈý>

master_volume := SoundGetVolume()
if A_Args.Length < 1
{
	FileAppend "Need a signed percentage (if amending volume) or a number (if setting outright)`r`n", "*"
	ExitApp
}
else
{
	SoundSetVolume A_Args[1]
	curVol := SoundGetVolume()
	curVol := Round(curVol)
	FileAppend ("Volume: " curVol "%`r`n"), "*"
}
