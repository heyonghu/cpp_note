# 1.下载opencv安装包
https://opencv.org/releases/
# 2.安装环境依赖

```cpp
sudo apt-get install build-essential libgtk2.0-dev libavcodec-dev libavformat-dev libjpeg-dev libswscale-dev libtiff5-dev
sudo apt-get install libgtk2.0-dev
sudo apt-get install pkg-config
```


# 3.安装

```cpp
1.cd到opencv目录下进行解压
2.创建build文件夹
    
mkdir build
cd build
    
3.编译opencv
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j8
make install
```


# 4.环境配置

```cpp
1.用gedit打开/etc/ld.so.conf
2.在文件中加上一行include /usr/local/lib
sudo gedit /etc/ld.so.conf
#在文件中加入一行include  /usr/local/lib
#然后执行：
sudo ldconfig
    
2.修改bash.bashrc文件
sudo gedit /etc/bash.bashrc 
3.添加
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
export PKG_CONFIG_PATH
4.source
source /etc/bash.bashrc
```

# 5. 查看是否安装成功
```cpp
显示版本号即安装成功

pkg-config opencv --modversion
```



# 遇到错误
```cpp
1. make install 时遇到
CMake Error at cmake_install.cmake:41 (file): file INSTALL cannot copy file “/home/wsb/gflags”

// 增加权限即可
sudo make install

2.查看版本 或者输入以下报错时
pkg-config --cflags opencv

Package opencv was not found in the pkg-config search path.
Perhaps you should add the directory containing `opencv.pc'
to the PKG_CONFIG_PATH environment variable
No package 'opencv' found

是缺失了opencv.pc这个配置信息文件，故解决方法就是添加这个文件然后将其导入到环境变量中，具体操作如下：

cd /usr/local/lib
sudo mkdir pkgconfig
cd pkgconfig
sudo touch opencv.pc

写入以下信息 注意opencv版本号

prefix=/usr/local
exec_prefix=${prefix}
includedir=${prefix}/include
libdir=${exec_prefix}/lib

Name: opencv
Description: The opencv library
Version:4.0.1
Cflags: -I${includedir}/opencv4
Libs: -L${libdir} -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann  -lopencv_core
~                                               

然后导入环境变量

export  PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
```




# 测试代码
下面是opencv官方例程(opencv-4.0.1/samples/cpp/example_cmake)里的代码文件和Makefile文件：
example.cpp:

```cpp
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawText(Mat & image);

int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat image;
    VideoCapture capture;
    capture.open(0);
    if(capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        for(;;)
        {
            capture >> image;
            if(image.empty())
                break;
            drawText(image);
            imshow("Sample", image);
            if(waitKey(10) >= 0)
                break;
        }
    }
    else
    {
        cout << "No capture" << endl;
        image = Mat::zeros(480, 640, CV_8UC1);
        drawText(image);
        imshow("Sample", image);
        waitKey(0);
    }
    return 0;
}

void drawText(Mat & image)
{
    putText(image, "Hello OpenCV",
            Point(20, 50),
            FONT_HERSHEY_COMPLEX, 1, // font face and scale
            Scalar(255, 255, 255), // white
            1, LINE_AA); // line thickness and type
}
```


Makefile:

```cpp
CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)

all: opencv_example

opencv_example: example.o; $(CXX) $< -o $@ $(LDFLAGS)

%.o: %.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f example.o opencv_example
```


创建文件 并进行make 生成可执行文件 opencv_example

```cpp
//创建文件 并执行
make 
./opencv_example  

```

# CMakeLists:

```cpp
cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp)

set(OpenCV_DIR "/snap/opencv-4.6.0/build")
# 寻找 opencv 的库
find_package(OpenCV COMPONENTS core highgui imgproc imgcodecs)
# 添加 opencv 的头文件
include_directories(${OpenCV_INCLUDE_DIRS})
# 链接 opencv 动态库路径
link_directories(${OpenCV_LIBRARY_DIRS})

## 设置库文件
target_link_libraries(untitled ${OpenCV_LIBS})
```

