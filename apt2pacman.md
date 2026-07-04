# apt ↔ pacman 命令对照表
| 层次 | apt命令 | pacman等效 | 说明 |
|------|---------|-----------|------|
| 1-直接对照 | apt update | pacman -Sy | 同步包数据库 |
| 1-直接对照 | apt upgrade | pacman -Su | 升级已安装包 |
| 1-直接对照 | apt full-upgrade | pacman -Syu | 同步数据库并升级（可处理依赖变更） |
| 1-直接对照 | apt install <pkg> | pacman -S <pkg> | 安装包 |
| 1-直接对照 | apt reinstall <pkg> | pacman -S <pkg> | 重新安装（pacman 默认覆盖，--needed 阻止） |
| 1-直接对照 | apt remove <pkg> | pacman -R <pkg> | 移除包（保留配置） |
| 1-直接对照 | apt purge <pkg> | pacman -Rns <pkg> | 移除包、配置及无用依赖 |
| 1-直接对照 | apt search <keyword> | pacman -Ss <keyword> | 搜索仓库包 |
| 1-直接对照 | apt show <pkg> | pacman -Si <pkg> | 查看仓库包详情 |
| 1-直接对照 | apt download <pkg> | pacman -Sw <pkg> | 仅下载包到缓存 |
| 1-直接对照 | apt clean | pacman -Scc | 清空全部缓存 |
| 1-直接对照 | apt autoclean | pacman -Sc | 仅清理未安装包的缓存 |
| 1-直接对照 | apt -h / --help | pacman -h / --help | 帮助信息 |
| 1-直接对照 | apt -v / --version | pacman -V / --version | 版本信息 |
| 2-组合可对照 | apt list | pacman -Q / -Sl / -Ss | 按场景拆分：-Q 已安装，-Sl 仓库列表，-Ss 搜索 |
| 2-组合可对照 | apt list --installed | pacman -Q | 已安装包列表 |
| 2-组合可对照 | apt list --upgradeable | pacman -Qu | 可升级包列表 |
| 2-组合可对照 | apt list -a <pkg> | pacman -Sl | grep <pkg> | 查看仓库中所有可用版本 |
| 2-组合可对照 | apt autoremove | pacman -Rns $(pacman -Qdtq) | 移除孤儿包（无其他包依赖） |
| 2-组合可对照 | apt autopurge | pacman -Rns $(pacman -Qdtq) | 同 autoremove；pacman -n 已含配置清除 |
| 2-组合可对照 | apt depends <pkg> | pacman -Si <pkg> | grep 'Depends On' / pactree <pkg> | 依赖树需安装 pacman-contrib |
| 2-组合可对照 | apt rdepends <pkg> | pacman -Qi <pkg> | grep 'Required By' / pactree -r <pkg> | 反向依赖需 pacman-contrib |
| 2-组合可对照 | apt policy <pkg> | pacman -Si <pkg> | grep -E 'Repository|Version' / pacman -Sl | grep <pkg> | 版本优先级需组合查询 |
| 2-组合可对照 | apt satisfy 'deps...' | pacman -T <pkg1> <pkg2> + pacman -S <pkg1> <pkg2> | -T 检测缺失，-S 安装；无单条解析字符串功能 |
| 2-组合可对照 | apt build-dep <pkg> | asp export <pkg> → 解析 PKGBUILD makedepends → pacman -S / makepkg -s | 或直接用 makepkg -s 自动安装构建依赖 |
| 2-组合可对照 | apt install -y <pkg> | pacman -S --noconfirm <pkg> | 自动确认 |
| 2-组合可对照 | apt install -d <pkg> | pacman -Sw <pkg> | 仅下载 |
| 2-组合可对照 | apt install -s <pkg> | pacman -Sp <pkg> | 仅打印下载 URI（不完全模拟） |
| 2-组合可对照 | apt remove --purge <pkg> | pacman -Rns <pkg> | 完全清除 |
| 2-组合可对照 | apt full-upgrade -s --print-uris | pacman -Syu --print | 打印下载链接 |
| 2-组合可对照 | apt -c <file> | pacman --config <file> | 指定配置文件 |
| 2-组合可对照 | apt -q / --quiet | pacman -q / --quiet | 静默输出 |
| 2-组合可对照 | apt -d / --download-only | pacman -w / --downloadonly | 仅下载 |
| 2-组合可对照 | apt --reinstall | pacman -S（去掉 --needed） | 强制重新安装 |
| 2-组合可对照 | apt --no-upgrade | pacman -S --needed | 不重新安装已存在版本 |
| 2-组合可对照 | apt --print-uris | pacman -Sp | 打印 URI |
| 3-无对照 | apt changelog <pkg> | 无对照 | Arch 包无内置 changelog 机制。替代：安装 asp 后执行 asp log <pkg> 查看 PKGBUILD 提交历史；或查看上游 Release Notes。 |
| 3-无对照 | apt source <pkg> | 无对照 | pacman 无内置源码下载命令。替代：安装 asp 工具，执行 asp export <pkg>（导出最新 PKGBUILD）或 asp checkout <pkg>（获取完整 Git 历史）。也可手动从 Arch Linux Archive (ALA) 下载。 |
| 3-无对照 | apt edit-sources | 无对照 | pacman 无内置编辑器调用命令。替代：直接手动编辑 /etc/pacman.conf 及 /etc/pacman.d/mirrorlist（如 sudo nano /etc/pacman.conf）。 |
| 3-无对照 | apt moo | 无对照 | pacman 无彩蛋命令。无替代。 |
| 3-无对照 | apt list（状态标记） | 无对照 | pacman 无 [installed,automatic]、[upgradable from: x] 等状态标记的列表格式。pacman -Q 仅输出 包名 版本，无仓库来源、安装方式标记。 |
| 3-无对照 | apt satisfy（复杂依赖字符串） | 无对照 | pacman 无 apt satisfy 'pkg1, pkg2 (>= 1.0)' 这种复杂依赖字符串解析与安装功能。pacman -T 仅检测缺失并输出包名，不处理版本约束字符串；pacman -S 只能按包名安装。 |
| 3-无对照 | apt --fix-broken | 无对照 | pacman 依赖处理是原子性的，安装/升级时若依赖不满足会直接失败并回滚，不存在修复损坏依赖的独立模式。 |
| 3-无对照 | apt --no-install-recommends | 无对照 | pacman 无 Recommends/Suggests 概念。Arch 仓库中所有 depends 均为强依赖，optdepends 仅提示信息，不会自动安装。 |
| 3-无对照 | apt -t <release> / --target-release | 无对照 | Arch 为滚动发行版，无 release 分支概念。pacman 不支持按发行版目标安装。 |
| 3-无对照 | apt -a <arch> / --architecture | 无对照 | pacman 自动处理架构，无按架构过滤安装的独立选项。 |
