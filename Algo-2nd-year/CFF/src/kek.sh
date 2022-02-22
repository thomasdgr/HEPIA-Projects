#!/bin/bash

javac Main.java

for number in 1 2 3 4 5 6 7 8 9 10
do
    cat Tests/commandes_de_test/cmd_a_tester_pt_"$number".txt | java Main > Tests/results_out/my_results_"$number".txt
done

for number in 1 2 3 4 5 6 7 8 9 10
do
    diff Tests/results_out/my_results_"$number".txt Tests/results_out/_"$number".txt
done

rm *.class