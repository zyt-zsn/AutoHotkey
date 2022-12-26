# AutoHotkey #

AutoHotkey is a free, open source macro-creation and automation software utility that allows users to automate repetitive tasks. It is driven by a custom scripting language that has special provision for defining keyboard shortcuts, otherwise known as hotkeys.

https://www.autohotkey.com/


## How to Compile ##

AutoHotkey is developed with [Microsoft Visual Studio Community 2022](https://www.visualstudio.com/products/visual-studio-community-vs), which is a free download from Microsoft.

  - Get the source code.
  - Open AutoHotkeyx.sln in Visual Studio.
  - Select the appropriate Build and Platform.
  - Build.

The project is configured to build with the Visual C++ 2010 toolset if available, primarily to facilitate Windows 2000 support but also because it appears to produce smaller 32-bit binaries than later versions. If the 2010 toolset is not available for a given platform, the project should automatically fall back to v140 (2015), v120 (2013) or v110 (2012).

Note that the fallback toolsets do not support targetting Windows XP. For that, install VS 2010 or change the platform toolset to v110_xp, v120_xp or v140_xp (if installed).

The project should also build in Visual C++ 2010, 2012 or 2013.


## Build Configurations ##

AutoHotkeyx.vcxproj contains several combinations of build configurations.  The main configurations are:

  - **Debug**: AutoHotkey.exe in debug mode.
  - **Release**: AutoHotkey.exe for general use.
  - **Self-contained**: AutoHotkeySC.bin, used for compiled scripts.

Secondary configurations are:

  - **(mbcs)**: ANSI (multi-byte character set). Configurations without this suffix are Unicode.
  - **.dll**: Builds an experimental dll for use hosting the interpreter, such as to enable the use of v1 libraries in a v2 script. See [README-LIB.md](README-LIB.md).


## Platforms ##

AutoHotkeyx.vcxproj includes the following Platforms:

  - **Win32**: for Windows 32-bit.
  - **x64**: for Windows x64.

Visual C++ 2010 officially supports XP SP2 and later.  AutoHotkey supports Windows XP pre-SP2 and Windows 2000 via an asm patch (win2kcompat.asm).  Older versions are not supported.
