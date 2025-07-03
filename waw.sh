#!/bin/bash

# Obtenir la résolution via xrandr
res=$(xrandr | grep '*' | awk '{print $1}')
width=$(echo $res | cut -d'x' -f1)
height=$(echo $res | cut -d'x' -f2)

# Calcul du rapport (format d'écran)
gcd() {
    a=$1
    b=$2
    while [ $b -ne 0 ]; do
        temp=$b
        b=$((a % b))
        a=$temp
    done
    echo $a
}

# Trouver le plus grand commun diviseur
div=$(gcd $width $height)

# Calcul du format simplifié
format_width=$((width / div))
format_height=$((height / div))

echo "Résolution : ${width}x${height}"
echo "Format : ${format_width}:${format_height}"
