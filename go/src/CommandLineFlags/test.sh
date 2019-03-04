#!/bin/bash
./CommandLineFlags -word=opt -numb=7 -fork -svar=flag
./CommandLineFlags -word=opt
./CommandLineFlags -word=opt a1 a2 a3
./CommandLineFlags -word=opt a1 a2 a3 -numb=7
./CommandLineFlags -h
./CommandLineFlags -wat
