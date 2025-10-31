#!/usr/bin/env zsh
setopt null_glob

# Get project name from user
read "project_name?✓ Enter the project name: "

# Get lab number from user
read "lab_number?✓ Enter the lab number: "

# Zero-pad lab number if needed
if [ $lab_number -lt 10 ]; then
    lab_number="0$lab_number"
fi

# Directories
root_dir="$(pwd)"
project_dir="$root_dir/lab$lab_number"

# Clean up existing project directory if it exists
if [ -d "$project_dir" ]; then
    echo "⚠️ lab$lab_number already exists. Removing it..."
    rm -rf "$project_dir"
fi

# Create project directory
mkdir -p "$project_dir"/{tests,src,include}
cd "$project_dir"

# Create a cpp file named app.cpp in src and app.h in include
touch src/main.cpp include/app.h

# Check libgtest installation
if [ ! -d "/usr/src/gtest" ]; then
    echo "⚠️ libgtest not found. Please make sure it is installed."
fi

# Copy templates from init dir
for file in "$root_dir"/init/**/*; do
    if [ -f "$file" ]; then
        relative_path="${file#"$root_dir/init/"}"
        mkdir -p "$(dirname "$project_dir/$relative_path")"
        sed "s/<project_name>/$project_name/g" "$file" > "$project_dir/$relative_path"
    fi
done
