# christorch (starter)

Ein minimaler Startpunkt für ein PyTorch-ähnliches Projekt mit C++-Backend (pybind11) und Python-Frontend, gebaut mit CMake + scikit-build-core **inkl. C++-Unit-Tests (GoogleTest)**.

## Schnellstart (Python + Extension)
```bash
python -m venv .venv
# macOS/Linux:
source .venv/bin/activate
# Windows PowerShell:
# .venv\Scripts\Activate.ps1

python -m pip install -U pip
pip install -e .             # baut christorch._C via CMake/pybind11
pip install pytest pre-commit

pytest -q                    # Python-Tests
```

## C++-Tests (GoogleTest/ctest)
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build -V    # Unix Makefiles / Ninja
# Für MSVC Multi-Config:
# ctest --test-dir build -C Debug -V
```

## IDE
- **PyCharm**: Ordner öffnen, `.venv` als Interpreter wählen.
- **CLion**: Ordner öffnen (CMakeLists erkannt). Für C++-Debug im Python-Kontext:
  - Run/Debug-Konfiguration:
    - Program: `python`
    - Arguments: `-m pytest tests/python -q`
    - Working dir: Projekt-Root
    - (ggf.) Environment für dein venv setzen.

## Struktur
```
christorch/
├─ CMakeLists.txt
├─ pyproject.toml
├─ cpp/                # C++ Core + pybind11 bindings + GoogleTest
├─ python/christorch/  # Python-Frontend (import christorch)
├─ tests/python/       # pytest
└─ examples/
```
