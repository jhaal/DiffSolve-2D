#!/bin/bash
cd 12by12
echo "Compiling DiffSolve-2D.cpp from 12by12 folder"
make
echo "Running DiffSolve-2D.cpp from Test_NMPC folder"
./DiffSolve-2D

cd ../12by16
echo "Compiling DiffSolve-2D.cpp from 12by16 folder"
make
echo "Running DiffSolve-2D.cpp from 12by16 folder"
./DiffSolve-2D.cpp