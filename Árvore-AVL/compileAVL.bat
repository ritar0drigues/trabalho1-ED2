@echo off
gcc -std=c11 -Wall -Wextra -O2 mainAVL.c ApresentadoresAVL.c CategoriasAVL.c ProgramasAVL.c StreamsAVL.c UtilsAVL.c -o mainAVL.exe
if %errorlevel% neq 0 (
    echo ❌ Erro na compilacao!
    exit /b %errorlevel%
)
echo ✅ Compilacao concluida. Rode: .\mainAVL.exe