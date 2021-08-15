# PTAM-AR
A PTAM project that  integrates a video window and rotating cube.



Steps:

1. unzip ptam-include-lib.zip , add "include" to the "VC include dir" , add "lib" to the "VC libiary dir"
    - additional lib: 
        - libcvd.lib
        - gvars3.lib
        - glew32.lib
        - opengl32.lib
        - 1394camera.lib
        - blas_win32_MT.lib
        - lapack_win32_MT.lib
        - pthreadVCE2.lib
        - videoInput.lib
3. unzip ptam-dll and move these .dll files to directory where PTAM.exe is.
4. build CameraCalibrator
5. build PTAM

Note:
- This project only provides the Release version of lib.

Result:
1. Video Window
- ![VideoWindow.gif](https://i.loli.net/2021/06/06/JWbQni6hg2pHBPR.gif)

2. rotating cube
- ![MovableObj.gif](https://i.loli.net/2021/06/06/EA3KZcJUPq6iy8C.gif)

