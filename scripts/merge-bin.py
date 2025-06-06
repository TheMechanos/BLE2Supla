import os
from pathlib import Path
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

def merge_bin(source, target, env):
    build_dir = Path(env.subst("$BUILD_DIR"))
    output_bin = build_dir / "merged-firmware.bin"

    # Lista (offset, plik) do mergowania
    segments = [
        ("0x1000", build_dir / "bootloader.bin"),
        ("0x8000", build_dir / "partitions.bin"),
        ("0x10000", build_dir / "firmware.bin")
    ]

    # Komenda podstawowa
    esptool_cmd = [
        "esptool",
        "--chip", env["BOARD_MCU"],
        "merge_bin",
        "-o", str(output_bin),
        "--flash_mode", "dio",
        "--flash_freq", "40m",
        "--flash_size", "4MB",
        "--target-offset", "0x1000"
    ]

    # Dodaj offsety i ścieżki plików
    for offset, filepath in segments:
        esptool_cmd.extend([offset, str(filepath)])

    # Wypisz komendę
    print(f"[merge_bin] Merging to {output_bin}")
    print("[merge_bin] Running command:")
    print(" ".join(esptool_cmd))

    # Wykonaj komendę
    ret = os.system(" ".join(esptool_cmd))
    if ret != 0:
        print("[merge_bin] esptool merge_bin failed!")
        env.Exit(1)

# Wywołaj po wygenerowaniu firmware.bin
env.AddPostAction("$BUILD_DIR/firmware.bin", merge_bin)