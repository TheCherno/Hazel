import sys
import os
from pathlib import Path

import Utils

class PremakeConfiguration:
    premakeVersion = "5.0.0-beta1"
    premakeZipUrls = f"https://github.com/premake/premake-core/releases/download/v{premakeVersion}/premake-{premakeVersion}-windows.zip"
    premakeLicenseUrl = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
    premakeDirectory = "./vendor/premake/bin"

    @classmethod
    def Validate(cls):
        if (not cls.CheckIfPremakeInstalled()):
            print("Premake is not installed.")
            return False

        print(f"Correct Premake located at {os.path.abspath(cls.premakeDirectory)}")
        return True

    @classmethod
    def CheckIfPremakeInstalled(cls):
        premakeExe = Path(f"{cls.premakeDirectory}/premake5.exe");
        if (not premakeExe.exists()):
            return cls.InstallPremake()

        return True

    @classmethod
    def InstallPremake(cls):
        permissionGranted = False
        while not permissionGranted:
            reply = str(input("Premake not found. Would you like to download Premake {0:s}? [Y/N]: ".format(cls.premakeVersion))).lower().strip()[:1]
            if reply == 'n':
                return False
            permissionGranted = (reply == 'y')

        premakePath = f"{cls.premakeDirectory}/premake-{cls.premakeVersion}-windows.zip"
        print("Downloading {0:s} to {1:s}".format(cls.premakeZipUrls, premakePath))
        Utils.DownloadFile(cls.premakeZipUrls, premakePath)
        print("Extracting", premakePath)
        Utils.UnzipFile(premakePath, deleteZipFile=True)
        print(f"Premake {cls.premakeVersion} has been downloaded to '{cls.premakeDirectory}'")

        premakeLicensePath = f"{cls.premakeDirectory}/LICENSE.txt"
        print("Downloading {0:s} to {1:s}".format(cls.premakeLicenseUrl, premakeLicensePath))
        Utils.DownloadFile(cls.premakeLicenseUrl, premakeLicensePath)
        print(f"Premake License file has been downloaded to '{cls.premakeDirectory}'")

        return True
