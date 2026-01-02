#!/bin/bash

# Check if the 'json_parser' executable exists
if [ ! -x build/src/jpar ]; then
  echo "Error: 'jpar' executable not found or not executable."
  exit 1
fi

# Specify the folder containing the files
folder="./test/"

# Check if the folder exists
if [ ! -d "$folder" ]; then
  echo "Error: Folder '$folder' does not exist."
  exit 1
fi

# Initialize counters for VALID JSON and INVALID JSON
total_cases=0
correct_result=0
incorrect_result=0


# Loop through all files in the folder and execute 'jpar' for each file
for filename in "$folder"/*; do
  if [ -f "$filename" ]; then
    echo "Processing file: $filename"
    output=$(build/src/jpar "$filename")
    echo $output
    ((total_cases++))
    if [ "$output" == "VALID JSON" ] && [[ "$filename" == *pass* ]]; then
      ((correct_result++))
    elif [ "$output" == "INVALID JSON" ] && [[ "$filename" == *fail* ]]; then
      ((correct_result++))
    fi
  fi
done

((incorrect_result = total_cases - correct_result))

# Print the counts
echo "*************************************"
echo "Number of test cases        : $total_cases"
echo "Number of test cases passed : $correct_result"
echo "Number of test cases failed : $incorrect_result"