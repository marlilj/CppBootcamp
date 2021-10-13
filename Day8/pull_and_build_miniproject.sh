#!/bin/bash

echo "Fetching newest changes"
git fetch # collects newest changes
git checkout origin/main -- Miniproject/*.cpp Miniproject/*.h # checkout Miniproject

echo "Changing directory to $(git rev-parse --show-toplevel)/Miniproject"
cd "$(git rev-parse --show-toplevel)/Miniproject"
g++ main.cpp reader.cpp printer.cpp solver.cpp -o bash_main

if [[ "$1" ]]; then
    echo "Running ./bash_main $1"
    ./bash_main "$1"
else
    echo "Input file must be provided as argument!"
fi

git checkout main # checkout master again