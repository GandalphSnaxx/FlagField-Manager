@echo off

echo "Configuring cmake"
cmake -S . -B ./build

echo "Building project..."
cmake --build ./build