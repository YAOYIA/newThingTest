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