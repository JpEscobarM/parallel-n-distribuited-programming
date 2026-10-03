set terminal gif animate delay 10
set output 'animacao.gif'

set pm3d map
set xlabel "X"
set ylabel "Y"
set title "Difusão de calor"

do for [i=0:99] {
    splot 'saida.txt' index i matrix
}

