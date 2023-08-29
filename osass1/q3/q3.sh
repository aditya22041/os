#!/bin/bash

# Create the Result directory if it doesn't exist
mkdir -p Result

# Store the input file contents in an array
mapfile -t lines < input.txt

# Get the total number of lines
num_lines=${#lines[@]}

# Loop through each line
for ((i=0; i<num_lines; i++)); do
    line=${lines[i]}
    List=($line)
    if [[ ${#List[@]} -ne 3 ]]; then
        echo "Error in input at line $((i+1))"
    else
        if [[ ${List[2]} == "compare" ]]; then
            result=$(( ${List[0]} > ${List[1]} ? ${List[0]} : ${List[1]} ))
            echo "Comparison result: $result"

        elif [[ ${List[2]} == "product" ]]; then
            result=$(( ${List[0]} * ${List[1]} ))
            echo "Product result: $result"

        elif [[ ${List[2]} == "xor" ]]; then
            result=$(( ${List[0]} ^ ${List[1]} ))
            echo "XOR result: $result"

        else
            echo "Invalid operation at line $((i+1))"
        fi

        # Write the result to the output file
        echo "$result" >> Result/output.txt

        # Add a newline after the last line if it's not the end of the file
        if [[ $i -ne $((num_lines-1)) ]]; then
            echo >> Result/output.txt
        fi
    fi
done