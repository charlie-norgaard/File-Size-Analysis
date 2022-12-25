<!-- SUMMARY -->
## Summary

This program uses multiple bash scripts, a C program, and an R script to calculate statistics and a scatterplot about the relative file sizes of C code files. The program works as such:

- geturls [OUTPUT FILE] [HTML FILE]  : extracts all .c file URLS from the given HTML page and writes them into the given output file
- measurepage [URL] : takes a URL as an argument and outputs the size of the corresponding page in words
- wordcount.c : emulates the unix command wc; for the purposes of this project, wordcount is only used with the -w option
- runanalysis [OUTPUT FILE] [INPUT FILE] : runs measure page on each URL in the input file and writes the results to the given output file
- scatterplot.R : reads in a file containing the data generated by runanalysis and generates a scatterplot of the data