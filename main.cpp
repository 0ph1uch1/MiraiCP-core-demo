// 这里需要特殊指出, 否则会和 utf8/core.h 混淆
#include "MiraiCP/core.h"
using namespace MiraiCP;

int main() {
    // 启动MiraiCP, 需要传入MiraiCP-core的jar组件
    Core::loadCore(R"(D:\Git\mirai\MiraiCP\kotlin\core\build\libs\MiraiCP-core-2.11.0-M2.jar)");
    // 登录一个bot
    Bot tmp(0);
    try {
        tmp = Core::login(1111, "password");
    }catch(BotException& e){
        Logger::logger.error("登录失败, 原因:", e.what());
    }
    // 使用全局日志发出
    Logger::logger.info("aa");
    Logger::logger.info(tmp.nick());
    // 自行控制主循环, 和最后的 while 配置, 否则会退出
    bool alive = true;
    // 可以直接在这里写监听
    Event::processor.registerEvent<GroupMessageEvent>([&alive](GroupMessageEvent a){
        Logger::logger.info("b");
        auto b = Group(a.group.id(), a.group.botid());
        Logger::logger.info("c");
        auto c = b[a.sender.id()];
        Logger::logger.info("d");
        c.changeNameCard(a.message.toMiraiCode());
        alive = false;
    });
    while (alive){};
    Core::exitCore();
}