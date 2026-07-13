#!/bin/bash
set -euo pipefail

RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'; BLUE='\033[0;34m'; NC='\033[0m'

BUILD_TYPE="Release"
CLEAN=0
INSTALL=0

while [[ $# -gt 0 ]]; do
    case "$1" in
        --debug|-d) BUILD_TYPE="Debug"; shift ;;
        --clean|-c) CLEAN=1; shift ;;
        --install|-i) INSTALL=1; shift ;;
        --help|-h)
            echo "用法: $0 [--debug] [--clean] [--install]"
            echo "  --debug   Debug 模式 (-O0 -g)"
            echo "  --clean   强制重新配置"
            echo "  --install 安装到 /usr/local/bin"
            exit 0
            ;;
        *) echo -e "${RED}未知参数: $1${NC}"; exit 1 ;;
    esac
done

# 1. 检查并安装基础依赖
echo -e "${BLUE}检查构建依赖...${NC}"
check_dep() {
    if ! command -v "$1" &>/dev/null; then
        echo "安装 $1..."
        sudo pacman -S --needed --noconfirm "$2"
    fi
}
check_dep cmake cmake
check_dep g++ gcc
check_dep ninja ninja

# 2. 验证 CMake 版本 >= 4.3
REQ_VER="4.3"
CUR_VER=$(cmake --version | head -n1 | grep -oP '[0-9]+\.[0-9]+\.[0-9]+')
if [ "$(printf '%s\n' "$REQ_VER" "$CUR_VER" | sort -V | head -n1)" != "$REQ_VER" ]; then
    echo -e "${RED}错误: CMake 要求 >= $REQ_VER，当前 $CUR_VER${NC}"
    echo "请更新: sudo pacman -S cmake"
    exit 1
fi
echo -e "${GREEN}CMake 版本: $CUR_VER ✓${NC}"

# 3. 选择生成器（Ninja 优先）
if command -v ninja &>/dev/null; then
    GENERATOR="Ninja"
    echo -e "${GREEN}生成器: Ninja${NC}"
else
    GENERATOR="Unix Makefiles"
    echo -e "${YELLOW}生成器: Make (建议安装 ninja)${NC}"
fi

# 4. 清理/创建构建目录
if [ "$CLEAN" -eq 1 ] && [ -d "build" ]; then
    echo "清理构建目录..."
    rm -rf build
fi
mkdir -p build

# 5. 配置
echo -e "${BLUE}配置项目 ($BUILD_TYPE)...${NC}"
cmake -B build -S . \
    -G "$GENERATOR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_COLOR_DIAGNOSTICS=ON

# 6. 编译
JOBS=$(nproc)
echo -e "${BLUE}编译 (并行 $JOBS)...${NC}"
cmake --build build --parallel "$JOBS"

# 7. 安装或提示
if [ "$INSTALL" -eq 1 ]; then
    echo -e "${GREEN}安装到 /usr/local/bin/aptman${NC}"
    sudo install -Dm755 build/aptman /usr/local/bin/aptman
    echo -e "${GREEN}完成！运行: aptman${NC}"
else
    echo -e "${GREEN}编译完成！运行: ./build/aptman${NC}"
fi