#!/bin/bash

# Usage: ./test_kalah.sh numHouses numSeeds

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print usage
print_usage(){
    echo -e "${YELLOW}Usage: $0 numHouses numSeeds${NC}"
}

# Check if exactly two arguments are provided
if [ "$#" -ne 2 ]; then
    print_usage
    exit 1
fi

NUM_HOUSES=$1
NUM_SEEDS=$2

# Directory containing test files
TEST_DIR="tests"

# Check if the test directory exists
if [ ! -d "$TEST_DIR" ]; then
    echo -e "${RED}Error:${NC} Test directory '${TEST_DIR}' does not exist."
    exit 1
fi

# Initialize counters
TOTAL=0
PASSED=0

# Header for test results
echo -e "${BLUE}================= Kalah Test Suite =================${NC}"
echo ""

# Iterate over all .in files in the test directory matching the pattern sample*.in
shopt -s nullglob
INPUT_FILES=("$TEST_DIR/sample"*.in)
shopt -u nullglob

if [ "${#INPUT_FILES[@]}" -eq 0 ]; then
    echo -e "${YELLOW}No input files found in '${TEST_DIR}'.${NC}"
    exit 1
fi

for INPUT_FILE in "${INPUT_FILES[@]}"; do
    # Extract the test number using parameter expansion and regex
    BASENAME=$(basename "$INPUT_FILE")
    if [[ "$BASENAME" =~ sample([0-9]+)\.in ]]; then
        TEST_NUM="${BASH_REMATCH[1]}"
    else
        echo -e "${YELLOW}Warning:${NC} Filename '$BASENAME' does not match the expected pattern 'sample<test_num>.in'. Skipping."
        continue
    fi

    EXPECTED_OUTPUT_FILE="$TEST_DIR/sample${TEST_NUM}.out"
    OUTPUT_FILE="output_${TEST_NUM}.txt"

    # Check if the expected output file exists
    if [ ! -f "$EXPECTED_OUTPUT_FILE" ]; then
        echo -e "${YELLOW}Warning:${NC} Expected output file '$EXPECTED_OUTPUT_FILE' not found. Skipping test $TEST_NUM."
        continue
    fi

    # Execute the kalah program with the provided arguments, piping the input
    if ! ./kalah "$NUM_HOUSES" "$NUM_SEEDS" < "$INPUT_FILE" > "$OUTPUT_FILE"; then
        echo -e "${RED}Test $TEST_NUM: ERROR${NC} - Program execution failed."
        TOTAL=$((TOTAL + 1))
        continue
    fi

    # Compare the output with the expected output
    if diff -q "$OUTPUT_FILE" "$EXPECTED_OUTPUT_FILE" > /dev/null; then
        echo -e "Test ${GREEN}#${TEST_NUM}${NC}: ${GREEN}PASSED${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "Test ${RED}#${TEST_NUM}${NC}: ${RED}FAILED${NC}"
        echo -e "Differences:"
        diff "$OUTPUT_FILE" "$EXPECTED_OUTPUT_FILE" | sed "s/^/${RED}    /"
    fi

    # Increment total tests
    TOTAL=$((TOTAL + 1))

    # Optionally, remove the temporary output file
    rm "$OUTPUT_FILE"
done

# Summary of test results
echo ""
echo -e "${BLUE}================= Test Summary =================${NC}"
echo -e "Total tests run: ${TOTAL}"
echo -e "Tests passed:    ${GREEN}${PASSED}${NC}"
echo -e "Tests failed:    ${RED}$((TOTAL - PASSED))${NC}"
echo -e "${BLUE}===============================================${NC}"
