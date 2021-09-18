How to build PlatformIO based project
=====================================
## PlatformIO IDE
1. Install PlatformIO IDE for VSCode  
   <https://platformio.org/platformio-ide>
2. Open HerbFarm Workspace 
3. Press `Ctrl+Shift+P` and select
    ```bash
    # Build project
    >PlatformIO: Build

    # Upload firmware
    >PlatformIO: Upload

    # Update installed platforms, packages and libraries
    >PlatformIO: Update All (platforms, packages, libraries)
    ```

## PlatformIO Core
1. Install PlatformIO Core  
   <http://docs.platformio.org/page/core.html>
2. Download development platform with examples  
   <https://github.com/platformio/platform-espressif32/archive/develop.zip>
3. Extract ZIP archive
4. Run these commands:
    ```bash
    # Build project
    $> platformio run

    # Upload firmware
    $> platformio run --target upload

    # Build specific environment
    $> platformio run -e wpa

    # Upload firmware for the specific environment
    $> platformio run -e wpa --target upload

    # Clean build files
    $> platformio run --target clean
    ```
