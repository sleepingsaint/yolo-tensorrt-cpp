xhost +local:docker
sudo nvidia-docker run --rm -it -v /home1/mirproject/TATADATA/speedup/yolo-tensorrt:/workspaces/yolo-tensorrt -v /tmp/.X11-unix:/tmp/.X11-unix sleepingsaint/tensorrt_opencv:21.07.py3-4.2 bash
