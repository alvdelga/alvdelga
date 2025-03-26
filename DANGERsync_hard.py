#!/usr/bin/env python3

import os
import subprocess
import sys

def run_cmd(command):
    print(f"🛠 Ejecutando: {command}")
    result = subprocess.run(command, shell=True)
    if result.returncode != 0:
        print(f"❌ Error ejecutando: {command}")
        sys.exit(result.returncode)

def main():
    # Verifica que estás dentro de un repositorio Git
    if not os.path.isdir(".git"):
        print("❌ Esto no parece un repositorio Git.")
        sys.exit(1)

    # Sincronización dura con el remoto
    run_cmd("git fetch origin")
    run_cmd("git reset --hard origin/main")
    run_cmd("git clean -fd")

    print("✅ Repositorio sincronizado con origin/main y limpio.")

if __name__ == "__main__":
    main()
