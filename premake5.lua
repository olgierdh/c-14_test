workspace "test"
    configurations { "Debug", "Release" }
    toolset "clang"

    filter "configurations:Debug"
        targetdir "bin/debug"
        defines { "_DEBUG" }
        buildoptions { "-fno-omit-frame-pointer", "-fsanitize=address", "-O1", "-g" }
        linkoptions { "-fno-omit-frame-pointer", "-fsanitize=address" }

    filter "configurations:Release"
        targetdir "bin/release"
        buildoptions { "-O3" }
        defines { "NDEBUG" }

    filter "language:c++"
        buildoptions { "-std=c++14", "-stdlib=libc++", "-pedantic", "-Wall" }
    
project "test_overload"
    kind "ConsoleApp"
    language "c++"
    files { "**.hxx", "**.cxx" }
    links { "c++" }



