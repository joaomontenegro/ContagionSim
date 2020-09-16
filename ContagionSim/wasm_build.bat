@echo off

set FILES=^
arenaRenderer.cpp ^
collision.cpp ^
disease.cpp ^
gridCollision.cpp ^
hospitalDisease.cpp ^
log.cpp ^
movement.cpp ^
run.cpp ^
simpleCollision.cpp ^
simpleDisease.cpp ^
simpleMovement.cpp ^
simulation.cpp ^
wasmMain.cpp ^
window.cpp

set OUTDIR=./wasm.out

:: Make sure the emscripten environment is set
if "%EMSDK%"=="" call emsdk_env

:: Create output dir
if not exist "%OUTDIR%" mkdir %OUTDIR%

:: Build
call emcc %FILES% -s WASM=1 -O3 -s USE_SDL=2 -s LEGACY_GL_EMULATION=1 --preload-file Params/contagion.params -owasm.out/contagion.html
