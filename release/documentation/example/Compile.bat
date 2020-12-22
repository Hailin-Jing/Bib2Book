@echo off

cd "C:/Users/Hailin/OneDrive/Documents/GitHub/Bib2Book/release/documentation/example"

xelatex Cover

xelatex example
xelatex example

del Cover.aux
del Cover.log
del Cover.out
del Cover.synctex.gz

del example.aux
del example.log
del example.out
del example.synctex.gz
