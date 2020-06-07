dp0=$(dirname $(readlink -f $0))
cd "$dp0/.."
./vendor/bin/premake/premake5-linux gmake2
