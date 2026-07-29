#!/bin/bash
# LuminEditor 组件重构验证脚本

echo "=========================================="
echo "LuminEditor 组件重构验证"
echo "=========================================="
echo ""

QT_PATH="/d/XDY/WorkApp/Qt/6.5.3/msvc2019_64/bin"
QMLLINT="$QT_PATH/qmllint.exe"

# 1. 检查文件完整性
echo "1. 检查文件完整性..."
echo ""

COMMON_FILES=(
    "Resources/Common/qmldir"
    "Resources/Common/LuminButton.qml"
    "Resources/Common/LuminToolButton.qml"
    "Resources/Common/LuminMenuBar.qml"
    "Resources/Common/LuminMenu.qml"
    "Resources/Common/LuminMenuItem.qml"
    "Resources/Common/LuminSeparator.qml"
    "Resources/Common/LuminMenuSeparator.qml"
    "Resources/Common/LuminWindowButtons.qml"
)

BAR_FILES=(
    "Resources/Bar/LuminWidgetBar.qml"
    "Resources/Bar/LuminMainMenuBar.qml"
    "Resources/Bar/LuminToolBar.qml"
)

ALL_FILES=("${COMMON_FILES[@]}" "${BAR_FILES[@]}" "main.qml" "qml.qrc")

missing_count=0
for file in "${ALL_FILES[@]}"; do
    if [ -f "$file" ]; then
        echo "  ✓ $file"
    else
        echo "  ✗ $file (缺失)"
        ((missing_count++))
    fi
done

echo ""
if [ $missing_count -eq 0 ]; then
    echo "  文件完整性检查：通过 ✓"
else
    echo "  文件完整性检查：失败 ✗ (缺失 $missing_count 个文件)"
    exit 1
fi

echo ""
echo "2. 检查 QML 语法..."
echo ""

if [ ! -f "$QMLLINT" ]; then
    echo "  ⚠ qmllint 未找到，跳过语法检查"
else
    error_count=0
    for file in main.qml "${COMMON_FILES[@]}" "${BAR_FILES[@]}"; do
        if [[ "$file" == *.qml ]]; then
            output=$("$QMLLINT" "$file" 2>&1 | grep -E "Error:")
            if [ -n "$output" ]; then
                echo "  ✗ $file"
                echo "$output" | sed 's/^/    /'
                ((error_count++))
            else
                echo "  ✓ $file"
            fi
        fi
    done

    echo ""
    if [ $error_count -eq 0 ]; then
        echo "  语法检查：通过 ✓"
    else
        echo "  语法检查：发现 $error_count 个错误 ✗"
        exit 1
    fi
fi

echo ""
echo "3. 检查 qml.qrc 配置..."
echo ""

qrc_missing=0
for file in "${COMMON_FILES[@]}" "${BAR_FILES[@]}"; do
    if [[ "$file" == *.qml ]]; then
        if grep -q "<file>$file</file>" qml.qrc; then
            echo "  ✓ $file"
        else
            echo "  ✗ $file (未在 qml.qrc 中注册)"
            ((qrc_missing++))
        fi
    fi
done

echo ""
if [ $qrc_missing -eq 0 ]; then
    echo "  qml.qrc 配置：通过 ✓"
else
    echo "  qml.qrc 配置：失败 ✗ (缺失 $qrc_missing 个条目)"
    exit 1
fi

echo ""
echo "=========================================="
echo "验证完成！"
echo "=========================================="
echo ""
echo "统计："
echo "  - 基础组件: ${#COMMON_FILES[@]} 个"
echo "  - 核心组件: ${#BAR_FILES[@]} 个"
echo "  - 总文件数: ${#ALL_FILES[@]} 个"
echo ""
echo "状态: 所有检查通过 ✓"
echo ""
echo "可以构建项目了！"
echo "  方式1: 在 Visual Studio 中打开 Lumin.sln 并构建"
echo "  方式2: 运行 'qmake LuminEditor.pro && make'"
echo ""
