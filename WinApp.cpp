‎DirectXGame.vcxproj
+ 2


Original file line number	Original file line	Diff line number	Diff line change
@@ - 168, 6 + 168, 7 @@ copy "$(WindowsSdkDir)bin\$(TargetPlatformVersion)\x64\dxil.dll" "$(TargetDir)dx
< ClCompile Include = "Input.cpp" / >
<ClCompile Include = "Input.cpp" / >
<ClCompile Include = "main.cpp" / >
<ClCompile Include = "main.cpp" / >
<ClCompile Include = "MyMath.cpp" / >
<ClCompile Include = "MyMath.cpp" / >
<ClCompile Include = "WinApp.cpp" / >
< / ItemGroup>
< / ItemGroup>
<ItemGroup>
<ItemGroup>
<ClInclude Include = "DebugReporter.h" / >
<ClInclude Include = "DebugReporter.h" / >
@@ - 183, 6 + 184, 7 @@ copy "$(WindowsSdkDir)bin\$(TargetPlatformVersion)\x64\dxil.dll" "$(TargetDir)dx
< ClInclude Include = "MyMath.h" / >
<ClInclude Include = "MyMath.h" / >
<ClInclude Include = "ResourceObject.h" / >
<ClInclude Include = "ResourceObject.h" / >
<ClInclude Include = "Struct.h" / >
<ClInclude Include = "Struct.h" / >
<ClInclude Include = "WinApp.h" / >
< / ItemGroup>
#include"WinApp.h"

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return LRESULT();
}
void WinApp::Initialize()
{
}
void WinApp::Update()
{
}