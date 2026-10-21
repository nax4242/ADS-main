cd ..
@if not exist build mkdir build
cd build
cmake ..
if %errorlevel% equ 0 for %%f in (*.sln) do start "" "%%f"
if %errorlevel% equ 0 for %%f in (*.slnx) do start "" "%%f"