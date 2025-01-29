# Win32 Hidden APIs' lib file

### Include
> I only generate the necessary APIs needed for the library, so there are only a few functions.
- NtSuspendProcess
- NtResumeProcess
  
### Way to generate those libs
> Prerequisites: Windows XP or later, Windows SDK
- Step 1: Open "Developer Command Prompt for VS xxxx" and run
```cmd
dumpbin /exports C:\Windows\System32\ntdll.dll > ntdll_exports.txt
```
or
```cmd
link /dump /exports C:\Windows\System32\ntdll.dll > ntdll_exports.txt
```
You will get `ntdll_exports.txt` that contains all APIs include undocumented ones.
- Step 2: Create `ntdll.def` and add:
```
LIBRARY ntdll
EXPORTS
NtSuspendProcess
NtResumeProcess
```
At your own discretion, you can add more functions.
- Step 3: Generate `.lib` 
```cmd
lib /def:ntdll.def /out:ntdll.lib /machine:x64
```
Replace `x64` with other machine types if you need.

