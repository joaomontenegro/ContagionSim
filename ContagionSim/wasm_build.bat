@echo off

set FILES=^
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
wasm.cpp

set OUTDIR=./wasm.out

:: Make sure the emscripten environment is set
if "%EMSDK%"=="" call emsdk_env

:: Create output dir
if not exist "%OUTDIR%" mkdir %OUTDIR%

:: Build
call emcc %FILES% -s WASM=1 -owasm.out/contagion.html
