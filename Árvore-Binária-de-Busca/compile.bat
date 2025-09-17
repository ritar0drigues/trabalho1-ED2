@echo off
gcc -std=c11 -Wall -Wextra -O2 main.c Apresentadores.c Categorias.c Programas.c Streams.c Utils.c -o main.exe
if %errorlevel% neq 0 (
    echo ❌ Erro na compilacao!
    exit /b %errorlevel%
)
echo ✅ Compilacao concluida. Rode: .\main.exe