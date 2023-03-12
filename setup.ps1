cd project

rm -r bin
rm -r build

mkdir 'bin/debug'
mkdir 'bin/release'
mkdir 'bin/tests'

mkdir 'build/debug'
mkdir 'build/release'
mkdir 'build/tests'

robocopy '../../../libraries/boost_1_79_0/stage/lib' 'bin/debug' 'libboost_filesystem-mgw12-mt-x64-1_79.dll' 'libboost_serialization-mgw12-mt-x64-1_79.dll'
robocopy '../../../libraries/boost_1_79_0/stage/lib' 'bin/release' 'libboost_filesystem-mgw12-mt-x64-1_79.dll' 'libboost_serialization-mgw12-mt-x64-1_79.dll'
robocopy '../../../libraries/boost_1_79_0/stage/lib' 'bin/tests' 'libboost_unit_test_framework-mgw12-mt-x64-1_79.dll'

robocopy 'resources' 'bin/debug/resources' 'sphere.obj' 'icosphere.obj' 'cube.obj' 'cone.obj' 'cylinder.obj' 'torus.obj'
robocopy 'resources' 'bin/release/resources' 'sphere.obj' 'icosphere.obj' 'cube.obj' 'cone.obj' 'cylinder.obj' 'torus.obj'

cd 'build/debug'
cmake -G 'Ninja' -S '../..' -DCMAKE_BUILD_TYPE=Debug -DCMAKE_RUNTIME_OUTPUT_DIRECTORY='../../bin/debug' -DPROGRAM_BUILD=1
# ninja # compile immediately
cd '../..'

cd 'build/release'
cmake -G 'Ninja' -S '../..' -DCMAKE_BUILD_TYPE=Release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY='../../bin/release' -DPROGRAM_BUILD=1
# ninja # compile immediately
cd '../..'

cd 'build/tests'
cmake -G 'Ninja' -S '../..' -DCMAKE_BUILD_TYPE=Debug -DCMAKE_RUNTIME_OUTPUT_DIRECTORY='../../bin/tests' -DPROGRAM_BUILD=0
# ninja # compile immediately
cd '../..'

cd ..