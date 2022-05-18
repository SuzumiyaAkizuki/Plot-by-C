# Plot-by-C
一种基于C++的PPM格式绘图工具箱，灵感来源于某大学《信号与系统》实验。

#用法说明

下载“arrayToPPM2.hpp”文件即可使用。

文件包含了一个结构体`PPMdata`，其中有三个分量`int r,g,b`表示三种颜色分量。

## 新建一张图：
```cpp
Graph G(width, height, centerX, centerY, rangeX, rangeY, gridX, gridY, line, grid, background, axis, s);
```
其中各参数的意义如下（按顺序）：

| 项目               | 意义                                  |
| ------------------ | ------------------------------------- |
| `int width`        | 整个图像的宽度 单位：像素             |
| `int height`       | 整个图像的高度 单位：像素             |
| `double centerX`   | 图片中心点对应的直角坐标X             |
| `double centerY`   | 图片中心点对应的直角坐标Y             |
| `double rangeX`    | X直角坐标范围                         |
| `double rangeY`    | Y直角坐标范围                         |
| `double gridX`     | X网格宽度（单位：直角坐标）           |
| `double gridY`     | Y网格宽度（单位：直角坐标）           |
| `PPMdata line`     | 绘图线颜色           |
| `PPMdata grid`     | 网格颜色           |
| `PPMdata background`     | 背景颜色           |
| `PPMdata axis`     | 坐标轴颜色           |
| `char *s`     | 文件名           |

## 在图上新增一个点
```cpp
G.drawPoint(x,y,size);
```
其中各参数的意义如下（按顺序）：

| 项目               | 意义                                  |
| ------------------ | ------------------------------------- |
| `double x`        | 点的横坐标             |
| `double y`       | 点的纵坐标             |
| `int size`   | 点的大小             |

## 在图上新增一条直线
```cpp
G.drawLine(x1,y1,x2,y2);
```
其中各参数的意义如下（按顺序）：

| 项目               | 意义                                  |
| ------------------ | ------------------------------------- |
| `double x1`        | 第一个点的横坐标             |
| `double y1`       | 第一个点的纵坐标             |
| `double x2`        | 第二个点的横坐标             |
| `double y2`       | 第二个点的纵坐标             |

## 在图上新增一条曲线
```cpp
G.drawXY(X,y,cnt);
```
其中各参数的意义如下（按顺序）：

| 项目               | 意义                                  |
| ------------------ | ------------------------------------- |
| `double* x`        | 采样点横坐标**必须单调递增**             |
| `double* y`       | 采样点纵坐标             |
| `int cnt`       | 采样点数目             |

## 输出文件
```cpp
G.draw();
```

