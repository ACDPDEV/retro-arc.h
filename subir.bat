@echo off
echo Descargando cambios del equipo...
git pull origin main
echo Preparando tus archivos...
git add .
set /p msg="Escribe que cambiaste y presiona Enter: "
git commit -m "%msg%"
echo Subiendo tu parte a GitHub...
git push origin main
echo.
echo ¡Todo listo y actualizado!
pause
