set(CMAKE_SYSTEM_NAME Windows)

if (MSYS OR MINGW)
	set(CMAKE_CROSSCOMPILING TRUE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-qual -Wcast-align -Wpointer-arith -Wshadow -Wall -Wextra -Wreturn-type -Wwrite-strings -Wno-unused-parameter -DWINVER=0x501")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ftree-vectorize -msse3 -DNDEBUG -D_FORTIFY_SOURCE=2")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -DDEBUG=1 -ggdb")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -Wnon-virtual-dtor")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_C_FLAGS_RELEASE}")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_C_FLAGS_DEBUG}")

	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows -static-libgcc -static-libstdc++")
	set(CMAKE_C_STANDARD_LIBRARIES "-lmingw32 -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -lws2_32 -liphlpapi")
	set(CMAKE_CXX_STANDARD_LIBRARIES "-lmingw32 -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -lws2_32 -liphlpapi")
elseif (MSVC)
	set(CMAKE_C_STANDARD_LIBRARIES "kernel32.lib user32.lib gdi32.lib winspool.lib winmm.lib imm32.lib version.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib dbghelp.lib wsock32.lib ws2_32.lib iphlpapi.lib rpcrt4.lib wininet.lib")
	set(CMAKE_CXX_STANDARD_LIBRARIES "kernel32.lib user32.lib gdi32.lib winspool.lib winmm.lib imm32.lib version.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib dbghelp.lib wsock32.lib ws2_32.lib iphlpapi.lib rpcrt4.lib wininet.lib")
endif()
