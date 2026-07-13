#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<unistd.h>
using namespace std;

// ANSI 颜色定义
const std::string RESET  = "\033[0m";
const std::string RED    = "\033[31m";
const std::string GREEN  = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN   = "\033[36m";
const std::string PURPLE = "\033[35m";

void moo() {
    cout <<"                  (__)" << endl;
    cout <<"                  (oo)" << endl;
    cout <<"            /------\\/" << endl;
    cout <<"           / |     ||" << endl;
    cout <<"          *  /\\---/\\" << endl;
    cout <<"             ~~   ~~" << endl;
    cout << R"(..."Have you mooed today?"...)" << std::endl;
}
void moomoo() {
    cout<<"                     ("<<YELLOW<<"__"<<RESET<<")"<<endl;
    cout<<RED<<"             -------"<<YELLOW<<"~("<<CYAN<<".."<<YELLOW<<")~"<<endl;
    cout<<YELLOW<<"               ,----"<<RED<<"\\"<<YELLOW<<"("<<PURPLE<<"oo"<<YELLOW<<")"<<endl;
    cout<<YELLOW<<"              /|____|,'"<<endl;
    cout<<YELLOW<<"               /\\   /\\"<<endl;
    cout<<GREEN<<"wWwWwWwWwWwWwWwWwWwWwWwWwWwWw"<<endl;
    cout<<"...\"Have you mooed today?\"..."<<endl;
}
void moomoomoo() {
    cout<<"                       \\ /"<<endl;
    cout<<"    mOOh  (__)        -(_)-"<<endl;
    cout<<"       \\  ~Oo~___      / \\"<<endl;
    cout<<"          (..)  |\\"<<endl;
    cout<<"____________|_|_|____________"<<endl;
    cout<<"...\"Have you mooed today?\"..."<<endl;

}





int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout<<R"(
aptman 1.1.4.514 (amd64)
用法： apt [选项] 命令

命令行软件包管理器 apt 提供软件包搜索，管理和信息查询等功能。
它提供的功能与其他 APT 工具相同（像 apt-get 和 apt-cache），
但是默认情况下被设置得更适合交互。

常用命令：
list - 根据名称列出软件包
search - 搜索软件包描述
show - 显示软件包细节
install - 安装软件包
reinstall - 重新安装软件包
remove - 移除软件包
autoremove - 自动卸载所有不再使用的软件包
update - 更新可用软件包列表
upgrade - 通过 安装/升级 软件来更新系统
full-upgrade - 通过 卸载/安装/升级 来更新系统
edit-sources - 编辑软件源信息文件
modernize-sources - 将 .list 文件现代化并改写为 .sources 文件
satisfy - 使系统满足依赖关系字符串
                                )"<<YELLOW<<"本 APT 具有超级牛力。"<<endl;
        return 1;
    }

    if (geteuid()!=0) {
        cerr<<RED<<"杂鱼!用root才配见我!"<<endl;
        return -1;
    }

    if (string(argv[1])=="moo") {
        if (argc>2&&string(argv[2])=="moo") {
            if (argc>3&&string(argv[3])=="moo") {
                moomoomoo();
                return 0;
            }
            moomoo();
            return 0;
        }
        moo();
        return 0;
    }

    std::string cmd = argv[1];
    std::vector<std::string> args(argv + 2, argv + argc);
    std::string pacman = "pacman ";

    // 忽略 3-无对照 的命令
    if (cmd=="changelog"){cout<<RED<<"[没有...没有那个东西啦]arch可没有什么changelog"<<endl<<YELLOW<<"变通方法:从AUR安装asp 然后使用`asp log`命令查看历史哦~"<<endl<<CYAN<<"真是杂鱼~"<<endl;return 0;}
    else if (cmd=="source"){cout<<RED<<"[没有...没有那个东西啦]arch可没有什么source"<<endl<<CYAN<<"真是杂鱼~"<<endl;return 0;}
    else if (cmd=="edit-sources"){cout<<RED<<"[没有...没有那个东西啦]arch可不能这样换源哦~"<<endl<<YELLOW<<"变通方法:用你*爱*的编辑器编辑`/etc/pacman.d/mirrorlist`"<<endl<<CYAN<<"要自己来哦~"<<endl;return 0;}
    else if (cmd=="list"){cout<<RED<<"[没有...没有那个东西啦]arch可不支持列表查看"<<endl<<YELLOW<<"变通方法:从AUR安装asp 然后使用`asp list-*`命令查看列表哦~"<<endl<<CYAN<<"真是杂鱼~"<<endl;return 0;}
    else if (cmd=="satisfy"){cout<<RED<<"[没有...没有那个东西啦]arch可没有什么satisfy"<<endl<<CYAN<<"真是杂鱼~"<<endl;return 0;}
    else if (cmd=="--fix-broken"){cout<<RED<<"[没有...没有那个东西啦]arch安装失败了就回滚了哦~"<<endl<<CYAN<<"滚开口牙~"<<endl;return 0;}
    else if (cmd=="--no-install-recommends"){cout<<RED<<"[没有...没有那个东西啦]arch不支持自动安装推荐依赖哦~ *依赖都是强制暗转的* 推荐依赖仅作为提示"<<endl<<CYAN<<"只能看着哦~"<<endl;return 0;}
    else if (cmd=="-t"||cmd=="--target-release"){cout<<RED<<"[没有...没有那个东西啦]arch是滚动更新的 可不能想来就来哦~"<<endl<<CYAN<<"强制的哦~"<<endl;return 0;}
    else if (cmd=="-a"||cmd=="--architecture"){cout<<RED<<"[不需要那种东西啦]arch自己就能处理好架构 让pacman自己来..."<<endl<<CYAN<<"享受吧"<<endl;return 0;}


    // 1-直接对照 & 2-组合可对照
    if (cmd == "update") pacman += "-Sy";
    else if (cmd == "upgrade") pacman += "-Su";
    else if (cmd == "full-upgrade") pacman += "-Syu";
    else if (cmd == "clean") pacman += "-Scc";
    else if (cmd == "autoclean") pacman += "-Sc";
    else if (cmd == "autoremove" || cmd == "autopurge") pacman += "-Rns $(pacman -Qdtq)";
    else if (cmd == "-h" || cmd == "--help") pacman += "-h";
    else if (cmd == "-v" || cmd == "--version")cout<<GREEN<<"pacman fucked apt 114514 times"<<endl,pacman += "-V";
    else if (cmd == "install" || cmd == "reinstall") {
        pacman += "-S";
        for (const auto& a : args) {
            if (a == "-y" || a == "--yes") pacman += " --noconfirm";
            else if (a == "-d" || a == "--download-only") pacman = "pacman -Sw";
            else if (a == "--no-upgrade") pacman += " --needed";
            else if (a == "--reinstall") continue;
            else pacman += " " + a;
        }
    }
    else if (cmd == "remove") {
        bool purge = std::find(args.begin(), args.end(), "--purge") != args.end();
        pacman += purge ? "-Rns" : "-R";
        for (const auto& a : args) if (a != "--purge") pacman += " " + a;
    }
    else if (cmd == "purge") {
        pacman += "-Rns";
        for (const auto& a : args) pacman += " " + a;
    }
    else if (cmd == "search") {
        pacman += "-Ss";
        for (const auto& a : args) pacman += " " + a;
    }
    else if (cmd == "show") {
        pacman += "-Si";
        for (const auto& a : args) pacman += " " + a;
    }
    else if (cmd == "download") {
        pacman += "-Sw";
        for (const auto& a : args) pacman += " " + a;
    }
    else {
        std::cout << RED << "Unknown command: " << cmd << RESET << "\n";
        return 1;
    }

    // 彩色输出转换结果
    std::cout << GREEN << "Converted: " << RESET << pacman << "\n";
    cout<<RESET<<endl;
    // 取消注释以实际执行
    system(pacman.c_str());

    return 0;
}

