# forest-fire-model
Implementation of Forest-fire model


x64 Native Tools Command Prompt for VS

SDL2-2.0.22 dowlnload link: https://github.com/libsdl-org/SDL/releases/download/release-2.0.22/SDL2-devel-2.0.22-VC.zip

cd C:\Users\stefanopi\Progetti\personal\forest-fire-model\src

cl main.c forest.c /I"..\SDL2-2.0.22\include" /link /LIBPATH:"..\SDL2-2.0.22\lib\x64" SDL2.lib SDL2main.lib Shell32.lib User32.lib /SUBSYSTEM:CONSOLE

main.exe