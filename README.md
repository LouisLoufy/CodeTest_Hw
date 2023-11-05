## 图片文件过大，启用了lfs
``` bash
sudo apt install git-lfs
git lfs clone git@github.com:LouisLoufy/OD.git
```

## build
``` bash
mkdir build && cd build
cmake .. && make -j16
```