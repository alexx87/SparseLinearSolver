
SET build_path="build"
SET install_path="bin"
SET sdk_path=""
SET cmake_path=""


set config_types=Debug;Release;RelWithDebInfo
set install_types=%config_types%
set sCMakeConfig="Visual Studio 17 2022"
set MKL_ROOT="C:/Program Files (x86)/Intel/oneAPI/mkl/2023.0.0"

cmake -S"." -G%sCMakeConfig% -B%build_path% -A"x64"  -DCMAKE_INSTALL_PREFIX=%install_path%