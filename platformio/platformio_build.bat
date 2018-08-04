rem Install Python27 platformio
rem C:\Python27\Scripts\pip.exe install -U platformio

rem Set Python path
set PATH=%PATH%;C:\Python27
set PATH=%PATH%;C:\Python27\Scripts

rem Update library
rem git fetch
rem git pull

rem Build example(s)
platformio ci --lib=".." --project-conf=platformio.ini ../examples/ContinuesMode/BH1750ContinuesAsynchronous/BH1750ContinuesAsynchronous.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/ContinuesMode/BH1750ContinuesBasic/BH1750ContinuesBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/ContinuesMode/BH1750ContinuesHighResolution/BH1750ContinuesHighResolution.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/ContinuesMode/BH1750ContinuesLowResolution/BH1750ContinuesLowResolution.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/ContinuesMode/BH1750ContinuesPowerMgt/BH1750ContinuesPowerMgt.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/OneTimeMode/BH1750OneTimeBasic/BH1750OneTimeBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/OneTimeMode/BH1750OneTimeHighResolution/BH1750OneTimeHighResolution.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/OneTimeMode/BH1750OneTimeLowResolution/BH1750OneTimeLowResolution.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/OneTimeMode/BH1750OneTimePowerMgt/BH1750OneTimePowerMgt.ino

@pause