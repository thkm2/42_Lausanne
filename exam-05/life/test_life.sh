#!/bin/bash
cd "$(dirname "$0")"
gcc -o life my-life-2.c || exit 1

PASS=0
FAIL=0

check() {
    local name="$1" input="$2" args="$3" expected="$4"
    actual=$(echo "$input" | ./life $args)
    if [ "$actual" = "$expected" ]; then
        echo "OK   $name"
        PASS=$((PASS + 1))
    else
        echo "FAIL $name"
        echo "  expected:"
        echo "$expected" | cat -e
        echo "  got:"
        echo "$actual" | cat -e
        FAIL=$((FAIL + 1))
    fi
}

# ===== RULE: Underpopulation (< 2 neighbors -> die) =====

# Single cell dies (0 neighbors)
check "Underpopulation: single cell dies" \
    "ddssx" "5 5 1" \
"$(printf '     \n     \n     \n     \n     ')"

# Two adjacent cells die (1 neighbor each)
check "Underpopulation: two cells die" \
    "dsxd" "4 4 1" \
"$(printf '    \n    \n    \n    ')"

# ===== RULE: Survival (2 or 3 neighbors -> live) =====

# Block (still life) - each cell has 3 neighbors, stable forever
check "Survival: block still life (10 iter)" \
    "dsxdsa" "4 4 10" \
"$(printf '    \n OO \n OO \n    ')"

# Blinker period 2 - cells survive with 2 neighbors
check "Survival: blinker returns after 2 iter" \
    "dxss" "3 3 2" \
"$(printf ' O \n O \n O ')"

# ===== RULE: Overpopulation (> 3 neighbors -> die) =====

# Cross pattern: center has 4 neighbors -> dies
check "Overpopulation: cross center dies" \
    "dxsaxddxxsax" "3 3 1" \
"$(printf 'OOO\nO O\nOOO')"

# ===== RULE: Reproduction (dead + 3 neighbors -> born) =====

# L-shape becomes block (corner cell born with exactly 3 neighbors)
check "Reproduction: L-shape becomes block" \
    "dsxdxsax" "4 4 1" \
"$(printf '    \n OO \n OO \n    ')"

# ===== OSCILLATORS =====

# Blinker: vertical -> horizontal -> vertical
check "Oscillator: blinker gen 0 (vertical)" \
    "dxss" "3 3 0" \
"$(printf ' O \n O \n O ')"

check "Oscillator: blinker gen 1 (horizontal)" \
    "dxss" "3 3 1" \
"$(printf '   \nOOO\n   ')"

check "Oscillator: blinker gen 2 (back vertical)" \
    "dxss" "3 3 2" \
"$(printf ' O \n O \n O ')"

# ===== GLIDER (tests all rules together) =====

# Glider gen 0
check "Glider: gen 0" \
    "dxxsdxxsaaxdd" "10 10 0" \
"$(printf ' O        \n  O       \nOOO       \n          \n          \n          \n          \n          \n          \n          ')"

# Glider gen 1
check "Glider: gen 1" \
    "dxxsdxxsaaxdd" "10 10 1" \
"$(printf '          \nO O       \n OO       \n O        \n          \n          \n          \n          \n          \n          ')"

# Glider gen 4 (shifted 1 step diagonally)
check "Glider: gen 4 (moved diag)" \
    "dxxsdxxsaaxdd" "10 10 4" \
"$(printf '          \n  O       \n   O      \n OOO      \n          \n          \n          \n          \n          \n          ')"

# ===== EMPTY BOARD =====

check "Empty board stays empty" \
    "" "3 3 5" \
"$(printf '   \n   \n   ')"

# ===== SUBJECT EXAMPLES =====

check "Subject example 1" \
    "sdxddssaaww" "5 5 0" \
"$(printf '     \n OOO \n O O \n OOO \n     ')"

check "Subject example 2" \
    "sdxssdswdxddddsxaadwxwdxwaa" "10 6 0" \
"$(printf '          \n O   OOO  \n O     O  \n OOO  O   \n  O  OOO  \n          ')"

echo ""
echo "Results: $PASS passed, $FAIL failed"
[ $FAIL -eq 0 ] && echo "ALL TESTS PASSED" || echo "SOME TESTS FAILED"
