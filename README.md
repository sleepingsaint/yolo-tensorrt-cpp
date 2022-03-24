# YOLO TensorRT CPP

Original repo is taken from [here](https://github.com/enazoe/yolo-tensorrt)

## Prerequisites

* OpenCV
* TensorRT

I suggest using TensorRT docker containers from Nvidia Container registry.

## How to build

* Create a build directory

```
mkdir build
```

* Run the following commands

```bash
cd build && cmake .. && make
```

It will create a __custom_detector__ executable in bin folder

## How to run

```bash
./custom_detector <config file path> <weights file path> <classnames file path> <video file path> 
```

## Results

The results is __60 fps (inference fps)__ on Nvidia RTX 2080.
