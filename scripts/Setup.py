
import os
import subprocess
import platform

from SetupPython import PythonConfiguration as PythonRequirements

# Make sure everything we need for the setup is installed
PythonRequirements.Validate()

from SetupPremake import PremakeConfiguration as PremakeRequirements
from SetupVulkan import VulkanConfiguration as VulkanRequirements
os.chdir('./../') # Change from devtools/scripts directory to root

PremakeRequirements.Validate()
VulkanRequirements.Validate()

if platform.system() == "Windows":
    print("\nRunning premake...")
    subprocess.call([os.path.abspath("./scripts/Win-GenProjects.bat"), "nopause"])

print("\nSetup completed!")
