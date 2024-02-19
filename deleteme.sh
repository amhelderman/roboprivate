#!/bin/bash

# Define lessons with their summaries
declare -A lessons=(
    ["unit_000_demos_slam_with_opencl"]="Demonstrates SLAM (Simultaneous Localization and Mapping) using OpenCL for real-time GPU processing."
    ["unit_000_demos_object_detection_with_opencl"]="Covers object detection techniques using OpenCL for GPU-accelerated real-time detection."
    ["unit_000_demos_nlp_with_opencl"]="Explores the application of OpenCL in natural language processing for efficient GPU text analysis."
    ["unit_000_demos_dqn_on_opencl"]="Demonstrates implementing Deep Q-Networks (DQN) with OpenCL for reinforcement learning on GPUs."
    ["unit_000_demos_sha256_with_opencl"]="Provides insights into SHA-256 hashing algorithm optimization with OpenCL on GPUs."
    # Add more lessons here
)

# Create folders and README.md files for each lesson
for lesson in "${!lessons[@]}"; do
    mkdir -p "$lesson"
    echo "${lessons[$lesson]}" > "$lesson/README.md"
done

echo "Folders and README.md files created for each lesson."
