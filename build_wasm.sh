#!/bin/bash
set -e

echo "[ MISFIT-SOLACE // EXECUTING SEPARATED WEB SOURCE ASSEMBLY ]"

emcc web_main.cpp -O3 \
    -s WASM=1 \
    -s FORCE_FILESYSTEM=1 \
    --js-library library_stdin.js \
    -o docs/index.html \
    --shell-file shell_minimal.html

echo "[ COMPLETE // WEB PAYLOAD ISOLATED IN docs/ ]"

