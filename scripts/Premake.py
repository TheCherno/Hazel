from pathlib import Path

from io import BytesIO
from urllib.request import urlopen
from zipfile import ZipFile

g_Premake_zip_url = 'https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-windows.zip'
g_Premake_location = 'vendor/premake/bin'

def InstallPremake():
    premakeExe = Path(f"{g_Premake_location}/premake5.exe")
    if (not premakeExe.exists()):
        print('Premake not found.')
        print('   Downloading premake...')
        with urlopen(g_Premake_zip_url) as zipresp:
            with ZipFile(BytesIO(zipresp.read())) as zfile:
                zfile.extractall(g_Premake_location)
        print(f"   Premake (v.5.0-alpha16) has been downloaded to '{g_Premake_location}'")
