set current_path=%cd%
for /d %%i in (*) do (
    cd %%i/programme
    REM make
    cd ../script
    REM copy /y ..\..\run.1.bat .\run.bat
    run.bat
    cd ../..
)