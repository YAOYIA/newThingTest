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