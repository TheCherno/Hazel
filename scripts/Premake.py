
import platform
from pathlib import Path

from io import BytesIO
from urllib.request import urlopen
from zipfile import ZipFile

g_Premake_zip_urls = {
    "Windows": 'https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-windows.zip',
    "Linux": 'https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-linux.tar.gz',
    "Darwin": 'https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-macosx.tar.gz'
}

g_Premake_location = 'vendor/premake/bin'

def InstallPremake():
    platformName = platform.system()
    if (platformName != "Windows"):
        print("Hazel currently supports Windows only.")
        return False

    premakeExe = ""
    if (platformName == 'Windows'):
        premakeExe = Path(f"{g_Premake_location}/premake5.exe")
    else:
        premakeExe = Path(f"{g_Premake_location}/premake5")

    if (not premakeExe.exists()):
        print('Premake not found.')
        print('   Downloading premake...')
        with urlopen(g_Premake_zip_urls[platformName]) as zipresp:
            with ZipFile(BytesIO(zipresp.read())) as zfile:
                zfile.extractall(g_Premake_location)
        print(f"   Premake (v.5.0-alpha16) has been downloaded to '{g_Premake_location}'")

    return True
