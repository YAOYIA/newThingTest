# 1. 选择基础镜像（相当于：我基于什么菜谱来做？）
FROM nginx:alpine

# 2. 复制文件（相当于：把我刚切的菜放进蒸锅）
#    把当前目录的 index.html，复制到镜像里的 Nginx 网页目录
COPY index.html /usr/share/nginx/html/index.html

# 3. 声明容器启动后做什么（nginx 镜像默认已经写好了启动命令，这里不用改）
#    CMD 指令在基础镜像里已经有了，所以我们省略。

