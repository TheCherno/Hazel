import sys
import subprocess
import platform
from pathlib import Path

from io import BytesIO
from urllib.request import urlopen
from zipfile import ZipFile

class PremakeConfiguration:
    premakeVersion = "v5.0.0-alpha16"
    premakeZipUrls = "https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-windows.zip"
    premakeDirectory = "./vendor/premake/bin"

    @classmethod
    def Validate(cls):
        if (not cls.CheckIfPremakeInstalled()):
            print("Premake can not be installed correctly.")
            return

        print("Premake is installed")

    @classmethod
    def CheckIfPremakeInstalled(cls):
        premakeExe = Path(f"{cls.premakeDirectory}/premake5.exe");
        if (not premakeExe.exists()):
            permissionGranted = False
            while not permissionGranted:
                reply = str(input("Premake not found. Would you like to install Preamake {0:s}? [Y/N]: ".format(cls.premakeVersion))).lower().strip()[:1]
                if reply == 'n':
                    return False
                permissionGranted = (reply == 'y')
            return cls.InstallPremake()

        return True

    @classmethod
    def InstallPremake(cls):
        print("    Downloading Premake...")
        with urlopen(cls.premakeZipUrls) as zipresp:
            with ZipFile(BytesIO(zipresp.read())) as zfile:
                zfile.extractall(cls.premakeDirectory)
        print(f"    Premake {cls.premakeVersion} has been downloaded to '{cls.premakeDirectory}'")

        return True
