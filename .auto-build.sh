#!/bin/sh

################################################################################
# Title         : .auto-build.sh
# Date created  : 2 August 2018
__AUTHOR__="Erriez"
#
# This script will start PlatformIO build.
#
################################################################################

################################################################################
##### Setup this script and get the current gh-pages branch.               #####
echo 'Setting up the script...'

# Exit with nonzero exit code if anything fails
set -e

# Build sources
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/ContinuesMode/BH1750ContinuesAsynchronous/BH1750ContinuesAsynchronous.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/ContinuesMode/BH1750ContinuesBasic/BH1750ContinuesBasic.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/ContinuesMode/BH1750ContinuesHighResolution/BH1750ContinuesHighResolution.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/ContinuesMode/BH1750ContinuesLowResolution/BH1750ContinuesLowResolution.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/ContinuesMode/BH1750ContinuesPowerMgt/BH1750ContinuesPowerMgt.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/OneTimeMode/BH1750OneTimeBasic/BH1750OneTimeBasic.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/OneTimeMode/BH1750OneTimeHighResolution/BH1750OneTimeHighResolution.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/OneTimeMode/BH1750OneTimeLowResolution/BH1750OneTimeLowResolution.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/OneTimeMode/BH1750OneTimePowerMgt/BH1750OneTimePowerMgt.ino
