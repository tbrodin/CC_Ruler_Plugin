# CC_Ruler_Plugin
This is a simple ruler creator plugin for ClouCompare 

## Preparations

1. Clone the CloudCompare project and checkout the correct version tag (to the one you want to build the plugin for). Also follow all the preparation instructions of the CloudCompare project. For example by downloading QT.

2. Make sure this projects repository is cloned to be at a sibling level of the folder where the source code of CloudCompare is.

3. Add following line to the end of CMakeList.txt in source code directory of the CloudCompare projects (..\CloudCompare\plugins\):
   ```
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../CC_Ruler_Plugin ${CMAKE_CURRENT_BINARY_DIR}/CC_Ruler_Plugin)
   ```
   This ensures that the plugin project can be built together with the CloudCompare project.
 

4. Make sure you have the correct default verions of QT (qmake) set.
To se which version that is active open Cmd and run:
   ```
     qmake --version in cmd to se active QT-version.
    ```
If the version is incorrect you might need to add correct version to Environment variable PATH and reorder it so it becomes the prioritized qmake version.

 
***Make sure to compile the plugin using the EXACT same QT-version and MSVC-version as was used for the installed CloudCompare version that you want to use the plugin with (For example by using Qt 5.9.9 and MSVC1916 for CloudCompare 2.11.3) *** (Versions used can be found by starting your installed CloudCompare and open Help->About..)


5. Generate the CloudCompare project using cmake (for example with Cmake-gui) according to the CloudCompare projects README. If preparations are done correctly you will be able to choose to generate the Plugin project (PLUGIN_LOAD_P3KA) together with the CloudCompare project.
Make sure to set CMAKE_INSTALL_PREFIX to other directory than "Program Files" since you might not have access to write to this directory.