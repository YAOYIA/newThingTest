# 容器、镜像
## 镜像（Image）：写在纸上的菜谱
他只记录步骤（文件系统）、配料（环境变量）、和做法（启动命令）
特性：它是只读的，你照着做一万遍，菜谱上的字不会变。不做菜的时候，他只是一张纸，不占用灶台空间（不占用cpu/内存），只占用书架空间（硬盘）

## 容器（Container）：锅里炒的菜
你照着菜谱真正动手去做了，油盐酱醋下过，这就是运行起来的过程。
特性：他是活的，占用cpu，内存，有独立的温度。
关键点：你在炒菜的过程中撒了一把葱花（修改了文件），菜谱（镜像）上不会多出现葱花，菜炒完了吃掉了（容器停止、删除），菜谱不会变化，下次还可以使用。

# 实战
```
docker run -d --name my-nginx -p 8080:80 nginx
```
run 表示运行一个容器
-d  表示后台运行
--name my-nginx  给他起一个名字
-p 8080:80   重点！把本机的8080端口，映射到内部的80端口
nginx    使用的镜像的名称

# 管理容器
现在镜像跑起来了，，要学会操控它
1.查看正在运行的容器
docker ps
2.查看所有容器
docker ps -a
3.停止容器
docker stop my-nginx
4.启动容器
docker start my-nginx
5.删除容器
docker rm my-nginx

# 镜像管理
1.下载镜像
docker pull ubuntu:22.04

2.查看所有镜像
docker images

# 自己制作镜像
写菜谱的大神 --- 编写Dockerfile
1.创建自己的厨房（项目文件）
mkdir  my_first_image

2.准备食材（你的网页文件）
创建一个简单的index.html文件
echo '<h1>🚀 这是我亲手做的 Docker 镜像！</h1>' > index.html

3.写下菜谱（Dockerfile）
这是最核心的一步！在同目录下，新建一个Dockerfile文件
FROM：所有镜像都必须基于某个“父镜像”。这里用了超小的 nginx:alpine（只有几兆）。

COPY：这是镜像和容器的分水岭！ 这行命令发生在 docker build 时，它把你的文件永久刻录进镜像的只读层。以后任何基于此镜像启动的容器，天生就有这个文件。

4.炒菜（构建镜像）
docker build -t my-nginx-custom:v1 .
build：构建镜像。

-t my-nginx-custom:v1：给镜像起个名字和版本号（Tag）。

末尾有一个空格和点号 .：这个点代表“把当前目录作为构建上下文（Build Context）发送给 Docker 引擎”。（相当于把整个文件夹打包传给 Docker 后台）。

5.尝菜
docker run -d -p 8080:80 --name my-app my-nginx-custom:v1

6.还记得上节课我们删容器改文件吗？现在做一次终极测试：
把现在的容器删掉：docker rm -f my-app
把本地的 index.html 删掉或改个名字：rm index.html（或者重命名）。
再次运行你的镜像：docker run -d -p 8080:80 my-nginx-custom:v1
刷新浏览器（localhost:8080）。
结果是什么？ 页面依然是 “🚀 这是我亲手做的 Docker 镜像！”
为什么？ 因为 index.html 已经作为只读镜像层被锁死在镜像里了。你电脑本地的源文件删了，关镜像什么事？镜像一旦构建，就是独立的、不可变的艺术品。

# 进阶硬核知识：Dockerfile 的“层”与缓存（面试必问）
你刚才写的 Dockerfile 只有两行，但实际构建时，Docker 是一行一行执行的，每一行都会产生一个“中间层（Layer）”。

|指令|作用时机|特点|
|----|----|----|
|FROM	|构建时	|拉取基础层|
|COPY	|构建时	|产生一个新层，把文件快照存进去|
|RUN（你没写，但以后常用）	|构建时	|执行命令（比如 RUN apt-get install），产生新层|
|CMD / ENTRYPOINT	|容器启动时|	不产生层！ 只定义启动命令|

重要技巧（缓存加速）：
如果你以后要写复杂的 Dockerfile，记得把不容易变动的命令（如安装依赖）写在上面，把容易变动的代码（COPY）写在下面。因为 Docker 构建时，如果某一层没变，它会直接用缓存，秒速完成！
错误写法（每次都要重装依赖，慢死）：

```
COPY . /app
RUN pip install -r requirements.txt
正确写法（依赖不变，秒速构建）：
```
```
COPY requirements.txt /app
RUN pip install -r requirements.txt
COPY . /app   # 代码改了，只重新复制这最后一步
```

# docker 环境上写代码的正确姿势
代码放在宿主机，通过挂载 -v "映射进容器，在宿主机用ID编写，容器里面实时生效"

# 挂载使用
1.创建文件夹和项目
```
mkdir second && cd second
```

2.写一个需要编译的c程序
创建main.c
```
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int x, y;
    printf("请输入两个整数（空格隔开）: ");
    scanf("%d %d", &x, &y);
    printf("✅ 计算结果: %d + %d = %d\n", x, y, add(x, y));
    return 0;
}
```

3.核心实验一 在docker中编译，挂载法
场景：你的电脑没有装gcc，但是想要编译这个.c文件
无需安装任何编译器，直接使用docker拉去一个带有gcc的镜像，把代码挂载上去，编译完，编译得到的二进制直接留在电脑上。
```
docker run --rm -v $(pwd):/workspace -w /workspace gcc:alpine gcc -o calculator main.c
```

参数|	含义
---|---
--rm	|编译完自动删除容器，不占空间（一次性工具）
-v $(pwd):/workspace	|把当前代码文件夹挂载进容器的 /workspace
-w /workspace	|进入容器后，默认就在 /workspace 目录下
gcc:alpine	|只有几兆的超小 Linux 发行版，自带 GCC
gcc -o calculator main.c|	这就是在容器内执行的编译命令


4.用dockerfile + 多阶段构建
现在要把程序打包成一个镜像，让任何人都可以一件运行，且镜像极小。
新建dockerfile
```
# ========== 阶段 1：编译环境（大而全） ==========
FROM gcc:alpine AS builder

WORKDIR /build

# 复制源码
COPY main.c .

# 【编译】生成静态链接的可执行文件（不依赖外部 .so 库）
RUN gcc -static -o calculator main.c

# ========== 阶段 2：运行环境（极简，只有 5MB） ==========
FROM alpine:latest

WORKDIR /app

# 从第一阶段只复制编译好的二进制文件
COPY --from=builder /build/calculator .

# 容器启动时执行它
CMD ["./calculator"]
```

5.构建镜像并运行
1.构建镜像
```
docker build -t c-calculator:v1 .
```
2.运行镜像
```
docker run -it --rm c-calculator:v1
```

6.结合挂载进行开发调试
1.修改宿主机的main.c
2.不用重新build镜像，而是服用之前的编译容器。直接在容器内编译，映射出来。
```
docker run --rm -v $(pwd):/workspace -w /workspace gcc:alpine gcc -o calculator main.c
```
3.直接在宿主机测试新编出的文件。
