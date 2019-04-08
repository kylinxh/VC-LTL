@call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
@call "%~dp0..\..\VC-LTL helper for nmake.cmd"

set libfileroot=%~dp0..\..\lib\x86

set libfile=%libfileroot%\msvcrt.lib

copy "%~dp0msvcrt.lib" "%libfile%" /y


lib /MACHINE:%Platform% /def:"%~dp0msvcrt.def" /out:"%~dp0msvcrtdll.lib"
lib /MACHINE:%Platform% /def:"%~dp0..\msvcp60.def" /out:"%~dp0msvcp60.lib"
lib /MACHINE:%Platform% /def:"%~dp0..\msvcrt_form_msvcp60.def" /out:"%~dp0msvcrt_form_msvcp60.lib"
lib /MACHINE:%Platform% /def:"%~dp0..\msvcrt_form_msvcp60_WinXP.def" /out:"%~dp0msvcrt_form_msvcp60_WinXP.lib"

lib "%libfile%" "%~dp0msvcrtdll.lib"
lib "%libfile%" "%~dp0msvcrt_form_msvcp60.lib"
lib "%libfile%" "%~dp0msvcp60.lib"

echo ɾ��msvcrt.dll��������

del "%libfileroot%\objs" /S /Q /F

::ɾ������obj�ļ�
"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" RemoveAllObj "%libfile%"

"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" CreateWeaks  /MACHINE:x86 /def:"%~dp0..\msvcrt_forward.def"  /out:"%libfileroot%\objs\msvcrt_forward"
"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" CreateWeaks  /MACHINE:x86 /def:"%~dp0..\msvcrt_vista.def"    /out:"%libfileroot%\objs\msvcrt_forward"

::���XP��֧�ֵĽӿ�
::"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%libfile%" x86 "%~dp0..\msvcrt_winxp.def" msvcrt.dll msvcrt2.dll
"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" CreateWeaks  /MACHINE:x86 /def:"%~dp0..\msvcrt_winxp.def"  /out:"%libfileroot%\objs\msvcrt_winxp"

::�������ģʽ
::"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%libfile%" x86 "%~dp0..\msvcrt_light.def" msvcrt.dll msvcrt2.dll
"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" CreateWeaks  /MACHINE:x86 /def:"%~dp0..\msvcrt_light.def"  /out:"%libfileroot%\objs\msvcrt_light"

::�����ǿģʽ
::"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%libfile%" x86 "%~dp0..\msvcrt_advanced.def" msvcrt.dll msvcrt2.dll
"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" CreateWeaks  /MACHINE:x86 /def:"%~dp0..\msvcrt_advanced.def"  /out:"%libfileroot%\objs\msvcrt_advanced"


set libfiletmp=%libfile%

::copy "%libfile%" "%libfiletmp%" /y


::ɾ�����ⲿ��ǵĵ������
::lib "%libfile%" /remove:msvcrt2.dll
::ɾ������msvcrt.dll����
::lib "%libfiletmp%" /remove:msvcrt.dll



::"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%libfiletmp%" x86 all msvcrt2.dll msvcrt.dll



pushd "%libfileroot%"

md "%libfileroot%\Vista"
md "%libfileroot%\Vista\Advanced"
md "%libfileroot%\Vista\Light"

md "%libfileroot%\WinXP"
md "%libfileroot%\WinXP\Advanced"
md "%libfileroot%\WinXP\Light\"


"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%libfile%" x86 "%~dp0..\msvcrt_forward.def" msvcrt.dll msvcrt3.dll
"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%libfile%" x86 "%~dp0..\msvcrt_vista.def"   msvcrt.dll msvcrt3.dll
lib "%libfile%" /remove:msvcrt3.dll

::���ͨ��ת����
lib "%libfile%" objs\msvcrt_forward\*



::����msvcrt_light.lib for vista
set tagetlibfile=%libfileroot%\Vista\Light\msvcrt_Platform.lib
copy "%libfiletmp%" "%tagetlibfile%" /y
lib "%tagetlibfile%" objs\msvcrt_light\*

"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%tagetlibfile%" x86 "%~dp0..\msvcrt_light.def" msvcrt.dll msvcrt2.dll
lib "%tagetlibfile%" /remove:msvcrt2.dll

::����msvcrt_light_xp.lib
set tagetlibfile=%libfileroot%\WinXP\Light\msvcrt_Platform.lib
copy "%libfiletmp%" "%tagetlibfile%" /y
lib "%tagetlibfile%" objs\msvcrt_winxp\*
lib "%tagetlibfile%" objs\msvcrt_light\*

"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%tagetlibfile%" x86 "%~dp0..\msvcrt_winxp.def" msvcrt.dll msvcrt2.dll
"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%tagetlibfile%" x86 "%~dp0..\msvcrt_light.def" msvcrt.dll msvcrt2.dll
lib "%tagetlibfile%" /remove:msvcrt2.dll
lib "%tagetlibfile%" "%~dp0ntdlllite.lib"
lib "%tagetlibfile%" "%~dp0msvcrt_form_msvcp60_WinXP.lib"

::����msvcrt_advanced.lib for vista
set tagetlibfile=%libfileroot%\Vista\Advanced\msvcrt_Platform.lib
copy "%libfiletmp%" "%tagetlibfile%" /y
lib "%tagetlibfile%" objs\msvcrt_advanced\*

"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%tagetlibfile%" x86 "%~dp0..\msvcrt_advanced.def" msvcrt.dll msvcrt2.dll
lib "%tagetlibfile%" /remove:msvcrt2.dll

::����msvcrt_advanced_xp.lib
set tagetlibfile=%libfileroot%\WinXP\Advanced\msvcrt_Platform.lib
copy "%libfiletmp%" "%tagetlibfile%" /y
lib "%tagetlibfile%" objs\msvcrt_winxp\*
lib "%tagetlibfile%" objs\msvcrt_advanced\*

"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%tagetlibfile%" x86 "%~dp0..\msvcrt_winxp.def" msvcrt.dll msvcrt2.dll
"D:\�û�����\Documents\Visual Studio 2017\Projects\ltlbuild\Debug\LibMaker.exe" renamelib "%tagetlibfile%" x86 "%~dp0..\msvcrt_advanced.def" msvcrt.dll msvcrt2.dll
lib "%tagetlibfile%" /remove:msvcrt2.dll
lib "%tagetlibfile%" "%~dp0ntdlllite.lib"
lib "%tagetlibfile%" "%~dp0msvcrt_form_msvcp60_WinXP.lib"


popd


::lib "%libfile%" "%~dp0ntdlllite.lib"

del "%~dp0msvcrtdll.*" /q

pause