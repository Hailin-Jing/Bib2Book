@echo of

if not defined TAG (
    set TAG=1
    start wt -p "cmd" %0
    :: Windows Terminal 中 cmd 的配置名，我这里是“cmd”
    exit
)

# copy /y "../../build-Bib2Book-Desktop_Qt_5_14_2_MinGW_64_bit-Release/release/Bib2Book.exe" "../../Bib2Book/release/Bib2Book.exe"

windeployqt Bib2Book.exe

pause